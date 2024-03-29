// FulTry.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


#include "pch.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
#define MAXLINE 30
using namespace std;
//////////////////////////
//标识符1，整数2，小数3，字符串4，保留字5，数学运算符6，比较运算符7，逻辑运算符8，分隔符9

string key[14] = { "if","else","while","do","float","string","begin","end","dim","integer","input","output","as","function" };    //保留字
string border[5] = { ";"  , "{" , "}" , "(" , ")" };										  //分隔符 5
string arithmetic[9] = { "+" , "-" , "*" , "/" ,"<" , "<=" , "=" , ">" , ">=" };             //运算符  6
string text;			 //记录标识符 1
string detail[MAXLINE];              //保存从文件读取的内容

int i = 0;			//i为字符游标
int templine = 0;

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
				text = detail[line][i]; i++; return 0;
			}

	return 0;

}


int main()
{
	ifstream infile("test.txt", ios::in);
	if (infile)
		cout << "文件读取成功! " << endl;
	else
		cout << "文件读取失败!" << endl;

	int hang, mode, k = 1, numline;  //k用于定位行数
	cout << endl;
	cout << "测试数据如下：" << endl;
	while (getline(infile, detail[k]))
	{
		cout << detail[k] << endl;
		k++;
	}
	numline = k--;   //numline记录了文件总行数
	cout << endl;
	cout << "词法分析结果：" << endl;

	for (k = 1; k <= numline; k++)
	{
		while (i != detail[k].length())
		{
			mode = scan(detail[k], k);
			if (mode != 0 && mode != -1)
				cout << " 行数：" << k << " 列数：" << i - text.length() + 1 << "  类别：" << mode << "  单词：" << text << endl;
			else
				if (mode == 0)
				{
					if (i < detail[k].length()) i++;
				}	//如果为行注释 直接跳到下一行
				else
					if (mode == -1)			//如果为块注释 找回行号
						k = templine;
		}
		i = 0;		//一行结束定位到下一行行头
	}
	getchar();
	return 0;
}

