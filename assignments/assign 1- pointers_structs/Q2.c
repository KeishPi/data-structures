/* Assignment 1 - Q.2
 * Name: Keisha Arnold
 * Description: Practice passing a pointer to a function
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    
    /*Set b to half its original value*/
    *b = *b / 2;
    
    /*Assign a+b to c*/
    c = *a + *b;
    
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    int valFoo;
    
    /*Print the values of x, y and z*/
    printf("x = %d ", x);
    printf("y = %d ", y);
    printf("z = %d ", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    valFoo = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
    printf("\nValue returned by foo: %d\n", valFoo);
    
    /*Print the values of x, y and z again*/
    printf("x = %d ", x);
    printf("y = %d ", y);
    printf("z = %d ", z);
    
    /*Is the return value different than the value of z?  Why?*/
    /*No, z is the same before and after we call foo because C is a pass-by-value language
     and when we pass z to foo we are passing a copy of z. So when we return from foo, z
     still equals 7 because foo was done on a copy of z, not z itself. If we want to change 
     z we have to do a simulation of pass-by-reference like we did with x and y, where we pass 
     to foo a copy of the address of z (foo(&z)), then dereference z within the foo function.*/
    
    return 0;
}
    
    
