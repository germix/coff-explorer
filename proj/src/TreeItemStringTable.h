#ifndef TREEITEMSTRINGTABLE_H
#define TREEITEMSTRINGTABLE_H
#include "TreeItem.h"
#include <QVector>

class TreeItemStringTable : public TreeItem
{
public:
	QVector<QString> strings;
public:
	TreeItemStringTable(TreeItem* parent);
	~TreeItemStringTable();
public:
	QIcon getIcon() const;
	QString getLabel() const;
};

#endif // TREEITEMSTRINGTABLE_H
