// yac.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <stack>
#include <queue>
#include <cstdlib>
#include <sstream>
#define MAXLINE 30
using namespace std;
//////////////////////////
//标识符1，整数2，小数3，字符串4，保留字5，数学运算符6，比较运算符7，逻辑运算符8，分隔符9

string key[14] = { "if","else","while","do","float","string","begin","end","def","integer","input","output","as","function" };    //保留字
string border[5] = { ";"  , "{" , "}" , "(" , ")" };										  //分隔符 5
string arithmetic[9] = { "+" , "-" , "*" , "/" ,"<" , "<=" , "=" , ">" , ">=" };             //运算符  6
string text;			 //记录标识符 1
string detail[MAXLINE];              //保存从文件读取的内容
string result[MAXLINE] = { "t1","t2","t3","t4","t5","t6","t7","t8","t9","t10" };

//**********************************************************************************************************************



int i = 0, k = 1, numline, mode;			//i为字符游标,k为行号,numline记录了文件总行数
int templine = 0;
int errornum = 0;
int warningnum = 0;
int r = 0, serial = 1;
string op, v1, v2, res;

struct Token
{
	string value;	  //值
	int mode;		  //类型
	int row;		      //行
	int col;		      //列
}token;

struct Symtable    //符号表结构
{
	string name;
	int type;
	bool value;
}S;

struct Quaternary//四元式结构
{
	int serial;
	string op;
	string v1;
	string v2;
	string result;
}Q;

Quaternary Quaternary_generater(int serial, string op, string v1, string v2, string result);		//函数声明

vector<Symtable> ST;
vector<Symtable> ::iterator it;
vector<Quaternary> QV;
vector<Quaternary> ::iterator it2;
stack<string> operator_stack;		//操作数堆栈
stack<string> operand_stack;		//操作符堆栈


struct compare : binary_function<Symtable, string, bool>  //仿函数和绑定器
{
	bool operator()(Symtable s, string str) const
	{
		if (s.name == str)
			return true;
		else
			return false;
	}
};

void push_in_token(Token token)  //进表操作
{
	S.name = token.value;
	S.type = -1;
	S.value = false;
	ST.push_back(S);
}

vector<Symtable> ::iterator find_token(Token token)  //查表操作
{
	it = find_if(ST.begin(), ST.end(), bind2nd(compare(), token.value));
	return it;
}


int scan(string s, int line)
{
	int j, flag = 0;
	text = "";          //赋空text
	while (detail[line][i] == ' ')						//判断空格
		i++;		//是空格跳过
	if ((detail[line][i] >= 65 && detail[line][i] <= 90) || (detail[line][i] >= 91 && detail[line][i] <= 122))   //判断是否为字母或者下划线
	{
		text += detail[line][i]; i++;
		while ((detail[line][i] >= 65 && detail[line][i] <= 90) || (detail[line][i] >= 91 && detail[line][i] <= 122) || detail[line][i] >= '0' && detail[line][i] <= '9')   //判断是否为数字或者字母或者下划线
		{
			text += detail[line][i]; i++;
		}
		for (j = 0; j <= 13; j++)
			if (text == key[j])			//查表判断是否为保留字
				return 5;
		if (text == "and" || text == "or")		//判断是否为逻辑运算符
			return 8;
		if (j == 14)
			return 1;				//若查表失败说明为标识符
	}
	else
	{
		while (detail[line][i] >= '0' && detail[line][i] <= '9')					//判断是否为数字
		{
			text += detail[line][i]; i++; flag = 1;
		}
		if (flag == 1)
		{
			if (detail[line][i] == '.')
			{
				text += detail[line][i]; i++;
				while (detail[line][i] >= '0' && detail[line][i] <= '9')					//判断是否为数字
				{
					text += detail[line][i]; i++;
				}
				return 2;   //整数
			}
			return 3;	//小数
		}
	}
	if (detail[line][i] == ';' || detail[line][i] == '{' || detail[line][i] == '}' || detail[line][i] == '(' || detail[line][i] == ')' || detail[line][i] == ',')	//判断是否为分隔符
	{
		text = detail[line][i]; i++; return 9;
	}


	if (detail[line][i] == '+' || detail[line][i] == '-' || detail[line][i] == '*' || detail[line][i] == '=')		//判断是否为运算符
	{
		text = detail[line][i]; i++; return 6;
	}

	if (detail[line][i] == '<' || detail[line][i] == '>')
		if (detail[line][i + 1] == '=')
		{
			text = detail[line][i]; text += detail[line][i + 1]; i = i + 2; return 7;
		}
		else
		{
			text = detail[line][i]; i++; return 7;
		}
	if (detail[line][i] == '“')   //判断是否为字符串
	{
		text += detail[line][i]; i++;
		while (detail[line][i] != '”')
			text += detail[line][i]; i++;
		text += detail[line][i]; i++;
		return 4;
	}
	if (detail[line][i] == '/')					//判断是否为注释
		if (detail[line][i + 1] == '/')
		{
			i = detail[line].length(); return 0;
		}		//如果为行注释那么游标指向行末
		else
			if (detail[line][i + 1] == '*')
			{
				i = i + 2;
				while (detail[line][i] != '*' || detail[line][i + 1] != '/')
					if (i == detail[line].length())
					{
						line++; i = 0;
					}
					else
						i++;
				i = i + 2; templine = line; return -1;   //-1代表块注释
			}
			else
			{
				text = detail[line][i]; i++; return 6;
			}		//说明是除号
//{ text = detail[line][i];i++; return 0;}

	return 0;

}

