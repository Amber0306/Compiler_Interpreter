#include "Label.h"


Label::Label()
{
	n=next();
	char buffer[6];
	text=itoa(n,buffer,10);
	text="L"+text;
}

Label::~Label()
{
	
}

int Label::next()
{
	return ++_label;
}

int Label::_label=0;