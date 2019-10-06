CC=g++
CFLAGS=
LEX=flex
YACC=bison
YACCFLAGS=-d
TARGGET=lexyacc

$(TARGGET):lex.yy.c yacc.tab.h yacc.tab.c
	$(CC) $(CFLAGS) lex.yy.c yacc.tab.c -o $(TARGGET)
lex.yy.c:lex.l
yacc.tab.c yacc.tab.h:yacc.y
	$(YACC) $(YACCFLAGS) yacc.y
	
clean:
	rm -f lex.yy.c yacc.tab.h yacc.tab.c