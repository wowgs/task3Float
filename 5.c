#include <stdio.h>
#include <string.h>
#include "hashTable.h"

int main()
{
    HashTable hashTable = createHashTable();
    int i;
    int n;
    printf("Please, enter your n = ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%s", s);
        add(hashTable, s);
    }
    countString(hashTable);
}
