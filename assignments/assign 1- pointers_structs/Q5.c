/* Assignment 1 - Q.5
 * Name: Keisha Arnold
 * Description: Practice arrays, pointers
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
    printf("word[0]: %c\n", word[0]);
    
    /*if 1st letter is lowercase, change to uppercase*/
    if((word[0] >= 'a') && (word[0] <= 'z')) {
        word[0] = toUpperCase(word[0]);
    }
    printf("word[0]: %c\n", word[0]);
    
    printf("word: %s\n", word);
    
    for(int i = 1; i < 20; i++) {
        if((i % 2) == 0) {      /*if array index is even, change to uppercase*/
            if((word[i] >= 'a') && (word[i] <= 'z')) {
                word[i] = toUpperCase(word[i]);
                //printf("low: %c\n", word[i]);
            }
        }
        else {      /*else index is odd, change to lowercase*/
            if((word[i] >= 'A') && (word[i] <= 'Z')) {
                word[i] = toLowerCase(word[i]);
            }
        }
    }
    printf("Sticky Word: %s\n", word);
}

int main(){
    char aWord[20];
    
    printf("Enter a single word and I will make it StIcKy: ");
    
    /*Read word from the keyboard using scanf*/
    scanf("%s", aWord);
    
    /*Call sticky*/
    sticky(aWord);
    
    /*Print the new word*/
    printf("Sticky Word: %s\n", aWord);
    
    return 0;
}
