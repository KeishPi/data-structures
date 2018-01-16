/********************************************************************************
 ** Program Filename: compare.c
 ** Author: Keisha Arnold (provided skeleton code)
 ** Description: Implementing a bag ADT using a binary search tree, which holds
 ** a generic container by utilizing the void pointer and TYPE macro.  This is
 ** a helper compare function implementation file.
 ********************************************************************************/
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right)
{
    /*FIXME: write this*/
	struct data* data1;
	struct data* data2;
	//cast left and right to pointer type (struct data *)
	data1 = (struct data*)left;
	data2 = (struct data*)right;
	
	//compare the values pointed to by the casted pointers
	if(data1 -> number < data2 -> number)
		return -1;
	else if(data1 -> number > data2 -> number)
		return 1;
	else    //left = right
		return 0;

}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{
    /*FIXME: write this*/
	printf("The current value is: %p\n", ((void *)curval));
}


