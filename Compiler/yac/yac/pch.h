// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#ifndef PCH_H
#define PCH_H
void procedure();
void funcBlock();
void func();
void stateBLOCK();
void state();
void stateVarible();
void dataType();
void stateIn();
void stateOut();
void stateGive();
void stateBranch();
void stateLoop();
void expression();
void item();
void factor();
void boolExp();
void relationExp();
void relation();
void error();

Quaternary Quaternary_generater(int serial, string op, string v1, string v2, string result);
void Quaternary_print();
void Quaternary_maker();

/*******
<程序>—> <函数块>
<函数块>—> <函数> [ <函数>]
<函数>—> function  id  (  ) <语句块> end  function
<语句块>—> begin  语句 [语句] end
<语句>—><分支语句>|<赋值语句>|<循环语句>|<输入语句>|<输出语句>|<变量定义语句>
<变量定义语句>—> dim id [ , id ] as <数据类型> ；
<数据类型>—> integer | float | string
<输入语句>—> input id  [ ,  id ] ；
<输出语句>—> output <表达式>  [ ,  <表达式> ] ；
<赋值语句>—> id  =  <表达式> ；
<分支语句>—> if  <布尔表达式> <语句块> { else <语句块> }
<循环语句>—> while  <布尔表达式> do <语句块>
<表达式>—> <项> [ +|－ <项> ]
<项>—> <因子> [ *|/  <因子> ]
<因子>—> id | con | deci |  (  <表达式>  )
<布尔表达式>—> <关系表达式> [ and | or  <布尔表达式> ]
<关系表达式>—> <表达式> <关系> <表达式>
<关系>—> < | <= | > | >= | == | <>
*******/
// TODO: 添加要在此处预编译的标头

#endif //PCH_H
