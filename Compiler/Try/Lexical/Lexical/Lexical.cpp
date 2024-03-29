// Lexical.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<fstream>
using namespace std;

void f_save();
void f_delete();
void f_change();
void f_add();

char srcstr;
ofstream out("test1.txt", ios::binary);
int main()
{
	ifstream in("test.txt", ios::in | ios::binary);
	char ch_in, ch_in_Type;
	int S_B = 0, S_A = 0;
	int State_Trans_Table[6][5] = { {0,1,2,0,1},{0,1,2,0,1},{0,0,3,4,0},
					{3,3,3,3,1},{4,4,4,5,4},{4,4,1,4,4} };

	char Ch_Type_Table[128] = { 0 };
	Ch_Type_Table['\r'] = Ch_Type_Table['\n'] = 4;   //'\r','\n'
	Ch_Type_Table['/'] = 2;   //'/'
	Ch_Type_Table['*'] = 3;  //'*'
	Ch_Type_Table[' '] = Ch_Type_Table['\t'] = 1;    //空格，/t


	//返回类型(指针变量名)（参数列表）；定义函数指针
	void(*Action_Table[6][6])(void) = { {f_save,f_change,f_delete,NULL,NULL,NULL},
{f_save,f_delete,f_delete,NULL,NULL,NULL},
{f_add,NULL,NULL,f_delete,f_delete,NULL},
{NULL,f_change,NULL,f_delete,NULL,NULL},
{NULL,NULL,NULL,NULL,f_delete,f_delete},
{NULL,f_change,NULL,NULL,f_delete,NULL} };
	while (in)  //当文件读取没有结束
	{
		S_B = S_A;
		in.get(ch_in);
		srcstr = ch_in;
		ch_in_Type = Ch_Type_Table[ch_in];
		S_A = State_Trans_Table[S_B][ch_in_Type];

		Action_Table[S_B][S_A]();
	}
	out.close();
	in.close();
	return 0;
}
void f_save() {  // f_留
	out << srcstr;
}
void f_delete() {  //f_删
}
void f_change() { // f_改
	out << " ";
}
void f_add() {     //f_补
	out << "/";
	out << " ";
}

