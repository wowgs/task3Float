#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAXLENGTH 512
#define SIZE 10267
#define MAX 100000

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
    newTable = (node**)malloc(sizeof(node*) * size);
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
    printf("There are %d  words\n", numbWords);
    printf("There are %d  different words\n", numbElem);
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

int check(char c, int l)
{
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '-' && l != 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void count(HashTable *hashTable)
{
    int i;
    for(i = 0; i< hashTable->size; i++)
    {
        node *tmp = hashTable->table[i];
        while (tmp)
        {
            printf("%s -> %d\n", tmp->st, tmp->value);
            tmp = tmp->next;
        }
    }
}

void textAnalyzer(HashTable *hashTable)
{

    int i, j, l;
    FILE *input;
    char *rez = (char*)malloc(sizeof(char) * MAXLENGTH);
    if (rez == NULL)
    {
        printf("malloc failed");
        return;
    }
    char *st = (char *) malloc(sizeof(char) * MAXLENGTH);
    if (st == NULL)
    {
        printf("malloc failed");
        return;
    }
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("File not found\n");
        return;
    }
    srand(time(NULL));
    clock_t begin,delta;
    begin = clock();
    while(fscanf(input, "%s", st) != EOF)
    {
        j = 0;
        l = strlen(st);
        for (i = 0; i < l; i++)
        {
            if (check(st[i],l))
            {
                rez[j] = st[i];
                j++;
            }
        }

        rez[j] = '\0';
        if (rez[0] != '\0')
        {
            if (get(hashTable, rez))
            {
               set(hashTable, rez, get(hashTable,rez)+1);
            }
            else
            {
                set(hashTable, rez, 1);
            }
        }
    }
    delta  = (clock() - begin);
    printf("time: %.4f\n", (double)delta/CLOCKS_PER_SEC);
    fclose(input);
    if (fclose(input) == 0)
    {
        printf("Error!\n");
        return;
    }
}
int main ()
{
    HashTable *hashTable = createTable(hashConst, SIZE);
    textAnalyzer(hashTable);
    stat(hashTable);
    freeTable(hashTable);
    hashTable = createTable(hashCountCodes, SIZE);
    textAnalyzer(hashTable);
    stat(hashTable);
    freeTable(hashTable);
    hashTable = createTable(hashGood, SIZE);
    textAnalyzer(hashTable);
    stat(hashTable);
    freeTable(hashTable);

}

/*	                    hashConst       hashCountCodes      hashGood
   non-empty cells      1               1134                6028
   words                104027          104027              104027
   different words      9107            9107                9107
   average length       9107.00         8.03                1.51
   max length           9107            43                  6
   min length           9107            1                   1
   time                 28.4040         0.0800              0.067*/
