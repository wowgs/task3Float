#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAXLENGTH 512
#define MAX 100000
#define SIZE 10267

typedef struct node node;

typedef struct HashTable HashTable;

struct node
{
    char st[MAXLENGTH];
    int value;
    struct  node *next;
};

struct HashTable
{
    int size;
    node **table;
    long long (*hashFunc)(HashTable*, char*);
};

node *addNode(node *list, char *st, int value)
{
    node *n = (node*)malloc(sizeof(node));
    if (n)
    {
        n->value = value;
        strcpy(n->st, st);
        n->next = list;
        return n;
    }
    else
    {
        printf("malloc failed");
        return;
    }
}

int hashConst(HashTable *hashtable, char *st)
{
    return 17;
}

int hashCountCodes(HashTable *hashTable, char *st)
{
    int l = strlen(st);
    int i;
    int hash = 0;
    for (i = 0; i < l; i++)
    {
        hash = hash + (int)st[i];
    }
    return hash % hashTable->size;
}

int hashGood(HashTable *hashTable, char *st)
{
    long long hash = 0;
    int i;
    const p = 79;
    for (i = 0; i < strlen(st); i++)
    {
        hash = hash * p + (int)st[i];
    }
    int size = hashTable->size;
    return (hash % size + size) % size;
}

HashTable *createTable(long long (*hashFunc)(HashTable*, char*), int size)
{
    HashTable *newTable;
    newTable = (HashTable*)malloc(sizeof(HashTable));
    if (newTable == NULL)
    {
        printf("malloc failed");
        return;
    }
    newTable->table = (node*)malloc(sizeof(node) * size);
    if (newTable->table == NULL)
    {
        printf("malloc failed");
        return;
    }
    int i;
    for(i = 0; i < size; i++)
    {
        newTable->table[i] = NULL;
    }
    newTable->size = size;
    newTable->hashFunc = hashFunc;
    return newTable;
}

node *search(HashTable *hashTable, char *st)
{
    int index = hashTable->hashFunc(hashTable, st);
    node *tmp = hashTable->table[index];
    while (tmp != NULL)
    {
        if ( strcmp(st, tmp->st) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}

void set(HashTable *hashTable, char *st, int value)
{
    int index = hashTable->hashFunc(hashTable, st);
    node *tmp = hashTable->table[index];
    while (tmp)
    {
        if (!strcmp(st, tmp->st))
        {
            tmp->value = value;
            return;
        }
        tmp = tmp->next;
    }
    hashTable->table[index] = addNode(hashTable->table[index], st, value);
}

void deleteSt(HashTable *hashTable, char *st)
{
    node *list = search(hashTable, st);
    if (!list)
    {
        printf("This string is not in the table\n");
    }
    else
    {
        node *tmp = list;
        list->next = tmp->next;
        free(tmp);
    }
}

int get(HashTable *hashTable, char *st)
{

    node *node = search(hashTable, st);
    if (node)
    {
         return node->value;
    }
    else
    {
        return NULL;
    }
}

void freeTable(HashTable *hashTable)
{
    node *tmp, *cur;
    int size = hashTable->size;
    if (hashTable == NULL)
    {
        return;
    }
    else
    {
        int i;
        for (i = 0; i< size; i++)
        {
           tmp = hashTable->table[i];
           while (tmp)
           {
               cur = tmp;
               tmp = tmp->next;
               free(cur);
           }
        }
        free(hashTable->table);
        free(hashTable);
    }
}

void stat(HashTable *hashTable)
{
    int i, nonEmpty = 0, numbElem = 0, numbWords = 0, minLen = MAX, maxLen = 0;
    double averageLen = 0.0;
    for (i = 0; i < hashTable->size; i++)
    {
        int tmpLen = 0;
        node *tmp = hashTable->table[i];
        if (tmp)
        {
            nonEmpty++;
        }
        while (tmp)
        {
            tmpLen++;
            numbElem++;
            numbWords = numbWords + tmp->value;
            tmp = tmp->next;
        }

        if ((minLen > tmpLen) && tmpLen != 0)
        {
            minLen = tmpLen;
        }

        if (maxLen < tmpLen)
        {
            maxLen = tmpLen;
        }
        averageLen += tmpLen;
    }

    if (maxLen)
    {
        averageLen = averageLen / (double)nonEmpty;
    }
    printf("There are %d  non-empty cells\n", nonEmpty);
    printf("There are %d  elements\n", numbElem);
    printf("Average length = %.2f\n", averageLen);
    printf("Max length = %d\n", maxLen);
    if (minLen == MAX)
    {
        printf("There is no min length != 0 \n");
    }
    else if (nonEmpty == 1)
    {
        printf("Min length = %d\n", maxLen); //minLen = maxLen
    }
    else
    {
        printf("Min length = %d\n", minLen);
    }
}
