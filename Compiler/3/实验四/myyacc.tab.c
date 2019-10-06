
/*  A Bison parser, made from myyacc.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define alloca

#define	LT	258
#define	LE	259
#define	EQ	260
#define	NE	261
#define	GT	262
#define	GE	263
#define	OR	264
#define	AND	265
#define	NOT	266
#define	INT	267
#define	CHAR	268
#define	BOOL	269
#define	FLOAT	270
#define	ID	271
#define	NUMBER	272
#define	IF	273
#define	ELSE	274
#define	WHILE	275
#define	DO	276
#define	BREAK	277
#define	BASIC	278
#define	TRUE	279
#define	FALSE	280
#define	REAL	281
#define	UMINUS	282
#define	IF_THEN	283

#line 1 "myyacc.y"

/****************************************************************************
myparser.y
ParserWizard generated YACC file.

Date: 2013Äê5ÔÂ25ÈÕ
****************************************************************************/
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "myyacc.tab.h"
int linenum = 1;
void yyerror(const char *msg);
extern double num[1000];
extern char *id[1000];
extern int yylex();

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		89
#define	YYFLAG		32768
#define	YYNTBASE	41

#define YYTRANSLATE(x) ((unsigned)(x) <= 283 ? yytranslate[x] : 57)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
    40,    29,    27,     2,    28,     2,    30,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    35,     2,
    38,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    36,     2,    37,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    33,     2,    34,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    31,    32
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     7,    10,    11,    15,    20,    22,    25,    26,
    31,    37,    45,    51,    59,    62,    64,    69,    71,    75,
    77,    81,    83,    87,    91,    93,    97,   101,   105,   109,
   111,   115,   119,   121,   125,   129,   131,   134,   137,   139,
   143,   145,   147,   149
};

static const short yyrhs[] = {    42,
     0,    33,    43,    46,    34,     0,    43,    44,     0,     0,
    45,    16,    35,     0,    45,    36,    17,    37,     0,    23,
     0,    46,    47,     0,     0,    48,    38,    49,    35,     0,
    18,    39,    49,    40,    47,     0,    18,    39,    49,    40,
    47,    19,    47,     0,    20,    39,    49,    40,    47,     0,
    21,    47,    20,    39,    49,    40,    35,     0,    22,    35,
     0,    42,     0,    48,    36,    49,    37,     0,    16,     0,
    49,     9,    50,     0,    50,     0,    50,    10,    51,     0,
    51,     0,    51,     5,    52,     0,    51,     6,    52,     0,
    52,     0,    53,     3,    53,     0,    53,     4,    53,     0,
    53,     8,    53,     0,    53,     7,    53,     0,    53,     0,
    53,    27,    54,     0,    53,    28,    54,     0,    54,     0,
    54,    29,    55,     0,    54,    30,    55,     0,    55,     0,
    11,    55,     0,    28,    55,     0,    56,     0,    39,    49,
    40,     0,    48,     0,    17,     0,    24,     0,    25,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    37,    39,    41,    42,    44,    46,    47,    62,    63,    65,
    66,    67,    68,    69,    70,    71,    73,    74,    77,    78,
    80,    81,    83,    84,    85,    87,    88,    89,    90,    91,
    94,    95,    96,    98,    99,   100,   102,   103,   104,   106,
   107,   108,   109,   110
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","LT","LE",
"EQ","NE","GT","GE","OR","AND","NOT","INT","CHAR","BOOL","FLOAT","ID","NUMBER",
"IF","ELSE","WHILE","DO","BREAK","BASIC","TRUE","FALSE","REAL","'+'","'-'","'*'",
"'/'","UMINUS","IF_THEN","'{'","'}'","';'","'['","']'","'='","'('","')'","program",
"block","decls","decl","type","stmts","stmt","loc","bool","join","equality",
"rel","expr","term","unary","factor", NULL
};
#endif

static const short yyr1[] = {     0,
    41,    42,    43,    43,    44,    45,    45,    46,    46,    47,
    47,    47,    47,    47,    47,    47,    48,    48,    49,    49,
    50,    50,    51,    51,    51,    52,    52,    52,    52,    52,
    53,    53,    53,    54,    54,    54,    55,    55,    55,    56,
    56,    56,    56,    56
};

static const short yyr2[] = {     0,
     1,     4,     2,     0,     3,     4,     1,     2,     0,     4,
     5,     7,     5,     7,     2,     1,     4,     1,     3,     1,
     3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
     3,     3,     1,     3,     3,     1,     2,     2,     1,     3,
     1,     1,     1,     1
};

