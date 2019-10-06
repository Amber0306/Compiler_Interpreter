// GrammarTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"string.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;
struct product
{
	int length;/*产生式右部的文法符号串的长度*/
	char left;/*产生式左部的非终结符*/
	char right[MaxPLength];/*产生式右部的文法符号串 */
}p[100]; /*产生式结构体*/

struct set {
	int n;/*first和follow 集中元素的个数*/
	char elm[100];
}first[MAX], follow[MAX];/*first 和follow 集结构体*/

char termin[MaxVtNum];/*终结符*/
 char non_termin[MaxVnNum];/*非终结符*/

 int n;/*产生式数量*/
 int VtNum;/*终结符数量*/
 int VnNum;/*非终结符数量*/

 int table[MAX][MAX];
 char wordList[100];

char stack[20] = { '#','Z' };/*对分析機stack赋初值*/
char input[MaxStLength]; /*剩余串 input*/
//char termin[MaxVtNum] = { 'i', '+', '*',  '(',')','#' };/*终结符, 此处将'#'作为终结村处理*/
//char non_termin[MaxVnNum] = { 'E','G','T','H','F' }; /*非终结符*/

struct  product E,T, G, G1, H, H1, F, F1;   /*用来存放各个产生式的结构体变量*/
struct product M[MaxVnNum][MaxVtNum];/*预测分析表*/
int flag = 1;/*当前正在分析字符在输入串中的下标*/
int top = 1;/*分析栈栈顶指针*/
int l;  /*l为输入串长度*/

void change()
{
	for (int q = 0; q < 100; q++)
	{
		wordList[q] = 0;
	}
	fstream openFile("D:\\Amber_project\\Compiler\\frame\\result.txt");
	if (openFile)
	{
		
		int i = 0;
		string mid;
		while (getline(openFile, mid))
		{
			fstream newFile("D:\\Amber_project\\Compiler\\frame\\1.txt", ios::trunc);
			newFile << mid;
			string str;
			newFile >> str;

			if (str == "(80,")
			{
				wordList[i] = 'n';
			}
			else if (str == "(79,")
			{
				wordList[i] = 'i';
			}
			else if (str == "(3,int)")
			{
				wordList[i] = 't';
			}
			else if (str == "(5,double)")
			{
				wordList[i] = 'd';
			}
			else if (str == "(4,float)")
			{
				wordList[i] = 'f';
			}
			else if (str == "(7,long)")
			{
				wordList[i] = 'l';
			}
			else if (str == "(10,struct)")
			{
				wordList[i] = 's';
			}
			else if (str == "(35,{)")
			{
				wordList[i] = '{';
			}
			else if (str == "(36,})")
			{
				wordList[i] = '}';
			}
			else if (str == "(77,;)")
			{
				wordList[i] = ';';
			}
			i++;
		}
		openFile.close();
	}
	else
	{
		cout << " open Error";
	}
	int p = 0;
	while (wordList[p] != 0)
	{
		cout << wordList[p];
		p++;
	}
	/*
	string s = NULL;
	int j = 0;
	while(wordList[j]!=NULL)
	{
		s = s + wordList[j];
	}
	return s;
	*/
}


/*判断是否为终结符*/
inline bool isterminal(char x)
{
	if (x >= 'A'&&x <= 'Z') return false;
	return true;
}

/*判断符号x是否出现过*/
bool exist(char x)
{
	int i;
	if (isterminal(x))
	{
		for (i = 1; i <= VtNum; i++)
			if (termin[i] == x) return true;
		return false;
	}
	for (i = 1; i <= VnNum; i++)
		if (non_termin[i] == x) return true;
	return false;
}
		//读入文法
