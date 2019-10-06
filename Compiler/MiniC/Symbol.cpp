#include "Symbol.h"

Symbol::Symbol()
{
	truelist = -1;
	falselist = -1;
	nextlist = -1;
	
}

Symbol::Symbol(const Symbol &b)
{
	group=b.group;
	line=b.line;
	word=b.word;
}

Symbol::~Symbol()
{
	
}

Symbol::operator =(const Symbol &b)
{
	group=b.group;
	line=b.line;
	word=b.word;
}




