
/*
 * helper functions for fb3-3
 */
#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
# include <math.h>
#  include "fb4-1.h"
#  include "expendfunc.h"

/* 汇编代码生成区 */
void MOV(struct four *p){
  if (p->t1 == 'N'){
    FILE *fwriteM = fopen("ans.asm","a+");
    p->p3 = p->p3 * 2 + 1;
    fprintf(fwriteM, "MOV BX,%d\n",p->p3);
    fprintf(fwriteM, "MOV %c[BX],%d\n",p->t3,p->p1);
    fprintf(fwriteM, "\n");
    fclose(fwriteM);
  }else {
    FILE *fwriteM = fopen("ans.asm","a+");
    p->p1 = p->p1 * 2 + 1;
    p->p3 = p->p3 * 2 + 1;
    fprintf(fwriteM, "MOV BX,%d\n",p->p1);
    fprintf(fwriteM, "MOV AX,%c[BX]\n",p->t1);
    fprintf(fwriteM, "MOV BX,%d\n",p->p3);
    fprintf(fwriteM, "MOV %c[BX],AX\n",p->t3);
    fprintf(fwriteM, "\n");
    fclose(fwriteM);
  }
}

void ADD(struct four *p){
  p->p1=2*p->p1+1;
  p->p2=2*p->p2+1;
  p->p3=2*p->p3+1;
  FILE *fwriteM = fopen("ans.asm","a+");
  fprintf(fwriteM, "MOV BX,%d\n",p->p1);
  fprintf(fwriteM, "MOV AX,%C[BX]\n",p->t1);
  fprintf(fwriteM, "MOV BX,%d\n",p->p2);
  fprintf(fwriteM, "MOV DX,%C[BX]\n",p->t2);
  fprintf(fwriteM, "MOV BX,DX\n");
  fprintf(fwriteM, "ADD AX,BX\n");
  fprintf(fwriteM, "MOV BX,%d\n",p->p3);
  fprintf(fwriteM, "MOV %c[BX],AX\n",p->t3);
  fprintf(fwriteM, "\n");
  fclose(fwriteM);
}

void SUB(struct four *p){
  p->p1=2*p->p1+1;
  p->p2=2*p->p2+1;
  p->p3=2*p->p3+1;
  FILE *fwriteM = fopen("ans.asm","a+");
  fprintf(fwriteM, "MOV BX,%d\n",p->p1);
  fprintf(fwriteM, "MOV AX,%C[BX]\n",p->t1);
  fprintf(fwriteM, "MOV BX,%d\n",p->p2);
  fprintf(fwriteM, "MOV DX,%C[BX]\n",p->t2);
  fprintf(fwriteM, "MOV BX,DX\n");
  fprintf(fwriteM, "SUB AX,BX\n");
  fprintf(fwriteM, "MOV BX,%d\n",p->p3);
  fprintf(fwriteM, "MOV %c[BX],AX\n",p->t3);
  fprintf(fwriteM, "\n");
  fclose(fwriteM);
}

void MUL(struct four *p){
  p->p1=2*p->p1+1;
  p->p2=2*p->p2+1;
  p->p3=2*p->p3+1;
  FILE *fwriteM = fopen("ans.asm","a+");
  fprintf(fwriteM, "MOV BX,%d\n",p->p1);
  fprintf(fwriteM, "MOV AX,%C[BX]\n",p->t1);
  fprintf(fwriteM, "MOV BX,%d\n",p->p2);
  fprintf(fwriteM, "MOV DX,%C[BX]\n",p->t2);
  fprintf(fwriteM, "MOV BX,DX\n");
  fprintf(fwriteM, "MUL BX\n");
  fprintf(fwriteM, "MOV BX,%d\n",p->p3);
  fprintf(fwriteM, "MOV %c[BX],AX\n",p->t3);
  fprintf(fwriteM, "\n");
  fclose(fwriteM);
}

void DIV(struct four *p){
  p->p1=2*p->p1+1;
  p->p2=2*p->p2+1;
  p->p3=2*p->p3+1;
  FILE *fwriteM = fopen("ans.asm","a+");
  fprintf(fwriteM, "MOV BX,%d\n",p->p1);
  fprintf(fwriteM, "MOV AX,%C[BX]\n",p->t1);
  fprintf(fwriteM, "MOV DX,0\n");
  fprintf(fwriteM, "MOV BX,%d\n",p->p2);
  fprintf(fwriteM, "MOV CX,%C[BX]\n",p->t2);
  fprintf(fwriteM, "MOV BX,CX\n");
  fprintf(fwriteM, "DIV BX\n");
  fprintf(fwriteM, "MOV BX,%d\n",p->p3);
  fprintf(fwriteM, "MOV %c[BX],AX\n",p->t3);
  //fprintf(fwriteM, "MOV,%c[BX],DX\n",p->t3-1);
  fprintf(fwriteM, "\n");
  fclose(fwriteM);
}

