#include "TreeItemRoot.h"

TreeItemRoot::TreeItemRoot() : TreeItem(TREEITEM_TYPE_ROOT, nullptr)
{
}

TreeItemRoot::~TreeItemRoot()
{
}

QIcon TreeItemRoot::getIcon() const
{
	return QIcon();
}

QString TreeItemRoot::getLabel() const
{
	return QString();
}
