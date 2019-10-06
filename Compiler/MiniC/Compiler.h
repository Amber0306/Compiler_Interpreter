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
	char    group;   //������𣬼��﷨
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
	int    bNum;					//������Ƿ�Ҫ����
	bool   isBack;               //�Ƿ��Ѿ����˱��
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
	preProcess();//Ԥ������
	parser(bool islex);//�﷨������
	//FourTerm* makelist(int line);   // ��line����Ԫʽ��֪������������
	bool      backPath(int head,int line);
	Token *lexer();//�ʷ�������
	void emitter();//������
	Compiler(string CmdLine);
	virtual ~Compiler();
	err(int no,int line);
	TokenGroup IsKeyword(string m,int num);
	int hasError;							//������״̬
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

        ifstream in;//����CRR�ļ�
	ofstream log;//�����־�ļ�
	ofstream out;//���ASM�ļ�
	ofstream mout; //�ҵ�ASM�ļ�
        ofstream ftoken; //token ��
        ofstream fft;  //  ��Ԫʽ��
        ofstream fstk; //�﷨ջ�ļ�
        ofstream cmes; //������Ϣ

        Compiler();
        char currentChar;
	int hasFile;//Դ�ļ���״̬

        Token cct[200];

        int line;//����״̬
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
	





	int needOutSuppose;//���֧��״̬

	//list<string> symbolList;//���ű�

	string  keywordstr[10];

	FourTerm ft[100];				//���ɵ���Ԫʽ
	Mcode  mainCode[100];

	stack<int> bk;					//������Ԫʽ�Ļ���

	int nlist;						//if(E) S else S

	stack<int> ss;
	stack<Symbol *> sos;

	string stk;
};








 