static const short yydefact[] = {     0,
     4,     1,     9,     7,     3,     0,     0,     0,     0,    18,
     0,     0,     0,     0,     2,    16,     8,     0,     5,     0,
     0,     0,     0,    15,     0,     0,     6,     0,    42,    43,
    44,     0,     0,    41,     0,    20,    22,    25,    30,    33,
    36,    39,     0,     0,     0,     0,    37,    38,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    17,    10,    40,    19,    11,    21,
    23,    24,    26,    27,    29,    28,    31,    32,    34,    35,
    13,     0,     0,     0,    12,    14,     0,     0,     0
};

static const short yydefgoto[] = {    87,
    16,     3,     5,     6,     7,    17,    34,    35,    36,    37,
    38,    39,    40,    41,    42
};

static const short yypact[] = {   -13,
-32768,-32768,    12,-32768,-32768,   -14,    47,    15,    42,-32768,
    -1,    23,    66,    31,-32768,-32768,-32768,   -15,-32768,    33,
    36,    36,    52,-32768,    36,    36,-32768,    36,-32768,-32768,
-32768,    36,    36,    37,    -6,    64,    25,-32768,    21,    -3,
-32768,-32768,    -4,    38,     3,     2,-32768,-32768,     1,    36,
    66,    36,    36,    36,    36,    36,    36,    36,    36,    36,
    36,    36,    66,    36,-32768,-32768,-32768,    64,    59,    25,
-32768,-32768,    27,    27,    27,    27,    -3,    -3,-32768,-32768,
-32768,     5,    66,    44,-32768,-32768,    83,    85,-32768
};

static const short yypgoto[] = {-32768,
    89,-32768,-32768,-32768,-32768,   -12,    -7,   -18,    40,    39,
   -21,   -39,    -2,   -19,-32768
};


#define	YYLAST		99


static const short yytable[] = {    18,
    23,     8,    50,    43,    50,    18,    45,    46,    47,    50,
    50,    50,    48,    50,    49,    73,    74,    75,    76,     1,
    25,     9,    26,    55,    56,    61,    62,    57,    58,    53,
    54,    71,    72,    51,     4,    63,    66,    21,    69,    65,
    67,    79,    80,    18,    84,    82,    28,    59,    60,    19,
    81,    10,    29,    59,    60,    18,    77,    78,    20,    30,
    31,    22,    10,    32,    11,    24,    12,    13,    14,    27,
    85,    44,    25,    52,    33,    18,    64,    83,    86,     1,
    15,    10,    88,    11,    89,    12,    13,    14,     2,    68,
    70,     0,     0,     0,     0,     0,     0,     0,     1
};

