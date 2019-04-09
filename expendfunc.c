#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
# include <math.h>
#  include "expendfunc.h"

void expendfunc(){
    FILE *fwriteM = fopen("ans.asm","a+");
    fprintf(fwriteM, ";example for display register content\n");
    fprintf(fwriteM, "print	proc\npush	ax\npush dx\npush cx\nmov dx,-1\npush dx\nmov cx, 10\nl_div10:\nxor dx,dx\ndiv    cx\npush dx\ntest ax,ax\njne l_div10\nmov cx,-1\nmov ah,2\nl_disp:\npop dx\ncmp dx,cx\nje l_ret\nadd dl,'0'\nint 21h\njmp l_disp\nl_ret:\npop cx\npop dx\npop ax\nret\nprint	endp\n");
    fprintf(fwriteM, "\n");
    fclose(fwriteM);
}