Token getToken() //该函数用于取字符
{

	for (; k <= numline; k++)
	{
		while (i != detail[k].length())
		{
			mode = scan(detail[k], k);
			if (mode != 0 && mode != -1)
			{
				token.value = text;
				token.mode = mode;
				token.row = k;
				token.col = i - text.length() + 1;
				return token;
			}
			else
				if (mode == 0)
				{
					if (i < detail[k].length()) i++;
				}	//如果为行注释 直接跳到下一行
				else
					if (mode == -1)			//如果为块注释 找回行号
						k = templine;
		}
		i = 0;	
	}
	token.value = "EOF";
	return token;
}

int main()
{
	string filename;
	ifstream infile("test.txt", ios::in);
	if (infile)
		cout << "文件读取成功! " << endl;
	else
		cout << "文件读取失败!" << endl;

	int hang, mode, k = 1;  //k用于定位行数
	cout << endl;
	cout << "测试数据如下：" << endl;
	while (getline(infile, detail[k]))
	{
		cout << detail[k] << endl;
		k++;
	}
	numline = k--;   //numline记录了文件总行数
	cout << endl;
	cout << "语法分析结果：" << endl;

	procedure();
	if (warningnum)
		cout << "warning: " << warningnum;
	if (errornum)
		cout << "  error: " << errornum << endl;
	else
		cout << "编译成功！" << endl;
	cout << endl;
	if (!errornum)
	{
		cout << "四元式如下：" << endl;
		Quaternary_maker();
		Quaternary_print();
	}
	getchar();
	return 0;
}

void error(Token token, const char *msg)           //编译错误处理函数
{
	cout << "编译错误："; printf("%s", msg); cout << endl << "错误位置：第" << token.row << "行，第" << token.col << "列 -> " << token.value;
	cout << endl; cout << endl;
	errornum++;
}

void warning(Token token, const char *msg)           //警告错误处理函数
{
	cout << "警告错误："; printf("%s", msg); cout << endl << "警告位置：第" << token.row << "行，第" << token.col << "列 -> " << token.value;
	cout << endl; cout << endl;
	warningnum++;
}

void procedure()
{
	token = getToken();
	funcBlock();
}

void funcBlock()
{
	func();
	while (token.value == "function")
	{
		func();
	}
}

void func()
{
	if (token.value == "function")
		token = getToken();
	else
		error(token, "缺少函数声明标志或函数声明标志不正确");
	if (token.mode == 1)
		token = getToken();
	else
		error(token, "函数名不正确");
	if (token.value == "(")
		token = getToken();
	else
		error(token, "函数名后应出现左括号");
	if (token.value == ")")
		token = getToken();
	else
		error(token, "函数名后应出现右括号");
	stateBLOCK();
	if (token.value == "end")
		token = getToken();
	else
		error(token, "缺少函数结束符end");
	if (token.value == "function")
		token = getToken();
	else
		error(token, "缺少关键字function");
}

