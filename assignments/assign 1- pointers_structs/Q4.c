/* Assignment 1 - Q.4
/* Name: Keisha Arnold
 * Description: Practice arrays, sorting, structs
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

/*Sort the n students based on their score*/
void sort(struct student* students, int n){
    int swpFlag;
    struct student temp;
    
    /*for(int i = 0; i < n; i++) {
        printf("ID:%d, Score: %d\n", students[i].id, students[i].score);
    }*/

    do {
        swpFlag = 0;    /*a swap hasn't occurred*/
        for(int i = 0; i < (n - 1); i++) {
            if(students[i].score > students[i + 1].score) {
                temp = students[i];
                students[i] = students[i + 1];
                students[i + 1] = temp;
                swpFlag = 1; /*swap occurred*/
            }
        }
    }
    while(swpFlag);     /*keep looping if swap occurred*/
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 5;
    
    /*Allocate memory for n students using malloc.*/
    struct student *arr = malloc(sizeof(arr[n]));
    
    /*Generate random and unique IDs and random scores for the n students, using rand()*/
    int usedId[5];          /*array to hold id's in use*/
    int endOfArr = 0;       /*keep track of end of array*/
    
    for(int i = 0; i < 5; i++) {
        int rId = rand() % 5 + 1;      /*generate random id between 1 and 5*/
        //printf("rId:%d \n", rId);
        //usedId[endOfArr] = rId;
        //printf("endOfArr: %d\n", endOfArr);
        
        int rScore = rand() % 101;      /*generate random score between 0 and 100*/
        //printf("rScore:%d\n", rScore);
        
        for(int j = 0; j <= endOfArr; j++) {     /*check if id already in use*/
            if(usedId[j] == rId) {
                //printf("CheckId: %d ", usedId[j]);
                rId = rand() % 5 + 1;          /*if found, generate new id, check again*/
                j = 0;
            }
        }
        usedId[endOfArr] = rId;
        endOfArr++;
        arr[i].id = rId;
        arr[i].score = rScore;
    }

    /*Print the contents of the array of n students.*/
    for(int i = 0; i < n; i++) {
        printf("ID:%d, Score: %d\n", arr[i].id, arr[i].score);
    }
    printf("\n\n");
    
    /*Pass this array along with n to the sort() function*/
    sort(arr, n);
    
    /*Print the contents of the array of n students.*/
    for(int i = 0; i < n; i++) {
        printf("ID:%d, Score: %d\n", arr[i].id, arr[i].score);
    }
    
    return 0;
}
