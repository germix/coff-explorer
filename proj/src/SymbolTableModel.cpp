#include "SymbolTableModel.h"
#include "SymbolTableItem.h"
#include "TreeItemSymbolTable.h"

#define MAX_COLUMNS 6

SymbolTableModel::SymbolTableModel(QObject* parent)
	: QAbstractItemModel(parent)
	, root(nullptr)
{
}

SymbolTableModel::~SymbolTableModel()
{
}

void SymbolTableModel::setSymbolTable(TreeItemSymbolTable* st)
{
	beginResetModel();
	root = st;
	endResetModel();
}

QVariant SymbolTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
			case 0: return "Name";
			case 1: return "Value";
			case 2: return "SectionNumber";
			case 3: return "Type";
			case 4: return "StorageClass";
			case 5: return "NumberOfAuxSymbols";
			default:
				return QVariant();
		}
	}
	return QVariant();
}

QModelIndex SymbolTableModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	if(!root || row < 0)
		return QModelIndex();

	if((row >= 0 && row < root->items.size()) && (column >= 0 && column < MAX_COLUMNS))
	{
		return createIndex(row, column, root->items.at(row));
	}
	return QModelIndex();
}

QModelIndex SymbolTableModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	return QModelIndex();
}

int SymbolTableModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	if(!root)
		return 0;
	if(!parent.isValid())
		return root->items.count();
	return 0;
}

int SymbolTableModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return MAX_COLUMNS;
}

QVariant SymbolTableModel::data(const QModelIndex& index, int role) const
{
	if(role == Qt::DisplayRole)
	{
		SymbolTableItem* item = static_cast<SymbolTableItem*>(index.internalPointer());

		switch(index.column())
		{
			case 0:
				return item->name;
			case 1:
				return QString().sprintf("%d", item->entry.Value);
			case 2:
				switch(item->entry.SectionNumber)
				{
					case IMAGE_SYM_UNDEFINED:					return "IMAGE_SYM_UNDEFINED";
					case IMAGE_SYM_ABSOLUTE:					return "IMAGE_SYM_ABSOLUTE";
					case IMAGE_SYM_DEBUG:						return "IMAGE_SYM_DEBUG";
				}
				return QString().sprintf("%d", item->entry.SectionNumber);
			case 3:
				switch(BTYPE(item->entry.Type))
				{
					case IMAGE_SYM_DTYPE_NULL:					return "IMAGE_SYM_DTYPE_NULL";
					case IMAGE_SYM_DTYPE_POINTER:				return "IMAGE_SYM_DTYPE_POINTER";
					case IMAGE_SYM_DTYPE_FUNCTION:				return "IMAGE_SYM_DTYPE_FUNCTION";
					case IMAGE_SYM_DTYPE_ARRAY:					return "IMAGE_SYM_DTYPE_ARRAY";
				}
				return "?";
			case 4:
				switch(item->entry.StorageClass)
				{
					case IMAGE_SYM_CLASS_END_OF_FUNCTION:		return "IMAGE_SYM_CLASS_END_OF_FUNCTION";
					case IMAGE_SYM_CLASS_NULL:					return "IMAGE_SYM_CLASS_NULL";
					case IMAGE_SYM_CLASS_AUTOMATIC:				return "IMAGE_SYM_CLASS_AUTOMATIC";
					case IMAGE_SYM_CLASS_EXTERNAL:				return "IMAGE_SYM_CLASS_EXTERNAL";
					case IMAGE_SYM_CLASS_STATIC:				return "IMAGE_SYM_CLASS_STATIC";
					case IMAGE_SYM_CLASS_REGISTER:				return "IMAGE_SYM_CLASS_REGISTER";
					case IMAGE_SYM_CLASS_EXTERNAL_DEF:			return "IMAGE_SYM_CLASS_EXTERNAL_DEF";
					case IMAGE_SYM_CLASS_LABEL:					return "IMAGE_SYM_CLASS_LABEL";
					case IMAGE_SYM_CLASS_UNDEFINED_LABEL:		return "IMAGE_SYM_CLASS_UNDEFINED_LABEL";
					case IMAGE_SYM_CLASS_MEMBER_OF_STRUCT:		return "IMAGE_SYM_CLASS_MEMBER_OF_STRUCT";
					case IMAGE_SYM_CLASS_ARGUMENT:				return "IMAGE_SYM_CLASS_ARGUMENT";
					case IMAGE_SYM_CLASS_STRUCT_TAG:			return "IMAGE_SYM_CLASS_STRUCT_TAG";
					case IMAGE_SYM_CLASS_MEMBER_OF_UNION:		return "IMAGE_SYM_CLASS_MEMBER_OF_UNION";
					case IMAGE_SYM_CLASS_UNION_TAG:				return "IMAGE_SYM_CLASS_UNION_TAG";
					case IMAGE_SYM_CLASS_TYPE_DEFINITION:		return "IMAGE_SYM_CLASS_TYPE_DEFINITION";
					case IMAGE_SYM_CLASS_UNDEFINED_STATIC:		return "IMAGE_SYM_CLASS_UNDEFINED_STATIC";
					case IMAGE_SYM_CLASS_ENUM_TAG:				return "IMAGE_SYM_CLASS_ENUM_TAG";
					case IMAGE_SYM_CLASS_MEMBER_OF_ENUM:		return "IMAGE_SYM_CLASS_MEMBER_OF_ENUM";
					case IMAGE_SYM_CLASS_REGISTER_PARAM:		return "IMAGE_SYM_CLASS_REGISTER_PARAM";
					case IMAGE_SYM_CLASS_BIT_FIELD:				return "IMAGE_SYM_CLASS_BIT_FIELD";
					case IMAGE_SYM_CLASS_FAR_EXTERNAL:			return "IMAGE_SYM_CLASS_FAR_EXTERNAL";
					case IMAGE_SYM_CLASS_BLOCK:					return "IMAGE_SYM_CLASS_BLOCK";
					case IMAGE_SYM_CLASS_FUNCTION:				return "IMAGE_SYM_CLASS_FUNCTION";
					case IMAGE_SYM_CLASS_END_OF_STRUCT:			return "IMAGE_SYM_CLASS_END_OF_STRUCT";
					case IMAGE_SYM_CLASS_FILE:					return "IMAGE_SYM_CLASS_FILE";
					case IMAGE_SYM_CLASS_SECTION:				return "IMAGE_SYM_CLASS_SECTION";
					case IMAGE_SYM_CLASS_WEAK_EXTERNAL:			return "IMAGE_SYM_CLASS_WEAK_EXTERNAL";
					case IMAGE_SYM_CLASS_CLR_TOKEN:				return "IMAGE_SYM_CLASS_CLR_TOKEN";
				}
				return QString().sprintf("%d", item->entry.StorageClass);
			case 5:
				return QString().sprintf("%d", item->entry.NumberOfAuxSymbols);
		}
	}
	return QVariant();
}
