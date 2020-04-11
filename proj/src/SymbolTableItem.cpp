#include "SymbolTableItem.h"

SymbolTableItem::SymbolTableItem(const COFF_SYMBOL& e)
	: entry(e)
{
}

SymbolTableItem::~SymbolTableItem()
{
}
