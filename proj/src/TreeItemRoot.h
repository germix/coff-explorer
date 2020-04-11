#ifndef TREEITEMROOT_H
#define TREEITEMROOT_H
#include "TreeItem.h"

class TreeItemRoot : public TreeItem
{
public:
	TreeItemRoot();
	~TreeItemRoot();
public:
	QIcon getIcon() const;
	QString getLabel() const;
};

#endif // TREEITEMROOT_H
