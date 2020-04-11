#include "TreeItemSection.h"

TreeItemSection::TreeItemSection(TreeItem* parent, const COFF_SECTION_HEADER& hdr)
	: TreeItem(TREEITEM_TYPE_SECTION_HEADER, parent)
{
	header = hdr;
	char s[8+1];
	strncpy(s, hdr.Name, 8);
	s[8] = 0;
	name = s;
}

TreeItemSection::~TreeItemSection()
{
}

QIcon TreeItemSection::getIcon() const
{
	return QIcon(":/images/tree-item-section-header.png");
}

QString TreeItemSection::getLabel() const
{
	return name;
}
