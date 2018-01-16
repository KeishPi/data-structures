/******************************************************************************
 ** Program Filename: stackapp.c
 ** Author: Keisha Arnold ("FIX ME")
 ** Description: Implementation of a stack to determine if a string contains
 ** balanced parentheses.
******************************************************************************/
/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/*  Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/*  Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post: 1 if balanced, otherwise 0
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */
	DynArr *dyn;
	dyn = newDynArr(1);
	TYPE topChar;
	TYPE nextCh;
	int isBal = 0;

	nextCh = nextChar(s);
	
	while(nextCh != '\0') {
	//printf("nextChar: %c\n", nextCh);
		/* open parens, push closed parens */
		if(nextCh == '(') {
			pushDynArr(dyn, nextCh + 1);
			//topChar = topDynArr(dyn);
			//printf("top: %c\n", topChar);
		}
		if(nextCh == '{' || nextCh == '[') {
			pushDynArr(dyn, (nextCh + 2));
			//topChar = topDynArr(dyn);
			//printf("top: %c\n", topChar);
		}
		/* closed parens */
		if(nextCh == ')' || nextCh == '}' || nextCh == ']') {
			if(isEmptyDynArr(dyn)) { /* check if stack is empty */
				printf("Stack is empty\n");
				return 0;
			}
			topChar = topDynArr(dyn);
			//printf("nextCh & topChar: %c%c\n", nextCh, topChar);
			if(nextCh == topChar) { /* matches, pop it off the stack */
				popDynArr(dyn);
				//printf("top after pop: %c\n", topChar);
			}
			else { /* no match, not balanced */
				//printf("returning 0...");
				return 0;
			}	
		}
	/* move to next character */
	nextCh = nextChar(s);
	//printf("next char: %c\n", nextCh);
	
	}
	/* end of string reached */
	if(nextCh == '\0') {
		if(isEmptyDynArr(dyn)) {
			isBal = 1;
		}
		else {
			isBal = 0;
		}
	}
	return isBal;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