void stateBLOCK()
{
	if (token.value == "begin")
		token = getToken();
	else
		error(token, "缺少关键字begin");
	state();
	while (token.value == "def" || token.value == "while" || token.value == "input" || token.value == "output" || token.value == "if" || token.mode == 1)
		state();
	if (token.value == "end")
		token = getToken();
	else
		error(token, "缺少语句块结束符end");
}

void state()
{
	if (token.value == "def")
		stateVarible();
	if (token.value == "while")
		stateLoop();
	if (token.value == "input")
		stateIn();
	if (token.value == "output")
		stateOut();
	if (token.mode == 1)
		stateGive();
	if (token.value == "if")
		stateBranch();
}

void stateVarible()
{
	if (token.value == "def")
		token = getToken();
	else
		error(token, "缺少关键字def");
	if (token.mode == 1)
	{
		/////////////////////////////////////////以下是语义分析
		it = find_token(token);
		if (it == ST.end())		//没有找到
			push_in_token(token);		//进表
		else
			warning(token, "变量重复定义");
		token = getToken();
	}
	else
		error(token, "标识符错误");
	while (token.value == ",")
	{
		token = getToken();
		if (token.mode == 1)
		{
			/////////////////////////////////////////以下是语义分析
			it = find_token(token);
			if (it == ST.end())		//没有找到
				push_in_token(token);		//进表
			else
				warning(token, "变量重复定义");
			token = getToken();
		}
		else
			error(token, "标识符错误");
	}
	if (token.value == "as")
		token = getToken();
	else
		error(token, "缺少关键字as");
	dataType();
	if (token.value == ";")
		token = getToken();
	else
		error(token, "缺少分号");
}

void dataType()
{
	if (token.value == "integer" || token.value == "float" || token.value == "string")
		token = getToken();
	else
		warning(token, "数据类型定义错误");
	for (it = ST.begin(); it != ST.end(); it++)
		if ((*it).type == -1)		//若变量未定义
		{
			if (token.value == "integer")
				(*it).type = 1;		//1为整数，2为小数，3为字符串
			else
				if (token.value == "float")
					(*it).type = 2;
				else
					(*it).type = 3;
			(*it).value = true;
		}
}

void stateIn()
{
	if (token.value == "input")
		token = getToken();
	else
		error(token, "缺少input关键字");
	if (token.mode == 1)
	{
		it = find_token(token);		//语义分析
		if (it == ST.end())		//没找到
			error(token, "变量未定义就使用");
		token = getToken();
	}
	else
		error(token, "标识符错误");
	while (token.value == ",")
	{
		token = getToken();
		if (token.mode == 1)
			token = getToken();
		else
			error(token, "标识符错误");
	}
	if (token.value == ";")
		token = getToken();
	else
		error(token, "缺少分号");
}

void stateOut()
{
	if (token.value == "output")
		token = getToken();
	else
		error(token, "缺少output关键字");
	expression();
	while (token.value == ",")
	{
		token = getToken();
		expression();
	}
	if (token.value == ";")
		token = getToken();
	else
		error(token, "缺少分号");
}

void stateGive()
{
	if (token.mode == 1)
	{
		it = find_token(token);		//语义分析
		if (it == ST.end())		//没找到
			error(token, "变量未定义就使用");
		else
			if ((*it).value == false)
				warning(token, "变量未赋值就引用");
		operand_stack.push(token.value);
		token = getToken();
	}
	else
		error(token, "标识符错误");
	if (token.value == "=")
	{
		operator_stack.push(token.value);
		token = getToken();
	}
	else
		error(token, "缺少等于号");
	expression();
	if (token.value == ";")
	{
		token = getToken(); Quaternary_maker();
	}
	else
		error(token, "缺少分号");
}

void stateBranch()
{
	if (token.value == "if")
	{
		token = getToken();
		//operand_stack.push( token.value  );
	}
	else
		error(token, "缺少if关键字");
	boolExp();
	stateBLOCK();
	if (token.value == "else")
	{
		token = getToken();
		stateBLOCK();
	}
}

void stateLoop()
{
	if (token.value == "while")
		token = getToken();
	else
		error(token, "缺少while关键字");
	boolExp();
	if (token.value == "do")
		token = getToken();
	else
		error(token, "缺少do关键字");
	stateBLOCK();
}

