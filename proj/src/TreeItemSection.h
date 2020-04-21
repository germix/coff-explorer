#ifndef TREEITEMSECTION_H
#define TREEITEMSECTION_H
#include "TreeItem.h"

class TreeItemSection : public TreeItem
{
public:
	QString						name;
	COFF_SECTION_HEADER			header;
	QByteArray					data;
	QVector<IMAGE_RELOCATION>	relocations;
public:
	TreeItemSection(TreeItem* parent, const COFF_SECTION_HEADER& hdr);
	~TreeItemSection();
public:
	QIcon getIcon() const;
	QString getLabel() const;
};

#endif // TREEITEMSECTION_H
