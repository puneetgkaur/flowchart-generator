/*-------detectConstruct.c-------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int detect(char input[],int position,char pattern[])
{
    int k=position;
    int len=strlen(pattern);
    int i=0;
   while(i<len)
   {
      if(input[k++]!=pattern[i++])
      return 0;
   }
   return 1;
}

int detectConstruct(  char input[],int startingPos  )
{
 if(detect(input,startingPos,"if")==1)return 1;
 else if(detect(input,startingPos,"while")==1) return 2;
 else if(detect(input,startingPos,"do")==1)return 3;
 else if(detect(input,startingPos,"for")==1) return 4;
 else if(detect(input,startingPos,"switch")==1) return 5;
 else return 0;
}
int detectIfType(char content[])
{
   int i=0;printf("%s",content);
   while(content[i]!='\0')
   {
      if((content[i]=='e')&&(content[i+1]=='l')&&(content[i+2]=='s')&&(content[i+3]=='e')&&(content[i+5]=='i')&&(content[i+6]=='f'))return 3;
      if((content[i]=='e')&&(content[i+1]=='l')&&(content[i+2]=='s')&&(content[i+3]=='e'))
      return 2;      
      i++;     
   }
   return 1; 
}

int detectNumOfElse(char content[])
{
   int i=0,count=0;
   while(content[i]!='\0')
   {
      if((content[i]=='e')&&(content[i+1]=='l')&&(content[i+2]=='s')&&(content[i+3]=='e'))
      count=count+1;  
      i++;     
   } 
   return count;
}

int detectElse(char input[],int position)
{
  int k=position;char ch;
  while(((ch=input[k++])!='{')&&(ch!=';'))
  {
      if((ch=='e')&&(input[k++]=='l')&&(input[k++]=='s')&&(input[k++]=='e'))
      return 1;
  }
  return 0;
}
