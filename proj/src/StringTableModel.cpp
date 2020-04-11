#include "StringTableModel.h"
#include "TreeItemStringTable.h"

#define MAX_COLUMNS 1

StringTableModel::StringTableModel(QObject* parent)
	: QAbstractItemModel(parent)
	, root(nullptr)
{
}

StringTableModel::~StringTableModel()
{
}

void StringTableModel::setStringTable(TreeItemStringTable* st)
{
	beginResetModel();
	root = st;
	endResetModel();
}

QVariant StringTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
			case 0: return "Name";
		}
	}
	return QVariant();
}

QModelIndex StringTableModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	if(!root || row < 0)
		return QModelIndex();

	if((row >= 0 && row < root->strings.size()) && (column >= 0 && column < MAX_COLUMNS))
	{
		return createIndex(row, column);
	}
	return QModelIndex();
}

QModelIndex StringTableModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	return QModelIndex();
}

int StringTableModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	if(!root)
		return 0;
	if(!parent.isValid())
		return root->strings.count();
	return 0;
}

int StringTableModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return MAX_COLUMNS;
}

QVariant StringTableModel::data(const QModelIndex& index, int role) const
{
	if(role == Qt::DisplayRole)
	{
		QString name = root->strings[index.row()];

		switch(index.column())
		{
			case 0:
				return name;
		}
	}
	return QVariant();
}
