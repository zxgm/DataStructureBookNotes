#include <stdio.h>
#include "../../include/Chapter04/Stack.h"

#define N_OPTR 9
typedef enum {ADD,	SUB, MUL,DIV,POW,FAC,L_P,R_P,EOE} Operator;
const char pri[N_OPTR][N_OPTR] = {
	    // +    -    *    /    ^    !    (    )   \0
	/*+*/ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/*-*/
/***/
/*/*/
/*^*/
/*!*/
/*(*/
/*)*/
/*\0*/
};

int main(int argc, char *argv[])
{
	Stack<char> s;
	convert(s, 178, 16);

	int size = s.size();
	while (size--)
		printf("%c", s.pop());

	getchar();
	return 0;
}