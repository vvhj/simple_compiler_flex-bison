/* Companion source code for "flex & bison", published by O'Reilly
 * Media, ISBN 978-0-596-15597-1
 * Copyright (c) 2009, Taughannock Networks. All rights reserved.
 * See the README file for license conditions and contact info.
 * $Header: /home/johnl/flnb/code/RCS/fb3-2.l,v 2.1 2009/11/08 02:53:18 johnl Exp $
 */
/* recognize tokens for the calculator */

%option noyywrap nodefault yylineno
%{
# include "fb4-1.h"
# include "fb4-1.tab.h"
# include "expendfunc.h"
# include<math.h>
%}

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"{" |
"}" |
"(" |
")"     { return yytext[0]; }

"int"  {return INTT;}
"main" {return MAIN;}

 /* built in functions */
"print" { yylval.fn = B_print; return FUNC; }


 /* debug hack */

 /* names */
[a-zA-Z][a-zA-Z0-9]*  { yylval.s = lookup(yytext); return NAME; }

0|[1-9][0-9]* { yylval.d = atof(yytext); return NUMBER; }

"//".*
[ \t]   /* ignore white space */
\\\n    printf("/n"); /* ignore line continuation */
"\n" |
.	{ yyerror("Mystery character %c\n", *yytext); }
%%
int main()
{
	FILE *fwriteCs = fopen("temp.txt","wt");
	fclose(fwriteCs);
	fwriteCs = fopen("ans.asm","wt");
	fclose(fwriteCs);
	fwriteCs = fopen("out.txt", "wt");
	fclose(fwriteCs);

	FILE *fwrites = fopen("temp.txt","a+");
    fprintf(fwrites, "start");
	
    fclose(fwrites);

	FILE *fwriteM = fopen("ans.asm","a+");
	fprintf(fwriteM, ";* 计算器实验 *;\n\n");
    fprintf(fwriteM, "data segment\n");
	fprintf(fwriteM, "T DW 1000 DUP(0)\n");
	fprintf(fwriteM, "H DW 1000 DUP(0)\n");
	fprintf(fwriteM, "data ends\n\n");
	fprintf(fwriteM, "stacks segment stack\ndb 1000 dup (?)\nstacks ends\ncode segment\nassume cs:code,ds:data,ss:stacks,es:data\n\n");
    fprintf(fwriteM, "start:\nMOV AX,CODE\nMOV DS,AX\nMOV DX,00H\n");
	fprintf(fwriteM, "\n");
    fclose(fwriteM);

	yyin = fopen("in.txt", "r");
    if(!(yyin))
    {
		perror("in.txt");
		return 0;
    }
	yyparse();

	FILE *fwritesE = fopen("temp.txt","a+");
    fprintf(fwritesE, "end");
    fclose(fwritesE);
    FILE *fwritesE1 = fopen("ans.asm","a+");
	fprintf(fwritesE1, "MOV AH,4CH\nINT 21H\n\n");
    fclose(fwritesE1);
	expendfunc();
	
	FILE *fwriteE = fopen("ans.asm","a+");
    fprintf(fwriteE, "code ends\n");
	fprintf(fwriteE, "end start");
    fclose(fwriteE);

	fclose(yyin);
	return 0;
}