#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Hash table key/value pair with linked list pointer
 ****/
typedef struct LinkedPair {
  char *key;
  char *value;
  struct LinkedPair *next;
} LinkedPair;

/****
  Hash table with linked pairs
 ****/
typedef struct HashTable {
  int capacity;
  LinkedPair **storage;
} HashTable;

/****
  Create a key/value linked pair to be stored in the hash table.
 ****/
LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = key;
  pair->value = value;
  pair->next = NULL;

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(LinkedPair *pair)
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
 ****/
HashTable *create_hash_table(int capacity)
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(LinkedPair *));

  return ht;
}

/****
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 ****/
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  // hash key to get index
  // pointer to linkedpar at index
  // if pair in Null insert, else loop thru `next` until null or matching key found
  int hashedKey = hash(key, ht->capacity);
  printf("1test\n");
  if(ht->storage[hashedKey] == NULL){
    printf("2test\n");
    ht->storage[hashedKey] = create_pair(key, value);
  }else{
    LinkedPair *pair = ht->storage[hashedKey];
    printf("3test%s\n", pair->value);
    while(pair != NULL){
      if(strcmp(pair->key, key) == 0){
        pair->value = value;
        break;
      }else if (pair->next == NULL){
        pair->next = create_pair(key, value);
        break;
      }else{
        printf("in loop value %s\n", pair->value);
        pair = pair->next;
      }

    }
  }
}

/****
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(HashTable *ht, char *key)
{
  // pointers to first pair at index and a trailing pointer
  // loop thru pair looking for a matching key or null
  // check if pair is null, if it is, no matching key was found
  // check if trail is null, if it is, then change index to next
  // set trail next to equal pair next
  int hashedKey = hash(key, ht->capacity);
  LinkedPair *pair = ht->storage[hashedKey];
  LinkedPair *trail = NULL;
  while(pair != NULL && strcmp(pair->key, key) != 0){
    trail = pair;
    pair = pair->next;
  }
  if(pair == NULL){
    printf("%s is not a key", key);
    return;
  }
  if(trail == NULL){
    ht->storage[hashedKey] = pair->next;
  }else{
    trail->next = pair->next;
  }
}

/****
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 ****/
char *hash_table_retrieve(HashTable *ht, char *key)
{
  int hashedKey = hash(key, ht->capacity);
  LinkedPair *pair = ht->storage[hashedKey];
  while(pair != NULL){
    if(strcmp(pair->key, key) == 0){
      return pair->value;
    }
    pair = pair->next;
  }
  return NULL;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(HashTable *ht)
{
  LinkedPair *current_pair;
  LinkedPair *pair_to_destroy;

  for (int i = 0 ; i < ht->capacity ; i++) {
    current_pair = ht->storage[i];
    while(current_pair != NULL) {
      pair_to_destroy = current_pair;
      current_pair = current_pair->next;
      destroy_pair(pair_to_destroy);
    }
  }

  free(ht->storage);
  free(ht);
}

/****
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 ****/
// HashTable *hash_table_resize(HashTable *ht)
// {
//   HashTable *new_ht;

//   return new_ht;
// }


#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, "line_1", "Tiny hash table\n");
  hash_table_insert(ht, "line_2", "Filled beyond capacity\n");
  hash_table_insert(ht, "line_3", "Linked list saves the day!\n");

  printf("%s", hash_table_retrieve(ht, "line_1"));
  printf("%s", hash_table_retrieve(ht, "line_2"));
  printf("%s", hash_table_retrieve(ht, "line_3"));

  // int old_capacity = ht->capacity;
  // ht = hash_table_resize(ht);
  // int new_capacity = ht->capacity;

  // printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  destroy_hash_table(ht);

  return 0;
}
#endif
