#include <string>
using namespace std;

class Goto
{
public:
	static int lookUp(char v,int s);
private:
	Goto();
	~Goto();
	static int Table[54][9];
	static string vs;
};
