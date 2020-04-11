#ifndef TREEITEMSYMBOLTABLE_H
#define TREEITEMSYMBOLTABLE_H
#include "TreeItem.h"
#include <QVector>

class SymbolTableItem;

class TreeItemSymbolTable : public TreeItem
{
public:
	QVector<SymbolTableItem*> items;
public:
	TreeItemSymbolTable(TreeItem* parent);
	~TreeItemSymbolTable();
public:
	QIcon getIcon() const;
	QString getLabel() const;
};

#endif // TREEITEMSYMBOLTABLE_H
