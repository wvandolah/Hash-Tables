#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = key;
  pair->value = value;

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) free(pair);
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash % max;
}


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(Pair *));

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // hash the key
  // create pair
  // check storage at hashed index
  // place pair in storage at hashed key
  int hashedKey = hash(key, ht->capacity);
  Pair *pair = create_pair(key, value);
  if(ht->storage[hashedKey] != NULL){
    printf("you just replayed what was in storage at %d\n", hashedKey);
    destroy_pair(ht->storage[hashedKey]);
  }
  ht->storage[hashedKey] = pair;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  // hash key
  // create Pair for pair at hashedKey index
  // destroy pair
  // TODO: check if hashed Key was in storage 
  int hashedKey = hash(key, ht->capacity);
  Pair *pair = ht->storage[hashedKey];
  if(pair != NULL){
    destroy_pair(pair);
    ht->storage[hashedKey] = NULL;
    return;
  }
  printf("%s cant be removed\n", key);
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  // hash key
  // if found, return pair
  int hashedKey = hash(key, ht->capacity);
  
  if(ht->storage[hashedKey] != NULL){
    return ht->storage[hashedKey]->value;
  }
  return NULL;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  // destroy all pairs
  // free storage and ht
  for(int i = 0; i < ht->capacity; i++){
    if (ht->storage[i] != NULL) {
      destroy_pair(ht->storage[i]);
    }
  }
  free(ht->storage);
  free(ht);
}


#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");
  hash_table_remove(ht, "something");
  printf("%s", hash_table_retrieve(ht, "line"));
  printf("retrieve %s", hash_table_retrieve(ht, "line"));
  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
