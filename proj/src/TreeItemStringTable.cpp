#include "TreeItemStringTable.h"

TreeItemStringTable::TreeItemStringTable(TreeItem* parent)
	: TreeItem(TREEITEM_TYPE_STRING_TABLE, parent)
{
}

TreeItemStringTable::~TreeItemStringTable()
{
}

QIcon TreeItemStringTable::getIcon() const
{
	return QIcon(":/images/tree-item-string-table.png");
}

QString TreeItemStringTable::getLabel() const
{
	return "String table";
}