void read()
{
	int i, j, k;
	char tmp[25];

	cout << "输入产生式的数量:";
	cin >> n;
	cout << "输入形如A->abc的产生式，其中～表示空:\n";
	for (VnNum = VtNum = 0, i = 0; i <= n; i++)
	{
		//string str;
		cin.getline(tmp, 25);

		p[i].left = tmp[0];
		if (!exist(tmp[0]))  non_termin[++VnNum] = tmp[0];
		for (k = 0, j = 3; tmp[j]; j++)
		{
			p[i].right[k++] = tmp[j];
			if (isterminal(tmp[j]))
				if (!exist(tmp[j]))termin[++VtNum] = tmp[j];
				else
					if (!exist(tmp[j]))non_termin[++VnNum] = tmp[j];
		}
		p[i].right[k] = 0;
		p[i].length = k - 1;
	}
	termin[++VtNum] = non_termin[++VnNum] = '#';
}

/*输出用户所输入的文法*/
void show()
{
	int i;
	cout << "用户所输入的产生式为:\n";
	for (i = 1; i <= n; i++)
		cout << "(" << i << ") " << p[i].left << "->" << p[i].right << endl;
}

/*把符号x变为对应的编号*/
int char_id(char x)
{
	int i;
	if (!isterminal(x))
	{
		for (i = 1; i <= VnNum; i++)
			if (non_termin[i] == x) return i;
	}
	for (i = 1; i <= VtNum; i++)
		if (termin[i] == x) return i + 1000;
	return-1;
}


/*判断符号idt是否在集合st里面 */				
bool in(struct set &st, char id)
{
	int i;
	for (i = 1; i <= st.n; i++)
		if (st.elm[i] == id)
			return true;
	return false;
}

/*把符号e添加到集合st里面*/
void add(struct set &st, char e)
{
	st.n++;
	st.elm[st.n] = e;
}

/*求first集*/
void compute_first()
{
	int i, j, k, idl, idr;
	bool inc;
	inc = true;
	while (inc)
	{
		inc = false;
		for (i = 1; i <= n; i++)//遍历所有产生式
		{
			idl = char_id(p[i].left);
			for (j = 0; p[i].right[j]; j++)
			{
				idr = char_id(p[i].right[j]);
				/*如果当前为终结符,并且first[idl]中不包含该终结符,
				  则把此终结符加入first[idl]*/
				if (idr > 1000)
				{
					if (!in(first[idl], p[i].right[j]))
					{
						add(first[idl], p[i].right[j]);
						inc = true;
					}
					break;
				}
				else/*否则把该非终结符first 集里面非空元素加入first[idl]*/
				{
					for (k = 1; k <= first[idr].n; k++)
					{
						if (!in(first[idl], first[idr].elm[k]) && first[idr].elm[k] != '~')
						{
							add(first[idl], first[idr].elm[k]);
							inc = true;
						}
					}
					//}
					if (!in(first[idl], '~'))
						break;
				}
			}
			/*若产生式右部的每一个文法符号都可以推导出空,则'~'应属于first[idl]*/
			if (p[i].right[j] == 0 && !in(first[idl], '~'))
			{
				add(first[idl], '~');
				inc = true;
			}
		}
	}
}

/*输出每个非终极符的first集合*/
	void print_first(struct set *st)
	{
		int i, j;
		puts("\n");
		for (i = 2; i <= VnNum; i++)
		{
			cout << "FIRST" << "(" << non_termin[i] << "):    ";
			for (j = 1; j <= st[i].n; j++)
				cout << st[i].elm[j] << "    "; puts(" ");
		}
	}

/*求FOLLOW集*/
	void compute_follow()
	{
		int i, j, k, idl, idr, idf;
		bool flag, inc = true;
		add(follow[2], '#');/*把结束标志#加入开始符号的FOLLOW集*/
		while (inc)
		{
			inc = false;
			for (i = 1; i <= n; i++)
			{
				idl = char_id(p[i].left);
				for (flag = true, j = p[i].length; j >= 0; j--)
				{
					idr = char_id(p[i].right[j]);
					if (idr > 1000)
					{
						flag = false;
						continue;
					}
					if (flag)
					{
						for (k = 1; k <= follow[idl].n; k++)
						{
							if (!in(follow[idr], follow[idl].elm[k]))
							{
								add(follow[idr], follow[idl].elm[k]);
								inc = true;
							}
						}
					}
					if (j< p[i].length) idf=char_id(p[i].right[j + 1]);
					else continue;
					if (idf > 1000)
					{
						if (!in(follow[idr], p[i].right[j + 1]))
							add(follow[idr], p[i].right[j + 1]);
						continue;
					}
					for (k = 1; k <= first[idf].n; k++)
					{
						if (!in(follow[idr], first[idf].elm[k]) && first[idf].elm[k] != '~')
						{
							add(follow[idr], first[idf].elm[k]); inc = true;
						}
					}
				}
			}
		}
	}