static const short yycheck[] = {     7,
    13,    16,     9,    22,     9,    13,    25,    26,    28,     9,
     9,     9,    32,     9,    33,    55,    56,    57,    58,    33,
    36,    36,    38,     3,     4,    29,    30,     7,     8,     5,
     6,    53,    54,    40,    23,    40,    35,    39,    51,    37,
    40,    61,    62,    51,    40,    64,    11,    27,    28,    35,
    63,    16,    17,    27,    28,    63,    59,    60,    17,    24,
    25,    39,    16,    28,    18,    35,    20,    21,    22,    37,
    83,    20,    36,    10,    39,    83,    39,    19,    35,    33,
    34,    16,     0,    18,     0,    20,    21,    22,     0,    50,
    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 37 "myyacc.y"
{printf("(%d)\tprogram -> block\n",linenum++);;
    break;}
case 2:
#line 39 "myyacc.y"
{printf("(%d)\tblock -> decls stmts\n",linenum++);;
    break;}
case 3:
#line 41 "myyacc.y"
{printf("(%d)\tdecls -> decls decl\n",linenum++);;
    break;}
case 4:
#line 42 "myyacc.y"
{printf("(%d)\tdecls -> e\n",linenum++);;
    break;}
case 5:
#line 44 "myyacc.y"
{printf("(%d)\tdecl -> type %s;\n",linenum++, id[yyvsp[-1]]);;
    break;}
case 6:
#line 46 "myyacc.y"
{printf("(%d)\ttype -> type[num]\n",linenum++);;
    break;}
case 7:
#line 47 "myyacc.y"
{
											switch (yyvsp[0]) 
											{
											case INT:
												printf("(%d)\ttype -> int\n",linenum++);break;
											case CHAR:
												printf("(%d)\ttype -> char\n",linenum++);break;
											case BOOL:
												printf("(%d)\ttype -> bool\n",linenum++);break;
											case FLOAT:
												printf("(%d)\ttype -> float\n",linenum++);break;
											}
										;
    break;}
case 8:
#line 62 "myyacc.y"
{printf("(%d)\tstmts -> stmts stmt\n",linenum++);;
    break;}
case 9:
#line 63 "myyacc.y"
{printf("(%d)\tstmts -> e\n",linenum++);;
    break;}
case 10:
#line 65 "myyacc.y"
{printf("(%d)\tstmt -> loc = bool;\n",linenum++);;
    break;}
case 11:
#line 66 "myyacc.y"
{printf("(%d)\tstmt -> if (bool) stmt\n",linenum++);;
    break;}
case 12:
#line 67 "myyacc.y"
{printf("(%d)\tstmt -> if (bool) stmt else stmt\n",linenum++);;
    break;}
case 13:
#line 68 "myyacc.y"
{printf("(%d)\tstmt -> while (bool) stmt\n",linenum++);;
    break;}
case 14:
#line 69 "myyacc.y"
{printf("(%d)\tstmt -> do stmt while (bool);\n",linenum++);;
    break;}
case 15:
#line 70 "myyacc.y"
{printf("(%d)\tstmt -> break;\n",linenum++);;
    break;}
case 16:
#line 71 "myyacc.y"
{printf("(%d)\tstmt -> block\n",linenum++);;
    break;}
case 17:
#line 73 "myyacc.y"
{printf("(%d)\tloc -> loc [bool]\n",linenum++);;
    break;}
case 18:
#line 74 "myyacc.y"
{printf("(%d)\tloc -> %s\n",linenum++, id[yyvsp[0]]);;
    break;}
case 19:
#line 77 "myyacc.y"
{printf("(%d)\tbool -> bool || join\n",linenum++);;
    break;}
case 20:
#line 78 "myyacc.y"
{printf("(%d)\tbool -> join\n",linenum++);;
    break;}
case 21:
#line 80 "myyacc.y"
{printf("(%d)\tjoin -> join && equality\n",linenum++);;
    break;}
case 22:
#line 81 "myyacc.y"
{printf("(%d)\tjoin -> equality\n",linenum++);;
    break;}
case 23:
#line 83 "myyacc.y"
{printf("(%d)\tequality -> equality == rel\n",linenum++);;
    break;}
case 24:
#line 84 "myyacc.y"
{printf("(%d)\tequality -> equality != rel\n",linenum++);;
    break;}
case 25:
#line 85 "myyacc.y"
{printf("(%d)\tequality -> rel\n",linenum++);;
    break;}
case 26:
#line 87 "myyacc.y"
{printf("(%d)\trel -> expr < expr\n",linenum++);;
    break;}
case 27:
#line 88 "myyacc.y"
{printf("(%d)\trel -> expr <= expr\n",linenum++);;
    break;}
case 28:
#line 89 "myyacc.y"
{printf("(%d)\trel -> expr >= expr\n",linenum++);;
    break;}
case 29:
#line 90 "myyacc.y"
{printf("(%d)\trel -> expr > expr\n",linenum++);;
    break;}
case 30:
#line 91 "myyacc.y"
{printf("(%d)\trel -> expr\n",linenum++);;
    break;}
case 31:
#line 94 "myyacc.y"
{printf("(%d)\texpr -> expr + term\n",linenum++);;
    break;}
case 32:
#line 95 "myyacc.y"
{printf("(%d)\texpr -> expr - term\n",linenum++);;
    break;}
case 33:
#line 96 "myyacc.y"
{printf("(%d)\texpr -> term\n",linenum++);;
    break;}
case 34:
#line 98 "myyacc.y"
{printf("(%d)\tterm -> term * unary\n",linenum++);;
    break;}
case 35:
#line 99 "myyacc.y"
{printf("(%d)\tterm -> term / unary\n",linenum++);;
    break;}
case 36:
#line 100 "myyacc.y"
{printf("(%d)\tterm -> unary\n",linenum++);;
    break;}
case 37:
#line 102 "myyacc.y"
{printf("(%d)\tunary --> ! unary\n",linenum++);;
    break;}
case 38:
#line 103 "myyacc.y"
{printf("(%d)\tunary -> - unary\n",linenum++);;
    break;}
case 39:
#line 104 "myyacc.y"
{printf("(%d)\tunary -> factor\n",linenum++);;
    break;}
case 40:
#line 106 "myyacc.y"
{printf("(%d)\tfactor -> (bool)\n",linenum++);;
    break;}
case 41:
#line 107 "myyacc.y"
{printf("(%d)\tfactor -> loc\n",linenum++);;
    break;}
case 42:
#line 108 "myyacc.y"
{printf("(%d)\tfactor -> %f\n",linenum++, num[yyvsp[0]]);;
    break;}
case 43:
#line 109 "myyacc.y"
{printf("(%d)\tfactor -> true\n",linenum++);;
    break;}
case 44:
#line 110 "myyacc.y"
{printf("(%d)\tfactor -> false\n",linenum++);;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 113 "myyacc.y"


void yyerror(const char *msg)
{ printf("ERROR:%s\n",msg);}

int main(int argc, char *argv[])
{
	return yyparse();
	return 0;
}
