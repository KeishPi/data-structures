/*
 * Assignment 6
 * Name: Keisha Arnold
 * Description: Implementation of a concordance using a hash map.
 *	Each hash link in the table will store a word from the file 
 *	as a key and the number of times the word appeared as the value.
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/*
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
/*  Could also add a ToLowerCase function, which makes all letters lowercase.
 *	Perhaps better to implement as part of nextWord function rather than a
 *	separate function? (the and The would be counted as 2)
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/*
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    // Be sure to free the word after you are done with it here.
	FILE *filePtr;
	char *word;
	int countWord;
	
	//open the file
	filePtr = fopen(fileName, "r");	//"r" = read
	if(filePtr == NULL) {
		fprintf(stderr, "Cannot open %s\n", fileName);
	}
	//Process file until EOF
	word = nextWord(filePtr);
	while(word != 0) {
		if(hashMapContainsKey(map, word)) {		//if already found, increment countWord
			countWord = *(hashMapGet(map, word));
			hashMapPut(map, word, ++countWord);
		}
		else {
			hashMapPut(map, word, 1);	//if not found before, countWord is 1
		}
		free(word);						//free the memory to word before assigning to the next word
		word = nextWord(filePtr);
	}
	//close the file!
	fclose(filePtr);
	
	//Print words and occurrence counts in the hash map
	for(int i = 0; i < map -> capacity; i++) {
		HashLink *lnk = map -> table[i];
		if(lnk != 0) {
			while(lnk != 0) {
				printf(" %s: %d \n", lnk -> key, lnk -> value);
				lnk = lnk -> next;
			}
		}
	}
	
    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}