void NEG(struct four *p){
  p->p3=2*p->p3+1;
  FILE *fwriteM = fopen("ans.asm","a+");
  fprintf(fwriteM, "MOV BX,%d\n",p->p3);
  fprintf(fwriteM, "MOV AX,%C[BX]\n",p->t3);
  fprintf(fwriteM, "NEG AX\n");
  fprintf(fwriteM, "MOV %C[BX],AX\n",p->t3);
  fprintf(fwriteM, "\n");
  fclose(fwriteM);
}

void PRT(struct four *p){
  p->p1=2*p->p1+1;
  FILE *fwriteM = fopen("ans.asm","a+");
  fprintf(fwriteM, "MOV BX,%d\n",p->p1);
  fprintf(fwriteM, "MOV AX,%C[BX]\n",p->t1);
  fprintf(fwriteM, "call print\n");
  fprintf(fwriteM, "\n");
  fclose(fwriteM);
}

/* 符号表 */
/* hash a symbol 哈希一个符号 */
static unsigned
symhash(char *sym)
{
  unsigned int hash = 0;
  unsigned c;

  while(c = *sym++) hash = hash*9 ^ c;

  return hash;
}

struct symbol *
lookup(char* sym)
{
  struct symbol *sp = &symtab[symhash(sym)%NHASH];
  int scount = NHASH;		/* how many have we looked at 需要查看的个数*/

  while(--scount >= 0) {
    if(sp->name && !strcmp(sp->name, sym)) { return sp; }

    if(!sp->name) {		/* new entry新条目 */
      sp->name = strdup(sym);
      sp->value = 0;
      sp->func = NULL;
      return sp;
    }

    if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry 尝试下一条目*/
  }
  yyerror("symbol table overflow\n");
  abort(); /* tried them all, table is full尝试完所有条目 符号表已满 */

}

/* 建树所用的节点 */
struct ast *
newast(int nodetype, struct ast *l, struct ast *r)
{
  struct ast *a = malloc(sizeof(struct ast));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  a->l = l;
  a->r = r;
  return a;
}

struct ast *
newnum(double d)
{
  struct numval *a = malloc(sizeof(struct numval));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'K';
  a->number = d;
  return (struct ast *)a;
}

struct ast *
newcmp(int cmptype, struct ast *l, struct ast *r)
{
  struct ast *a = malloc(sizeof(struct ast));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = '0' + cmptype;
  a->l = l;
  a->r = r;
  return a;
}

struct ast *
newfunc(int functype, struct ast *l)
{
  struct fncall *a = malloc(sizeof(struct fncall));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'F';
  a->l = l;
  a->functype = functype;
  return (struct ast *)a;
}


struct ast *
newref(struct symbol *s)
{
  struct symref *a = malloc(sizeof(struct symref));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'N';
  a->s = s;
  return (struct ast *)a;
}

struct ast *
newasgn(struct symbol *s, struct ast *v)
{
  struct symasgn *a = malloc(sizeof(struct symasgn));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = '=';
  a->s = s;
  a->v = v;
  return (struct ast *)a;
}


struct adress *callbuiltin(struct fncall *);
int ti = 0;
int hi = 0;

void initt(){

  for (int i=0;i<NHASH;i++){
    symtab[i].pos=-1;
    ti = 0;
    hi = 0;
  }
}


