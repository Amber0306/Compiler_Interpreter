#include <string>
using namespace std;

class Action
{
public:
	static int lookUp(char v,int s);
private:
	Action();
	~Action();
	static int Table[54][19];
	static string vs;
};