////////////////////////////////////////////////////
//算数符号优先级：*/  >  +-  >  =
void expression()
{
	item();
	while (token.value == "+" || token.value == "-")
	{
		///////////////////////////////////////////////四元式
		while (!operator_stack.empty() && operator_stack.top() != "=")		//此处要注意用while循环，if会出错，因为需要不断判断直至栈顶的符号优先级小于需要压栈的符号
		{
			op = operator_stack.top();
			operator_stack.pop();
			v1 = operand_stack.top();
			operand_stack.pop();
			v2 = operand_stack.top();
			operand_stack.pop();
			res = result[r]; r++;
			Q = Quaternary_generater(serial, op, v1, v2, res); serial++;
			QV.push_back(Q);
			operand_stack.push(res);
			for (it2 = QV.begin(); it2 != QV.end(); it2++)			//找回真出口
				if ((*it2).result == "null")
				{
					stringstream ss;
					ss << QV.back().serial;
					string   s = ss.str();
					(*it2).result = s;
					break;
				}
		}
		operator_stack.push(token.value);					//如果栈空或者准备进栈的符号的优先级大于栈顶的优先级则进栈
		token = getToken();
		item();
	}
}

void item()
{
	factor();
	while (token.value == "*" || token.value == "/")
	{
		operator_stack.push(token.value);
		token = getToken();
		factor();
	}
}

void factor()
{
	if (token.mode == 1 || token.mode == 2 || token.mode == 3)
	{
		if (token.mode == 1)
		{
			it = find_token(token);		//语义分析
			if (it == ST.end())		//没找到
				error(token, "变量未定义就使用");
		}
		operand_stack.push(token.value);
		token = getToken();
	}
	else
	{
		if (token.value == "(")
			token = getToken();
		else
			error(token, "缺少左括号");
		expression();
		if (token.value == ")")
			token = getToken();
		else
			error(token, "缺少右括号");
	}

}

void boolExp()
{
	relationExp();
	while (token.value == "and" || token.value == "or")
	{
		token = getToken();
		boolExp();
	}
}

void relationExp()
{
	expression();
	relation();
	expression();
	////////////////////////////////////////
	//布尔表达式四元式生成
	op = operator_stack.top();
	operator_stack.pop();
	v1 = operand_stack.top();
	operand_stack.pop();
	v2 = operand_stack.top();
	operand_stack.pop();
	res = "null";
	Q = Quaternary_generater(serial, op, v1, v2, res); serial++;		//res现在还未知,出口为真
	QV.push_back(Q);
	Q = Quaternary_generater(serial, "j", "-", "-", res); serial++;	//出口为假
	QV.push_back(Q);
}

void relation()
{
	if (token.mode == 7)
	{
		operator_stack.push(token.value);		//关系判断符号进栈
		token = getToken();
	}
	else
	{///////////////////////////////////////////////////关键字规则
		error(token, "关系运算符错误");
		for (i = 0; i <= 13; i++)
			if (text == key[i])			//查表判断是否为保留字
				break;
	}
}

Quaternary Quaternary_generater(int serial, string op, string v1, string v2, string result)		//四元式生成函数
{
	Q.serial = serial;
	Q.op = op;
	Q.v1 = v1;
	Q.v2 = v2;
	Q.result = result;
	return Q;
}

void Quaternary_maker()
{
	while (!operand_stack.empty() && !operator_stack.empty())
	{
		op = operator_stack.top();
		operator_stack.pop();
		v1 = operand_stack.top();
		operand_stack.pop();
		v2 = operand_stack.top();
		operand_stack.pop();
		res = result[r]; r++;
		Q = Quaternary_generater(serial, op, v1, v2, res); serial++;
		QV.push_back(Q);
		////////////////
		for (it2 = QV.begin(); it2 != QV.end(); it2++)			//找回真出口
			if ((*it2).result == "null")
			{
				stringstream ss;
				ss << QV.back().serial;
				string   s = ss.str();
				(*it2).result = s;
				break;
			}
		///////////////
		operand_stack.push(res);
	}
}

void Quaternary_print()
{
	while (!QV.empty())
	{
		cout << QV.front().serial << " ( " << QV.front().op << " , " << QV.front().v2 << " , " << QV.front().v1 << " , " << QV.front().result << " ) " << endl;
		it2 = QV.begin();
		QV.erase(it2);
	}
}
