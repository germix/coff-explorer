#include "TreeItem.h"

TreeItem::TreeItem(TREEITEM_TYPE t, TreeItem* p)
	: type(t)
	, parent(p)
{
	if(parent)
		parent->children.append(this);
}

TreeItem::~TreeItem()
{
	for(int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
	children.clear();
}
