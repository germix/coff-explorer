#include "TreeItemSymbolTable.h"

TreeItemSymbolTable::TreeItemSymbolTable(TreeItem* parent)
	: TreeItem(TREEITEM_TYPE_SYMBOL_TABLE, parent)
{
}

TreeItemSymbolTable::~TreeItemSymbolTable()
{
}

QIcon TreeItemSymbolTable::getIcon() const
{
	return QIcon(":/images/tree-item-symbol-table.png");
}

QString TreeItemSymbolTable::getLabel() const
{
	return "Symbol table";
}