/*输出每个非终极符的 FOLLOW集合*/
		void print_follow(struct set*st)
		{
			int i, j;
			puts("\n");
			for (i = 2; i <= VnNum; i++)
			{
				cout << "FOLLOW" << "(" << non_termin[i] << "): ";
				for (j = 1; j <= st[i].n; j++)
					cout << st[i].elm[j] << "  "; puts(" ");
			}
		}


	

void table_control()
{
	int i, j;
	build_table();
	cout << "\t|\t";
	for (j =3; j <= VtNum; j++)
	{
		if (termin[j] != '~')
			cout << termin[j] << '\t';
	}
	cout << endl;
	for (i = 1; i < VtNum; i++)
		cout << "----\t";
	cout << endl;
	for (i = 2; i < VnNum; i++)
	{
		cout << non_termin[i] << "\t|\t";
		for (j = 3; j < VtNum+1; j++)
		{
			if (termin[j] != '~')
				if (table[i][j] > 0)
					cout << table[i][j] << '\t';
				else
					cout << "error\t";
		}
		cout << endl;
	}
}

void build_table()
{
	int i, j, k, idl, idr, idt;
	char ch;
	bool flag;
	memset(table, 0, sizeof(table));
	table[VnNum][VtNum] = -1;
	for (i =1; i <= n; i++)
	{
		idl = char_id(p[i].left);
		for (j = 0; j <= p[i].length; j++)
		{
			ch = p[i].right[j];
			idr = char_id(ch);
			if (idr > 1000)/*产生式右部的第一个文法符号为终结符,此处仍将空串作为终结符处理*/
			{
				idr -= 1000;
				if (ch != '~')/*产生式右部的第一个文法符号为非空终结符*/
				{
					if (table[idl][idr])
					{
						cout << "It's not a LL(1)language.\n";
						return;
					}
					table[idl][idr] = i;
				}
				else/*产生式右部的第一个文法符号为空*/
				{
					for (k = 1; k <= follow[idl].n; k++)/*将产生式左部文法符号和其FOLLOW集中的所有符号所对应位置都填入该产生式*/
					{
						idt = char_id(follow[idl].elm[k]) - 1000;
						if (table[idl][idt])
						{
							cout << "It's not a LL(1)language.\n";
							return;
						}
						table[idl][idt] = i;
					}
				}
				break;
			}
			/*产生式右部的第一个文法符号为非终结符*/
			for (flag = false, k = 1; k <= first[idr].n; k++)
			{
				idt = char_id(first[idr].elm[k]) - 1000;
				if (first[idr].elm[k] == '~')
					flag = true;
				if (table[idl][idt])
				{
					cout << "It's not a LL(1)language.\n";
					return;
				}
				table[idl][idt] = i;
			}
			if (!flag)
				break;
		}
		if (j > p[i].length)
		{
			for (k = 1; k <= follow[idl].n; k++)
			{
				idt = char_id(follow[idl].elm[k]) - 1000;
				if (table[idl][idt])
				{
					cout << "It's not a LL(1)language.\n";
					return;
				}
				table[idl][idt] = i;
			}
		}
	}
	return;
}

/*
*/
void print_stack()/*输出分析栈*/
{
	int i;/*指計*/
	for (i = 0; i <= top; i++)
		cout << stack[i];
}

void print_input()/*输出剩余串*/
{
	int i;
	for (i = 0; i < flag - 1; i++)/*输出对齐符*/
		cout << " ";
	for (i = flag - 1; i <= l; i++)
		cout << input[i];
}

