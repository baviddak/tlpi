/* Write a program to see what happens if we try to longjmp() into a function 
 * that has already returned.
 */

/* Usage: ./longjmp_into_returned_fn.exe */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void fn2(){
	longjmp(env, 1);
	return;
}

static void fn1(){
	
	switch(setjmp(env)){
		case 0:
			break;
		case 1: /* Should never hit this condition */
			fn2();
		default:
			break;
	}
	return;
}

int main(int argc, char * argv[]){
	fn1();
	printf("We have reached past the call to fn1() \n");
	fn2();
	
	return(EXIT_SUCCESS);
}
