%{
#include <stdio.h>
#include <stdlib.h>
#define VOID 1//void
#define INT 2 // int
#define DOUBLE 3 // double
#define RETURN 4 // return
#define BREAK 5 // break
#define IF 6 // if
#define ELSE 7 // else
#define SWITCH 8 // switch
#define CASE 9 // case
#define DEFAULT 10 // default
#define FOR 11 // for
#define DO 12 // do
#define WHILE 13 // while
#define SCANF 14 // scanf
#define PRINTF 15 // printf
#define LC 16 // {
#define RC 17 // }
#define LB 18 // [
#define RB 19 // ]
#define LP 20 // (
#define RP 21// )
#define MODIFY 22 // *
#define DIVOP 23 // /
#define COMOP 24 // %
#define PLUS 25 // +
#define MINUS 26 // -
#define RELG 27 // >
#define RELGEQ 28 // >=
#define RELL 29 // <
#define RELLEQ 30 // <=
#define EQUAL 31 // =
#define EQUOP 32 // ==
#define UEQUOP 33 // !=
#define COMMA 34 // ,
#define SHA 35 // #
#define SEMI 36 // ;
#define ID 37  //标识符
#define NUMBER 38  // 数字
#define QUOTE 39   // '
#define QUOTEDOUBLE 40 // "
%}
delim [" "\n\t]
whitespace {delim}+
digit  [0-9]
letter [A-Za-z]
id  ({letter}|_)({letter}|{digit}|_)*
number  [1-9]{digit}*|0
%%
{whitespace} { /* do nothing*/ }
"//"[^}\n]*  ;     //删除注释
{id} {fprintf(yyout, "(%d,%s)\n", ID, yytext); }
{number} {fprintf(yyout, "(%d,%s)\n", NUMBER, yytext); }
void {fprintf(yyout, "(%d,%s)\n", VOID, yytext); }
int {fprintf(yyout, "(%d,%s)\n", INT, yytext); }
double {fprintf(yyout, "(%d,%s)\n", DOUBLE, yytext); }
return { fprintf(yyout, "(%d,%s)\n", RETURN, yytext); }
break {fprintf(yyout, "(%d,%s)\n", BREAK, yytext); }
if {fprintf(yyout, "(%d,%s)\n", IF, yytext); }
else { fprintf(yyout, "(%d,%s)\n", ELSE, yytext); }
switch {fprintf(yyout, "(%d,%s)\n", SWITCH, yytext); }
case {fprintf(yyout, "(%d,%s)\n", CASE, yytext); }
default {fprintf(yyout, "(%d,%s)\n", DEFAULT, yytext); }
for {fprintf(yyout, "(%d,%s)\n", FOR, yytext); }
do { fprintf(yyout, "(%d,%s)\n", DO, yytext); }
while {fprintf(yyout, "(%d,%s)\n", WHILE, yytext); }
scanf {fprintf(yyout, "(%d,%s)\n", SCANF, yytext); }
printf {fprintf(yyout, "(%d,%s)\n", PRINTF, yytext); }
"{" {fprintf(yyout, "(%d,%s)\n", LC, yytext); }
"}" {fprintf(yyout, "(%d,%s)\n", RC, yytext); }
"[" {fprintf(yyout, "(%d,%s)\n", LB, yytext); }
"]" {fprintf(yyout, "(%d,%s)\n", RB, yytext); }
"(" {fprintf(yyout, "(%d,%s)\n", LP, yytext); }
")" {fprintf(yyout, "(%d,%s)\n", RP, yytext); }
"*" {fprintf(yyout, "(%d,%s)\n", MODIFY, yytext); }
"/" {fprintf(yyout, "(%d,%s)\n", DIVOP, yytext); }
"%" {fprintf(yyout, "(%d,%s)\n", COMOP, yytext); }
"+" {fprintf(yyout, "(%d,%s)\n", PLUS, yytext); }
"-" {fprintf(yyout, "(%d,%s)\n", MINUS, yytext); }
">" {fprintf(yyout, "(%d,%s)\n", RELG, yytext); }
">=" {fprintf(yyout, "(%d,%s)\n", RELGEQ, yytext); }
"<" {fprintf(yyout, "(%d,%s)\n", RELL, yytext); }
"<=" {fprintf(yyout, "(%d,%s)\n", RELLEQ, yytext); }
"==" {fprintf(yyout, "(%d,%s)\n", EQUOP, yytext); }
"!=" {fprintf(yyout, "(%d,%s)\n", UEQUOP, yytext); }
"=" {fprintf(yyout, "(%d,%s)\n", EQUAL, yytext); }
"," {fprintf(yyout, "(%d,%s)\n", COMMA, yytext); }
"#" {fprintf(yyout, "(%d,%s)\n", SHA, yytext); }
";" {fprintf(yyout, "(%d,%s)\n", SEMI, yytext); }
"'"  {fprintf(yyout, "(%d,%s)\n", QUOTE, yytext); }
. {fprintf(yyout, "Unrecognized character: %s\n", yytext); }
%%
int yywrap(void)
{
	return 1;
}
main()
{	
	yyin=fopen("text.txt","r");
	yyout=fopen("result.txt","w");
	if(yyin!=NULL)
		return yylex();
}





