/* Assignment 1 - Q.1
 * Name: Keisha Arnold
 * Description: Practice using structs, malloc, free
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
    /*Allocate memory for ten students*/
    struct student *p = malloc((sizeof(struct student) * 10));
    /*return the pointer*/
    return p;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1-10, scores between 0-100*/
    int usedId[10];         //array to hold id's in use
    int endOfArr = 0;       //keep track of end of array
  
    for(int i = 0; i < 10; i++) {
        int rId = rand() % 10 + 1;      //generate random id between 1 and 10
        //printf("rId:%d ", rId);
        usedId[endOfArr] = rId;
        //printf("usedId: %d ", usedId[endOfArr]);
        
        int rScore = rand() % 101;      //generate random score between 0 and 100
        //printf("rScore:%d\n", rScore);
        
        for(int j = 0; j < endOfArr; j++) {     //check if id already in use
            if(rId == usedId[j]) {
                //printf("usedId: %d", usedId[j]);
                rId = rand() % 10 + 1;          //if found, generate new id, check again
                j = 0;
            }
        }
        //rId = usedId[endOfArr + 1];
        endOfArr++;
        students -> id = rId;
        students -> score = rScore;
        students = students + (sizeof(struct student));
        
    }
}

void output(struct student* students){
    /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/

    for(int i = 0; i < 10; i++) {
        printf("ID%d, Score%d\n", students -> id, students -> score);
        students = students + (sizeof(struct student));
    }
}

void summary(struct student* students){
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min;
    int max;
    double avg;
    double total = 0;
    
    max = students -> score;
    min = students -> score;
    avg = students -> score;
    for(int i = 0; i < 10; i++) {      //find max
        //printf("Max:%d\n", max);
        //students = students + (sizeof(struct student));
        if(max < (students -> score)) {
            max = students -> score;
            //printf("New Max:%d\n", max);
        }
        //printf("Min:%d\n", min);
        if(min > (students -> score)) {
            min = students -> score;
            //printf("New Min:%d\n", min);
        }
        avg = students -> score;
        total = total + avg;
        //printf("Avg:%f\n", avg);
        //printf("Total:%f\n", total);
        students = students + (sizeof(struct student));
    }
    avg = total / 10;
    //printf("Avg:%.2f\n", avg);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    //struct student* allocate();
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
