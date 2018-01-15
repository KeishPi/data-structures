/* Assignment 1 - Q.3
/* Name: Keisha Arnold
 * Description: Practice using arrays, sorting, malloc
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
     /*Sort the given array number , of length n*/
    int swpFlag;
    int temp;
    
    do {
        swpFlag = 0;    /*a swap hasn't occurred*/
        for(int i = 0; i < (n - 1); i++) {
            if(number[i] > number[i + 1]) {
                temp = number[i];
                number[i] = number[i + 1];
                number[i + 1] = temp;
                swpFlag = 1;
            }
        }
    }
    while(swpFlag);     /*keep looping if swap occurred*/
}

int main(){
    
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int *arr = malloc(sizeof(arr[n]));
    
    /*Fill this array with random numbers, using rand().*/
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 1001;
        //printf("%d\n", arr[i]);
    }
    
    /*Print the contents of the array.*/
    for(int i = 0; i < n; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n\n");
    
    /*Pass this array along with n to the sort() function of part a.*/
    sort(arr, n);
    
    /*Print the contents of the array.*/
    for(int i = 0; i < n; i++) {
        printf("%d, ", arr[i]);
    }
   
    
    return 0;
}
