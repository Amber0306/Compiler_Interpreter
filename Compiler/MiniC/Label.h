#include <string>
//#include <cstdio.h>
//#include <cstdlib.h>
using namespace std;

class Label
{
public:
	Label();
	virtual ~Label();
	string text;
        static int _label;
private:
	int n;
	static int next();
	//static int _label;
};