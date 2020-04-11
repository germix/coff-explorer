#ifndef TREEITEMFOLDER_H
#define TREEITEMFOLDER_H
#include "TreeItem.h"

class TreeItemFolder : public TreeItem
{
public:
	QString name;
public:
	TreeItemFolder(TreeItem* parent, const QString& name);
	~TreeItemFolder();
public:
	QIcon getIcon() const;
	QString getLabel() const;
};

#endif // TREEITEMFOLDER_H