struct adress *
eval(struct ast *a)
{
  double v;
  struct adress *re = malloc(sizeof(struct adress));
  struct adress *l = malloc(sizeof(struct adress));
  struct adress *r = malloc(sizeof(struct adress));
  struct four *f = malloc(sizeof(struct four));
  f->t1='N';
  f->t2='N';
  f->t3='N';
  if(!a) {
    yyerror("internal error, null eval");
    re->v=0.0;
    re->type='N';//-1为空
    return re;
  }

  switch(a->nodetype) {
    /* constant常量 */
  case 'K': v = ((struct numval *)a)->number;
            re->v=v;
            re->type='T';
            re->pos=ti++;
            int pv = v;
            FILE *fwrite = fopen("temp.txt","a+");
            fprintf(fwrite, "MOV,%d,,%c%d\n", pv,re->type,re->pos);
            fclose(fwrite);
            f->t3 = 'T';
            f->p1 = pv;
            f->p3 = re->pos;
            MOV(f);
            break;

    /* name reference名字引用 */
  case 'N': v = ((struct symref *)a)->s->value; 
            re->v=v;
            re->type='H';
            if (((struct symref *)a)->s->pos==-1){
              FILE *fwrite1 = fopen("temp.txt","a+");
              pv = v;
              ((struct symref *)a)->s->pos = re->pos=hi++;
              fprintf(fwrite1, "MOV,%d,,%c%d\n", pv,re->type,re->pos);
              fclose(fwrite1);
              f->t3='H';
              f->p1=pv;
              f->p3=re->pos;
              MOV(f);
              }
            else
              re->pos=((struct symref *)a)->s->pos;
            break;

    /* assignment赋值 */
  case '=':  
      re = eval(((struct symasgn *)a)->v);
      ti = 0;
      v = re->v;
      int Hpos,Tpos,Ttyp;
      if (((struct symasgn *)a)->s->pos==-1)
        Hpos = ((struct symasgn *)a)->s->pos = hi++;
      else
        Hpos = ((struct symasgn *)a)->s->pos;
      Tpos = re->pos;
      Ttyp = re->type;
      FILE *fwrite2 = fopen("temp.txt","a+");
      fprintf(fwrite2, "MOV,%c%d,,H%d\n", Ttyp,Tpos,Hpos);
      fclose(fwrite2);
      f->t1=Ttyp;
      f->p1=Tpos;
      f->t3='H';
      f->p3=Hpos;
      MOV(f);
      ((struct symasgn *)a)->s->value = re->v;
      break;

    /* expressions 表达式*/
  case '+': 
        l = eval(a->l);
        r = eval(a->r);
        v = l->v + r->v;
        int lt,rt,ls,rs;
        lt = l->type;
        rt = r->type;
        ls = l->pos;
        rs = r->pos;
        re->pos = ti++;
        re->type = 'T';
        re->v = v;
        FILE *fwrite3 = fopen("temp.txt","a+");
        fprintf(fwrite3, "ADD,%c%d,%c%d,T%d\n", lt,ls,rt,rs,re->pos);
        fclose(fwrite3);
        f->t1=lt;
        f->p1=ls;
        f->t2=rt;
        f->p2=rs;
        f->t3='T';
        f->p3=re->pos;
        ADD(f);
        break;
  case '-': 
        l = eval(a->l);
        r = eval(a->r);
        v = l->v - r->v;
        /*int lt,rt,ls,rs;*/
        lt = l->type;
        rt = r->type;
        ls = l->pos;
        rs = r->pos;
        re->pos = ti++;
        re->type = 'T';
        re->v = v;
        FILE *fwrite4 = fopen("temp.txt","a+");
        fprintf(fwrite4, "SUB,%c%d,%c%d,T%d\n", lt,ls,rt,rs,re->pos);
        fclose(fwrite4);
        f->t1=lt;
        f->p1=ls;
        f->t2=rt;
        f->p2=rs;
        f->t3='T';
        f->p3=re->pos;
        SUB(f);
        break;
  case '*': 
        l = eval(a->l);
        r = eval(a->r);
        v = l->v * r->v;
        /*int lt,rt,ls,rs;*/
        lt = l->type;
        rt = r->type;
        ls = l->pos;
        rs = r->pos;
        re->pos = ti++;
        re->type = 'T';
        re->v = v;
        FILE *fwrite5 = fopen("temp.txt","a+");
        fprintf(fwrite5, "MUL,%c%d,%c%d,T%d\n", lt,ls,rt,rs,re->pos);
        fclose(fwrite5);
        f->t1=lt;
        f->p1=ls;
        f->t2=rt;
        f->p2=rs;
        f->t3='T';
        f->p3=re->pos;
        MUL(f);
        break;
  case '/':
        l = eval(a->l);
        r = eval(a->r);
        v = l->v / r->v;
        /*int lt,rt,ls,rs;*/
        lt = l->type;
        rt = r->type;
        ls = l->pos;
        rs = r->pos;
        re->pos = ti++;
        re->type = 'T';
        re->v = v;
        FILE *fwrite6 = fopen("temp.txt","a+");
        fprintf(fwrite6, "DIV,%c%d,%c%d,T%d\n", lt,ls,rt,rs,re->pos);
        fclose(fwrite6);
        f->t1=lt;
        f->p1=ls;
        f->t2=rt;
        f->p2=rs;
        f->t3='T';
        f->p3=re->pos;
        DIV(f);
        break;
  case 'M':
        l = eval(a->l);
        v = -l->v;
        /*int lt,ls;*/
        lt = l->type;
        ls = l->pos;
        re->pos = ls;
        re->type = lt;
        re->v = v;
        FILE *fwrite7 = fopen("temp.txt","a+");
        fprintf(fwrite7, "NEG,,,%c%d\n",lt,ls);
        fclose(fwrite7);
        f->t3=lt;
        f->p3=ls;
        NEG(f);
        break;

    /* comparisons 比较*/

  /* control flow 控制流*/
  /* null if/else/do expressions allowed in the grammar, so check for them允许空故需检查 */
	              
  case 'L': eval(a->l); 
        re = eval(a->r);
        v = re->v; 
        break;

  case 'F': re = callbuiltin((struct fncall *)a);
            v = re->v;
            break;

  default: printf("internal error: bad node %c\n", a->nodetype);
  }
  return re;
}

