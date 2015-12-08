#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sortCount(int *data, int size)
{
    const int max = 100000;
    int i;

    int *count = malloc(max * sizeof(int));
    if (count == NULL)
    {
        printf("malloc failed\n");
        return;
    }

    for (i = 0; i < max; i++)
    {
        count[i]=0;
    }

    for (i = 0; i < size; i++)
    {
        count[data[i]]++;
    }
    int j = 0;

    for(i = 0; i <= max; i++)
    {
        while(count[i] > 0)
        {
            count[i]--;
            data[j]=i;
            j++;
        }
     }
    free(count);
}

void sortBubble(int *data, int size)
{
    int i,j;
    for (j = 0; j < size-1; j++)
    {
        for (i = 0; i < size-j-1; i++)
        {
             if (data[i] > data[i+1])
             {
                 int tmp = data[i];
                 data[i] = data[i+1];
                 data[i+1] = tmp;
             }
         }
     }
 }
int mergeSort(int *up, int *down, int l, int r)
{
  if (l == r)
  {
      return 0;
  }

  int mid =(l + r) * 0.5;

  mergeSort(up, down, l, mid);
  mergeSort(up, down, mid + 1, r);

  int i = l;
  int j = mid + 1;
  int step;
  for(step = 0; step < r - l + 1; step++)
  {
      if((j > r) || ((i <= mid) && (up[i] < up[j])))
      {
        down[step] = up[i];
        i++;
      }
      else
      {
          down[step] = up[j];
          j++;
      }
  }

  for(step = 0; step < r - l + 1; step++)
  {
      up[l+step]=down[step];
  }
}


void sortMerge(int *data, int size)
{

    int *down = malloc(size * sizeof(int));
    if (down == NULL)
    {
        printf("malloc failed\n");
        return;
    }
    data = mergeSort(data, down, 0, size);
    free(down);
}


int main()
{
    int n = 100000000;
    int *data;
    data = (int*)malloc(n * sizeof(int));
    if (data == NULL)
    {
        printf("malloc failed\n");
        return 0;
    }

    srand(time(NULL));
    int i;
    for (i = 0; i < n; i++)
    {
        data[i] = rand();
    }

    clock_t begin,delta;

    begin = clock();
    sortCount(data,n);
    free(data);
    delta  = (clock() - begin);
    printf("time: %.4f", (double)delta/CLOCKS_PER_SEC);

    return 0;
}
/*	size     n       n^2    n*logn
    	5   0.0000	0.0000	0.00000
	10  	0.0000 	0.0000 	0.0000
	100 	0.0000	0.0000	0.0000
	1k  	0.0000 	0.0030  0.0000
	10k 	0.0100	0.3580	0.0000
	100k	0.0100 	37.600  0.0000
	1M  	0.0070 	n/a	0.2710
	10M 	0.0620	n/a     2.8770
    	100M	0.5600	n/a     27.8780 */

