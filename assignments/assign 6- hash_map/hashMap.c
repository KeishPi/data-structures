/*
 * Assignment 6
 * Name: Keisha Arnold
 * Description: Hash map implementation using a table of buckets, 
 *	each containing a singly linked list of hash links.
 *	Each hash link stores the key-value pair (string-integer) 
 *	and a pointer to the next link in the list.
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/*
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/*
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/*
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/*
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
	for(int i = 0; i < map -> capacity; i++) {
		HashLink* lnk = map -> table[i];
		map->table[i] = 0;
		
		while(lnk != 0) {
			HashLink* temp = lnk;
			lnk = lnk -> next;
			hashLinkDelete(temp);
		}
		free(map -> table[i]);
	}
	free(map -> table);
}

/*
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/*
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/*
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
	//compute hash table bucket index
	int idx = HASH_FUNCTION(key) % map -> capacity;
	HashLink* lnk = map -> table[idx];
	
	while(lnk != 0) {
		if(strcmp(lnk -> key, key) == 0) {
			return &lnk -> value;	//returns a POINTER to the value of the link
		}
		lnk = lnk -> next;
	}
    return NULL;
}

/*
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
	int oldCap = map -> capacity;
	HashLink** oldTable = map -> table;
	
	hashMapInit(map, capacity);	//new Table
	
	for(int i = 0; i < oldCap; i++) {
		HashLink* lnk = oldTable[i];
		while(lnk != 0) {
			hashMapPut(map, lnk -> key, lnk -> value);	//rehash links into new table
			lnk = lnk -> next;
		}
	}
	
	for(int i = 0; i < oldCap; i++) {	//free the memory from the old links and old table
		HashLink* lnk = oldTable[i];
		oldTable[i] = 0;
		while(lnk != 0) {
			HashLink* temp = lnk;
			lnk = lnk -> next;
			hashLinkDelete(temp);
		}
		free(oldTable[i]);
	}
	free(oldTable);
}

/*
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
	int idx;
	
	if(hashMapTableLoad(map) >= MAX_TABLE_LOAD) {	//resize if load factor is too large
		resizeTable(map, (map -> capacity * 2));
	}
	
	idx = HASH_FUNCTION(key) % map -> capacity;		//calculate hash table bucket index
	if(idx < 0) {
		idx = idx + (map -> capacity);				//make sure we have a positive hash value
	}
	
	HashLink* lnk = map -> table[idx];
	HashLink* newLnk = 0;
	if(lnk == 0) {									//bucket is empty, so add to current bucket
		newLnk = hashLinkNew(key, value, 0);
		map -> table[idx] = newLnk;
		map -> size++;
		return;
	}
	else {
		while(lnk != 0) {							//bucket has 1 or more links
			if(strcmp(lnk -> key, key) == 0) {
				lnk -> value = value;				//link-key already occurs, so return
				return;
			}
			lnk = lnk -> next;
		}
		newLnk = hashLinkNew(key, value, map -> table[idx]);	//link-key doesn't exist
		map -> table[idx] = newLnk;								//so make a new link & add it
		map -> size++;											//increment the size of the map
		return;
	}
}

/*
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
	int idx;
	
	if(!hashMapContainsKey(map, key)) {			//make sure key is in map
		return;
	}
	idx = HASH_FUNCTION(key) % map -> capacity;	//find the correct bucket
	HashLink* lnk = map -> table[idx];
	HashLink* lastLnk = map -> table[idx];
	
	while(lnk != 0) {							//loop while link is not empty
		if(strcmp(lnk -> key, key) == 0) {
			if(lnk == map -> table[idx]) {		//first link is a match
				map -> table[idx] = lnk -> next;	//point to next link
				hashLinkDelete(lnk);			//delete link
				map -> size--;					//decrement size
				lnk = 0;
			}
			else {
				lastLnk -> next = lnk -> next;
				hashLinkDelete(lnk);
				map -> size--;
				lnk = 0;
			}
		}
		else {		//walk down the links
			lastLnk = lnk;
			lnk = lnk -> next;
		}
	}
}
	

/*
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
	int idx = HASH_FUNCTION(key) % map -> capacity;		//find the correct bucket
	HashLink* lnk = map -> table[idx];
	while(lnk != 0) {									//loop while link is not null
		if(strcmp(lnk -> key, key) == 0) {
			return 1;									//return 1 if found
		}
		lnk = lnk -> next;
	}
    return 0;
}

/*
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
	return (map -> size);
}

/*
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
	return (map -> capacity);
}

/*
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
	int numEmptyBuckets = 0;
	
	for(int i = 0; i < map -> capacity; i++) {
		HashLink* lnk = map -> table[i];
		if(lnk == 0) {
			numEmptyBuckets++;
		}
	}
	return numEmptyBuckets;
}

/*
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
	float tableLoad;
	
	float numLinks = (float)map -> size;	//cast to float
	float numBuckets = (float)map -> capacity;
	tableLoad = (numLinks/numBuckets);
	
	return tableLoad;	//represents average number of elements in each bucket
}

/*
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
