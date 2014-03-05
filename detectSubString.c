/*----detectSubString.c----*/
#include<stdio.h>
#include<string.h>

int detectSubString(char search[],char toBeSearched[])
{
  int i=0;
  while(toBeSearched[i]!='\0')
  {
      int k=0; int j=i;
      while(search[k]!='\0')
      {
                  int save=j;
                  if(search[k]==toBeSearched[j])
                  {
                       k++;j++; 
                       if(search[k]=='\0')return save;
                  }
                  else
                   break;
      }
      i++;
  }
   return 0;
}
/*
void main()
{
 printf("%d",detect("Hello1","Hello1World"));
}
*/
