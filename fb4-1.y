
/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb3-2.y,v 2.1 2009/11/08 02:53:18 johnl Exp $
 */
/* calculator with AST */

%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "fb4-1.h"
#  include "expendfunc.h"
extern FILE *yyout;
%}

%union {
  struct ast *a;
  double d;
  struct symbol *s;		/* which symbol */
  int fn;			/* which function */
}

/* declare tokens */
%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC
%token INTT 
%token MAIN



%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%nonassoc lower_then_fenhao
%nonassoc ';'

%type <a> exp stmt list explist

%start calclist

%%
stmt: /* nothing */ { printf("1 ");$$ = NULL; }
   |  list '}' { printf("2 ");$$ = $1; }
   ;

list: /* nothing */ { printf("3 ");$$ = NULL; }
   |  exp ';' list    { printf("4 ");if ($3 == NULL)
	                $$ = $1;
                      else
			$$ = newast('L', $1, $3);
                    }

   ;


exp: exp '+' exp          { printf("5 ");$$ = newast('+', $1,$3); }
   | exp '-' exp          { printf("6 ");$$ = newast('-', $1,$3);}
   | exp '*' exp          { printf("7 ");$$ = newast('*', $1,$3); }
   | exp '/' exp          { printf("8 ");$$ = newast('/', $1,$3); }
   | '|' exp              { printf("9 ");$$ = newast('|', $2, NULL); }
   | '(' exp ')'          { printf("10 ");$$ = $2; }
   | '-' exp %prec UMINUS { printf("11 ");$$ = newast('M', $2, NULL); }
   | NUMBER               { printf("12 ");$$ = newnum($1); }
   | FUNC '(' explist ')' { printf("13 ");$$ = newfunc($1, $3); }
   | NAME                 { printf("14 ");$$ = newref($1); }
   | NAME '=' exp         { printf("15 ");$$ = newasgn($1, $3); }
;

explist: exp
 | exp ',' explist  { printf("16 ");$$ = newast('L', $1, $3); }
;

calclist: /* nothing */{printf("17 ");}
  | calclist INTT MAIN '(' ')' '{' stmt  {
    initt();
    printf("18 ");
    if(debug) dumpast($7, 0);
    else {
     eval($7);
     treefree($7);
     FILE *fwritez = fopen("temp.txt","a+");
     fprintf(fwritez, "\n");
     fclose(fwritez);
     }
    }
  | calclist error { printf("19 ");yyerrok; fprintf(yyout,""); }
 ;
%%