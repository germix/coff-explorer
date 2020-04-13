#include "TreeModel.h"
#include <QFileInfo>
#include "TreeItem.h"
#include "TreeItemFileHeader.h"
#include "TreeItemFolder.h"
#include "TreeItemRoot.h"
#include "TreeItemSection.h"
#include "TreeItemStringTable.h"
#include "TreeItemSymbolTable.h"
#include "SymbolTableItem.h"

#define MAX_COLUMNS 1

TreeModel::TreeModel(QObject* parent)
	: QAbstractItemModel(parent)
	, root(nullptr)
{
	root = new TreeItemRoot();
}

TreeModel::~TreeModel()
{
	clear();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
	if(row < 0 || column < 0 || column >= MAX_COLUMNS)
	{
		return QModelIndex();
	}
	TreeItem* parentItem = parent.isValid() ? toItem(parent) : root;
	if(parentItem && row < parentItem->children.count())
	{
		TreeItem* item = parentItem->children.at(row);
		if(item)
			return createIndex(row, column, item);
		return QModelIndex();
	}
	return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& child) const
{
	if(!child.isValid())
		return QModelIndex();
	TreeItem* item = static_cast<TreeItem*>(child.internalPointer());
	if(!item || item == root)
		return QModelIndex();
	return toIndex(item->parent, 0);
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
	if(!root)
		return 0;
	if(!parent.isValid())
		return root->children.count();
	TreeItem* parentItem = toItem(parent);
	if(parentItem)
		return parentItem->children.count();
	return 0;
}

int TreeModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return MAX_COLUMNS;
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
	if(!index.isValid())
		return QVariant();
	TreeItem* item = toItem(index);
	if(!item)
		return QVariant();
	if(role == Qt::DisplayRole)
	{
		if(index.column() == 0)
		{
			return item->getLabel();
		}
	}
	else if(role == Qt::DecorationRole)
	{
		if(index.column() == 0)
		{
			return item->getIcon();
		}
	}
	return QVariant();
}

void TreeModel::clear()
{
	if(root)
	{
		beginResetModel();
		delete root;
		root = nullptr;
		endResetModel();
	}
}

bool TreeModel::loadFile(const QString& fileName)
{
	clear();

	QFile file(fileName);
	COFF_FILE_HEADER fhdr;

	if(!file.open(QFile::ReadOnly))
		return false;
	file.read((char*)&fhdr, sizeof(fhdr));

	beginResetModel();
	root = new TreeItemRoot();
	TreeItemFileHeader* fileHeaderItem = new TreeItemFileHeader(root, fileName, fhdr);

	//
	// Read symbols
	//
	TreeItemFolder* sectionFolder = new TreeItemFolder(fileHeaderItem, "Sections");
	for(int i = 0; i < fhdr.NumberOfSections; i++)
	{
		COFF_SECTION_HEADER shdr;

		file.read((char*)&shdr, sizeof(shdr));

		new TreeItemSection(sectionFolder, shdr);
	}
	for(int i = 0; i < sectionFolder->children.size(); i++)
	{
		TreeItemSection* sec = (TreeItemSection*)sectionFolder->children[i];

		file.seek(sec->header.PointerToRawData);
		sec->data = file.read(sec->header.SizeOfRawData);
	}

	//
	// Read string table
	//
	QByteArray stringTableData;
	TreeItemStringTable* stringTableItem = new TreeItemStringTable(fileHeaderItem);

	file.seek(fhdr.PointerToSymbolTable + fhdr.NumberOfSymbols*SIZE_OF_COFF_SYMBOL);

	if(file.pos() < file.size())
	{
		quint32 len;
		file.read((char*)&len, sizeof(quint32));
		len -= 4;
		stringTableData = file.read(len);
		const char* ptr = stringTableData.constData();

		while(len > 0)
		{
			char chr;
			QString str;
			do
			{
				len--;
				chr = *ptr++;
				if(chr != 0)
					str += chr;
			}
			while(chr != 0 && len > 0);

			stringTableItem->strings.append(str);
		}
	}

	//
	// Read symbol table
	//
	TreeItemSymbolTable* symbolTableItem = new TreeItemSymbolTable(fileHeaderItem);

	file.seek(fhdr.PointerToSymbolTable);
	for(unsigned int i = 0; i < fhdr.NumberOfSymbols; i++)
	{
		COFF_SYMBOL e;

		file.read((char*)&e, sizeof(e));

		symbolTableItem->items.append(new SymbolTableItem(e));

		for(int j = 0; j < e.NumberOfAuxSymbols; j++)
		{
			i++;
			file.skip(SIZE_OF_COFF_SYMBOL);
		}
	}
	for(int i = 0; i < symbolTableItem->items.size(); i++)
	{
		SymbolTableItem* item = symbolTableItem->items[i];

		if(item->entry.LongName.Zeroes == 0)
		{
			item->name = QString((char*)&stringTableData.constData()[item->entry.LongName.Offset-4]);
		}
		else
		{
			char n[8+1];

			strncpy(n, (char*)item->entry.ShortName, 8);
			n[8] = 0;
			item->name = n;
		}
	}

	endResetModel();

	return true;
}

TreeItem* TreeModel::toItem(const QModelIndex& index) const
{
	if(!index.isValid())
		return 0;
	return static_cast<TreeItem*>(index.internalPointer());
}

QModelIndex TreeModel::toIndex(TreeItem* item, int column) const
{
	if(!item || (item == root))
		return QModelIndex();
	TreeItem* parent = item->parent;
	if(!parent)
		parent = root;
	int row = parent->children.lastIndexOf(item);
	if(row != -1)
		return createIndex(row, column, item);
	return QModelIndex();
}
