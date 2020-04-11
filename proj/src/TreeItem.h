#ifndef TREEITEM_H
#define TREEITEM_H
#include <QIcon>
#include <QVector>
#include <QByteArray>
#include "coff.h"

enum TREEITEM_TYPE
{
	TREEITEM_TYPE_ROOT,
	TREEITEM_TYPE_FOLDER,
	TREEITEM_TYPE_FILE_HEADER,
	TREEITEM_TYPE_SECTION_HEADER,
	TREEITEM_TYPE_SYMBOL_TABLE,
	TREEITEM_TYPE_STRING_TABLE,
};

class TreeItem
{
public:
	TREEITEM_TYPE		type;
	TreeItem*			parent;
	QVector<TreeItem*>	children;
public:
	TreeItem(TREEITEM_TYPE t, TreeItem* p);
	virtual ~TreeItem();
public:
	virtual QIcon getIcon() const = 0;
	virtual QString getLabel() const = 0;
};

#endif // TREEITEM_H
