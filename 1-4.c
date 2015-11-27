#include <stdio.h>
size_t strlen(char *src)
{
    int count = 0;
    while (src[count] != '\0')
    {
        count++;
    }
    return count;
}

size_t strctt(char *dst, char *src)
  {
      int i = 0;
      int j = 0;
      while (dst[i]!= '\0')
      {
          i++;
      }
          while(dst[j]!= '\0')
          {
              dst[i] = src[j];
              i++;
              j++;
          }
          dst[i] = '\0';
  }
  

size_t strcpy(char *dst, char *src)
  {
      int i = 0;
      while (src[i] != '\0')
      {
          dst[i]=src[i];
          i++;
      }
      dst[i] = '\0';

  }

size_t strcmp(char *s1, char *s2)
  {
      int i = 0;
      int k = 0;
      while (s1[i] == s2[i])
             {
                   i++;
             };
      return s1[i] - s2[i];
  }
