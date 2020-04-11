#include "TreeItemFileHeader.h"
#include <QFileInfo>

TreeItemFileHeader::TreeItemFileHeader(TreeItem* parent, const QString& fname, const COFF_FILE_HEADER& hdr)
	: TreeItem(TREEITEM_TYPE_FILE_HEADER, parent)
{
	header = hdr;
	fileName = fname;
}

TreeItemFileHeader::~TreeItemFileHeader()
{
}

QIcon TreeItemFileHeader::getIcon() const
{
	return QIcon(":/images/tree-item-file-header.png");
}

QString TreeItemFileHeader::getLabel() const
{
	return QFileInfo(fileName).fileName();
}
