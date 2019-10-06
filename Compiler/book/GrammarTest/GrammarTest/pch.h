
#ifndef PCH_H
#define PCH_H



// TODO: 添加要在此处预编译的标头
#define MAX 100
#define MaxVtNum 30/*终结符最大的数目*/
#define MaxVnNum 30/*非终结符最大的数目*/
#define MaxPLength 30/*产生式的右部最大长度*/

#define MaxStLength 50/*待分析输入串的最大长度*/



inline bool isterminal(char x);
bool exist(char x);
void read();
void show();
int char_id(char x);
bool in(struct set &st, char id);
void add(struct set &st, char e);
void compute_first();
void print_first(struct set *st);
void compute_follow();
void print_follow(struct set*st);


void table_control();
void build_table();



#endif //PCH_H
