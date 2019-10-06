%{
#include <stdio.h>
#include <stdlib.h>
#define VOID 1 // void
#define CHAR 2 // char
#define INT 3 // int
#define FLOAT 4 //float
#define DOUBLE 5 // double
#define SHORT 6 // short
#define LONG 7 // long
#define SIGNED 8 // signed
#define UNSINGED 9 //unsigned
#define STRUCT 10 // struct
#define UNION 11 //union
#define ENUM 12 // enum
#define TYPEDF 13 // typedef
#define SIZEOF 14 //sizeof
#define AUTO 15 //auto
#define STATIC 16 // static
#define REGISTER 17 // register
#define EXTERN 18 // extern
#define CONST 19 // const
#define VOLATILE 20 // volatile
#define RETURN 21 // return
#define CONTINUE 22 //continue
#define BREAK 23 // break
#define GOTO 24 //goto
#define IF 25 // if
#define ELSE 26 // else
#define SWITCH 27 // switch
#define CASE 28 // case
#define DEFAULT 29 // default
#define FOR 30 // for
#define DO 31 // do
#define WHILE 32 // while
#define SCANF 33 // scanf
#define PRINTF 34 // printf
#define LC 35 // {
#define RC 36 // }
#define LB 37 // [
#define RB 38 // ]
#define LP 39 // (
#define RP 40 // )
#define DOT 41 // .
#define STRUCTOP 42 // ->
#define LOGRE 43 // ~是否需要
#define INPLUS 44 // ++
#define INMINUS 45 // --
#define LOCRE 46 // !
#define AND 47 // &
#define STAR 48 // *
#define DIVOP 49 // /
#define COMOP 50 // %
#define PLUS 51 // +
#define MINUS 52 // -
#define SHIFTR 53 // >>
#define SHIFTL 54 // <<
#define RELG 55 // >
#define RELGEQ 56 // >=
#define RELL 57 // <
#define RELLEQ 58 // <=
#define EQUOP 59 // ==
#define UEQUOP 60 // !=
#define XOR 61 // ^
#define OR 62 // !
#define ANDAND 63 // &&
#define OROR 64 // ||
#define QUEST 65 // ?
#define EQUAL 66 // =
#define ASSIGNDIV 67 // /=
#define ASSIGNSTAR 68 // *=
#define ASSIGNCOM 69 // %=
#define ASSIGNPLUS 70 // +=
#define ASSIGNMINUS 71 // -=
#define ASSIGNAND 72 // &=
#define ASSIGNXOR 73 // ^=
#define ASSIGNOR 74 // |=
#define COMMA 75 // ,
#define SHA 76 // #
#define SEMI 77 // ;
#define COLON 78 // :
#define ID 79  //标识符
#define NUMBER 80  // 数字
#define QUOTE 81   // '
#define QUOTEDOUBLE 82 // "
%}
delim [" "\n\t]
whitespace {delim}+
digit  [0-9]
letter [A-Za-z]
id  ({letter}|_)({letter}|{digit}|_)*
number  [1-9]{digit}*|0
%%
{whitespace} { /* do nothing*/ }
"/*"[^}\n]*"*/"  ; //删除注释
"//"[^}\n]*  ;     //删除注释
{id} {fprintf(yyout, "(%d, %s)\n", ID, yytext); }
{number} {fprintf(yyout, "(%d, %s)\n", NUMBER, yytext); }
void {fprintf(yyout, "(%d,%s)\n", VOID, yytext); }
char {fprintf(yyout, "(%d,%s)\n", CHAR, yytext); }
int {fprintf(yyout, "(%d,%s)\n", INT, yytext); }
float {fprintf(yyout, "(%d,%s)\n", FLOAT, yytext); }
double {fprintf(yyout, "(%d,%s)\n", DOUBLE, yytext); }
short {fprintf(yyout, "(%d,%s)\n", SHORT, yytext); }
long {fprintf(yyout, "(%d,%s)\n", LONG, yytext); }
signed {fprintf(yyout, "(%d,%s)\n", SIGNED, yytext); }
unsigned {fprintf(yyout, "(%d,%s)\n", UNSINGED, yytext); }
struct {fprintf(yyout, "(%d,%s)\n", STRUCT, yytext); }
union {fprintf(yyout, "(%d,%s)\n", UNION, yytext); }
enum {fprintf(yyout, "(%d,%s)\n", ENUM, yytext); }
typedef {fprintf(yyout, "(%d,%s)\n", TYPEDF, yytext); }
sizeof {fprintf(yyout, "(%d,%s)\n", TYPEDF, yytext); }
auto {fprintf(yyout, "(%d,%s)\n", AUTO, yytext); }
static {fprintf(yyout, "(%d,%s)\n", STATIC, yytext); }
register {fprintf(yyout, "(%d,%s)\n", REGISTER, yytext); }
extern {fprintf(yyout, "(%d,%s)\n", EXTERN, yytext); }
const {fprintf(yyout, "(%d,%s)\n", CONST, yytext); }
volatile {fprintf(yyout, "(%d,%s)\n", VOLATILE, yytext); }
return { fprintf(yyout, "(%d,%s)\n", RETURN, yytext); }
continue {fprintf(yyout, "(%d,%s)\n", CONTINUE, yytext); }
break {fprintf(yyout, "(%d,%s)\n", BREAK, yytext); }
goto {fprintf(yyout, "(%d,%s)\n", GOTO, yytext); }
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
"." {fprintf(yyout, "(%d,%s)\n", DOT, yytext); }
"->" {fprintf(yyout, "(%d,%s)\n", STRUCTOP, yytext); }
"~" {fprintf(yyout, "(%d,%s)\n", LOGRE, yytext); }
"++" {fprintf(yyout, "(%d,%s)\n", INPLUS, yytext); }
"--" {fprintf(yyout, "(%d,%s)\n", INMINUS, yytext); }
"!" {fprintf(yyout, "(%d,%s)\n", LOCRE, yytext); }
"&" {fprintf(yyout, "(%d,%s)\n", AND, yytext); }
"*" {fprintf(yyout, "(%d,%s)\n", STAR, yytext); }
"/" {fprintf(yyout, "(%d,%s)\n", DIVOP, yytext); }
"%" {fprintf(yyout, "(%d,%s)\n", COMOP, yytext); }
"+" {fprintf(yyout, "(%d,%s)\n", PLUS, yytext); }
"-" {fprintf(yyout, "(%d,%s)\n", MINUS, yytext); }
">>" {fprintf(yyout, "(%d,%s)\n", SHIFTR, yytext); }
"<<" {fprintf(yyout, "(%d,%s)\n", SHIFTL, yytext); }
">" {fprintf(yyout, "(%d,%s)\n", RELG, yytext); }
">=" {fprintf(yyout, "(%d,%s)\n", RELGEQ, yytext); }
"<" {fprintf(yyout, "(%d,%s)\n", RELL, yytext); }
"<=" {fprintf(yyout, "(%d,%s)\n", RELLEQ, yytext); }
"==" {fprintf(yyout, "(%d,%s)\n", EQUOP, yytext); }
"!=" {fprintf(yyout, "(%d,%s)\n", UEQUOP, yytext); }
"^" {fprintf(yyout, "(%d,%s)\n", XOR, yytext); }
"|" {fprintf(yyout, "(%d,%s)\n", OR, yytext); }
"&&" {fprintf(yyout, "(%d,%s)\n", ANDAND, yytext); }
"||" {fprintf(yyout, "(%d,%s)\n", OROR, yytext); }
"?" {fprintf(yyout, "(%d,%s)\n", QUEST, yytext); }
"=" {fprintf(yyout, "(%d,%s)\n", EQUAL, yytext); }
"/=" {fprintf(yyout, "(%d,%s)\n", ASSIGNDIV, yytext); }
"*=" {fprintf(yyout, "(%d,%s)\n", ASSIGNSTAR, yytext); }
"%=" {fprintf(yyout, "(%d,%s)\n", ASSIGNCOM, yytext); }
"+=" {fprintf(yyout, "(%d,%s)\n", ASSIGNPLUS, yytext); }
"-=" {fprintf(yyout, "(%d,%s)\n", ASSIGNMINUS, yytext); }
"&=" {fprintf(yyout, "(%d,%s)\n", ASSIGNAND, yytext); }
"^=" {fprintf(yyout, "(%d,%s)\n", ASSIGNXOR, yytext); }
"|=" {fprintf(yyout, "(%d,%s)\n", ASSIGNOR, yytext); }
"," {fprintf(yyout, "(%d,%s)\n", COMMA, yytext); }
"#" {fprintf(yyout, "(%d,%s)\n", SHA, yytext); }
";" {fprintf(yyout, "(%d,%s)\n", SEMI, yytext); }
":" {fprintf(yyout, "(%d,%s)\n", COLON, yytext); }
"\"" {fprintf(yyout, "(%d,%s)\n", QUOTEDOUBLE, yytext); }
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
	yyout=fopen("lexical_result.txt","w");
	if(yyin!=NULL)
		return yylex();
}