struct adress *
callbuiltin(struct fncall *f)
{
  enum bifs functype = f->functype;
  struct adress *re = malloc(sizeof(struct adress));
  struct four *ff = malloc(sizeof(struct four));
  re = eval(f->l);
  double v = re->v;
  int t = re->type;
  int s = re->pos;
 switch(functype) {
 case B_print:
   printf("= %4.4g\n", v);
   FILE *fwrite10 = fopen("temp.txt","a+");
   fprintf(fwrite10, "print,%c%d, , \n", t,s);
   fclose(fwrite10);
   char ch[100];
   FILE *out = fopen("out.txt", "a+");
   gcvt(v,10,ch);
   fprintf(out,"%s\n",ch);
   fclose(out);
   ff->p1=s;
   ff->t1=t;
   PRT(ff);
   return re;
 default:
   yyerror("Unknown built-in function %d", functype);
   return re;
 }
}



void
treefree(struct ast *a)
{
  switch(a->nodetype) {

    /* two subtrees */
  case '+':
  case '-':
  case '*':
  case '/':
  case '1':  case '2':  case '3':  case '4':  case '5':  case '6':
  case 'L':
    treefree(a->r);

    /* one subtree */
  case '|':
  case 'M': case 'C': case 'F':
    treefree(a->l);

    /* no subtree */
  case 'K': case 'N':
    break;

  case '=':
    free( ((struct symasgn *)a)->v);
    break;

  case 'I': case 'W':
    free( ((struct flow *)a)->cond);
    if( ((struct flow *)a)->tl) free( ((struct flow *)a)->tl);
    if( ((struct flow *)a)->el) free( ((struct flow *)a)->el);
    break;

  default: printf("internal error: free bad node %c\n", a->nodetype);
  }	  
  
  free(a); /* always free the node itself */

}

void
yyerror(char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

int debug = 0;
void
dumpast(struct ast *a, int level)
{

  printf("%*s", 2*level, "");	/* indent to this level */
  level++;

  if(!a) {
    printf("NULL\n");
    return;
  }

  switch(a->nodetype) {
    /* constant */
  case 'K': printf("number %4.4g\n", ((struct numval *)a)->number); break;

    /* name reference */
  case 'N': printf("ref %s\n", ((struct symref *)a)->s->name); break;

    /* assignment */
  case '=': printf("= %s\n", ((struct symref *)a)->s->name);
    dumpast( ((struct symasgn *)a)->v, level); return;

    /* expressions */
  case '+': case '-': case '*': case '/': case 'L':
  case '1': case '2': case '3':
  case '4': case '5': case '6': 
    printf("binop %c\n", a->nodetype);
    dumpast(a->l, level);
    dumpast(a->r, level);
    return;

  case '|': case 'M': 
    printf("unop %c\n", a->nodetype);
    dumpast(a->l, level);
    return;

  case 'I': case 'W':
    printf("flow %c\n", a->nodetype);
    dumpast( ((struct flow *)a)->cond, level);
    if( ((struct flow *)a)->tl)
      dumpast( ((struct flow *)a)->tl, level);
    if( ((struct flow *)a)->el)
      dumpast( ((struct flow *)a)->el, level);
    return;
	              
  case 'F':
    printf("builtin %d\n", ((struct fncall *)a)->functype);
    dumpast(a->l, level);
    return;

  default: printf("bad %c\n", a->nodetype);
    return;
  }
}
