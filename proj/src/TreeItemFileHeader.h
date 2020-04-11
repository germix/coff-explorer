#ifndef TREEITEMFILEHEADER_H
#define TREEITEMFILEHEADER_H
#include "TreeItem.h"

class TreeItemFileHeader : public TreeItem
{
public:
	COFF_FILE_HEADER	header;
	QString				fileName;
public:
	TreeItemFileHeader(TreeItem* parent, const QString& fname, const COFF_FILE_HEADER& hdr);
	~TreeItemFileHeader();
public:
	QIcon getIcon() const;
	QString getLabel() const;
};

#endif // TREEITEMFILEHEADER_H
