#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include "Symbol.h"
#include "Temp.h"
#include <cstdlib>
#include<sstream>
using namespace std;

#define KEYNUM    6




typedef struct
{
	string word;
	TokenGroup    type;
}Id;


typedef struct
{
	string word;  
	char    group;   //所属类别，简化语法
	int    line;     
} Token;

typedef struct node
{
	string op;
	string p1;
	string p2;
    string res;
	int    next;
	
	//node * next;
}FourTerm;


typedef struct  
{
	string code;
	int    bNum;					//该语句是否要回填
	bool   isBack;               //是否已经加了标号
	int    lNum;
} Mcode;



class Compiler
{
public:
	optimize();
	string code;
	string code1;
	int    tNum;
	char nextChar();
	preProcess();//预处理器
	parser(bool islex);//语法分析器
	//FourTerm* makelist(int line);   // 第line个四元式不知道该往哪跳。
	bool      backPath(int head,int line);
	Token *lexer();//词法分析器
	void emitter();//生成器
	Compiler(string CmdLine);
	virtual ~Compiler();
	err(int no,int line);
	TokenGroup IsKeyword(string m,int num);
	int hasError;							//错误发生状态
	bool IsBackpath(stack<Symbol *> sos);
	int Merge(int line1,int line2);
	void loadSymbol(TokenGroup tg);

	static string intTostr(int num);

	void showFterm(void);

	void saveStack(const string str);

	void reverseStk(stack<int> sss,stack<int> *tsss);
	void reverseStk(stack<Symbol*> soss,stack<Symbol*> *tsoss);

	void saveQuad(Token* ip);

        void addBlank(string* pstr,int n);

	void genMaincode(void);
	void initMaincode(void);
	int strToint(string str);

	void backMaincode(void);

	void loadMaincode(void);
	void creatAsm(void);

	void wriStk(void);

        string fileName;

        ifstream in;//输入CRR文件
	ofstream log;//输出日志文件
	ofstream out;//输出ASM文件
	ofstream mout; //我的ASM文件
        ofstream ftoken; //token 表
        ofstream fft;  //  四元式表
        ofstream fstk; //语法栈文件
        ofstream cmes; //调试信息

        Compiler();
        char currentChar;
	int hasFile;//源文件打开状态

        Token cct[200];

        int line;//行数状态
        void reSet(void);
        bool isClose;

        char  lexErrChar;
        bool  isLexErrId;
        list<Id>       symbolList;
        int     nextquad;

        bool        isClrIn;
        bool    isTokenClose;
        bool    isFtClose;
        bool    isStkClose;
        bool    isAsmClose;
        bool    isLogClose;
private:
	TokenGroup lookup(string m);
	





	int needOutSuppose;//输出支持状态

	//list<string> symbolList;//符号表

	string  keywordstr[10];

	FourTerm ft[100];				//生成的四元式
	Mcode  mainCode[100];

	stack<int> bk;					//用于四元式的回填

	int nlist;						//if(E) S else S

	stack<int> ss;
	stack<Symbol *> sos;

	string stk;
};








 









