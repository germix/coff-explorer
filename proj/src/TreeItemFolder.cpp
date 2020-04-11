#include "TreeItemFolder.h"

TreeItemFolder::TreeItemFolder(TreeItem* parent, const QString& n)
	: TreeItem(TREEITEM_TYPE_FOLDER, parent)
	, name(n)
{
}

TreeItemFolder::~TreeItemFolder()
{
}

QIcon TreeItemFolder::getIcon() const
{
	return QIcon(":/images/tree-item-folder.png");
}

QString TreeItemFolder::getLabel() const
{
	return name;
}
