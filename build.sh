bison -d fb4-1.y
flex -ofb4-1.lex.c fb4-1.l 
gcc -o x86 fb4-1.tab.c fb4-1.lex.c expendfunc.c fb4-1funcs.c -lm
