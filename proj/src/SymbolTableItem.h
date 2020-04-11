#ifndef SYMBOLTABLEITEM_H
#define SYMBOLTABLEITEM_H
#include "coff.h"
#include <QString>

class SymbolTableItem
{
public:
	QString			name;
	COFF_SYMBOL		entry;
public:
	SymbolTableItem(const COFF_SYMBOL& e);
	~SymbolTableItem();
};

#endif // SYMBOLTABLEITEM_H