int non_termin_row(char c)/*非终结符转换为行号*/
{
	int i;
	for (i = 2; i < (int)strlen(non_termin); i++)
		if (c == non_termin[i])
			return i-2;
	cout<<"Error in non_termin_row()>" << c << endl;
	exit(0);
}

int termin_col(char c)/*终结符转换为列号*/
{
	int i;
	for (i = 1; i < (int)strlen(termin); i++)
		if (c == termin[i])
			return i-3;
	cout << "Error in termin_col()>" << c << endl;
	exit(0);
}

bool isNT(char c)/*判断c是否是非终结符*/
{
	int i;
	for (i = 0; i < (int)strlen(non_termin); i++)
		if (c == non_termin[i])
			return true;
	return false;
}

bool isT(char c)/*判断c是否是终结符(不包括'#')*/
{
	int i;
	for (i = 0; i < (int)strlen(termin) - 1; i++)
		if (c == termin[i])
			return true;
	return false;
}


void step_control()
{
	//为使程序运行正常，修改termin 和non_termin
	termin[0] = '$';
	non_termin[0] = '$';
	non_termin[1] = '$';
	int i, j = 0, k = 0;
	int flag2 = 0;
	char ch;
	/*指示输入串的当前字符*/
	char X = ' ';
	/*存储栈顶字符*/
	struct product cha;
	
	for (i = 2; i < MaxVnNum; i++)
	{
		for (j = 3; j < MaxVtNum; j++)
		{
			if (table[i][j] > 0)
			{
				M[i-2][j-3] = p[table[i][j]];
			}
		}

	}
	/*
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 20; j++)
		{
			cout << M[i][j].left<<'\t';
		}
		cout << endl;
	}
	*/

	
	//这里直接用table[][]
	
	cout << "请输入要分析的字符串:";
	change();
	int z = 0;
	j = 0;
	do/*读入分析串*/
	{
		//ch = getchar();
		ch = wordList[z];
		z++;
		//scanf("%c", &ch);
		/*
		if((ch != 'i') && (ch != '+') && (ch != '*')&&(ch!='(')&&(ch!=')')&&(ch!='#'))
		{
			cout << "输入串中有非法字符\n";
			exit(1);
		}*/
		/*
		if(!(isNT(ch)||ch=='#'))
		{
			cout << "输入串中有非法字符\n";
			exit(1);
		}
		*/
		input[k] = ch;
		k++;
	} while (ch != '#');

	l = strlen(input);
	ch = input[0];
	cout << endl;
	cout << "步数\t分析栈\t输入串\t所用规则 \n";
	while (1)
	{
		cout << "\n(" << j++ << ")\t";/*输出当前执行步数*/
		print_stack();/*输出当前栈的内容(出栈前)*/
		cout << "\t";
		print_input();/*输出剩余输出串*/
		cout << "\t";
		if (flag2 == 1)
		{
			cout << cha.left << "->" << cha.right;/*输出产生式*/
			flag2 = 0;
		}
		cout << "\t";
		//出栈
		X = stack[top--];
		if (X == '#')/*如果X是结束符*/
		{
			if (X == ch)
			{
				cout << "\t";
				cout << "ACC" << endl;
			}
			else {
				cout << "\t";
				cout << "ERROR" << endl;
			}
				break;
		}
		else if (isT(X))/*如果X是终结符*/
		{
			ch = input[flag++];
		}
		else if (isNT(X))/*如果X是非终结符*/
		{
			cha = M[non_termin_row(X)][termin_col(ch)];
			flag2 = 1;
			for (i = (cha.length ); i >= 0; i--)/*产生式逆序入栈*/
				stack[++top] = cha.right[i];
			if (stack[top] == '~')/*为空则不进栈*/
				top--;
		}
		else
		{
			cout << "Error in main()>" << X << '\n' << endl;
			exit(0);
		}
	}
}


int main()
{
	
	read();
	show();
	compute_first();
	print_first(first);
	compute_follow();
	print_follow(follow);
	table_control();
	
	step_control();
	return 0;
}



