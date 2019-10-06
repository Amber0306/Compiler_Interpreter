#include <string>

#include "Gloab.h"
using namespace std;

class Symbol  
{
public:
	int line;
	string word;
	char group;
	TokenGroup  type;
	int  truelist;
	int  falselist;
	int  nextlist;
	Symbol();
	Symbol(const Symbol &b);
	virtual ~Symbol();
	operator =(const Symbol &b);
	string code;
	//void loadSymbol(TokenGroup tg);
};