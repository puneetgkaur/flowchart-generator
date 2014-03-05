/*------extractConstruct.c------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "detectConstruct.c"

void extractIfContent(char content[],char input[],int* position )
{
  int i=0;
  int k=*position;
  char ch;
  int bracketCount=0;
  while(((ch=input[k++])!='{')&&(ch!=';'))
  {
     content[i++]=ch;//printf("%c",ch);
  }
  if(ch==';')
  {
    content[i++]='\0';
    return;
  }


  //extracted if part
  while(1)
  {
    if(ch=='{')bracketCount++;
    if(ch=='}')bracketCount--;
    content[i++]=ch;
    ch=input[k++];
    if(bracketCount==0)break;
  }

  while(detectElse(input,k)==1)
  {
	  while((ch=input[k++])!='{')
	  content[i++]=ch;
	  content[i++]=ch;
	  while(1)
	  {
	    if(ch=='{')bracketCount++;
	    if(ch=='}')bracketCount--;
	    ch=input[k++];
	    content[i++]=ch;
	    if(bracketCount==0)break;
	   }  
  }
  *position=k;
  content[i++]='\0'; printf("::%s::",content);
}
/*
void extractIf1Content(char content[],char input[],int position)
{
  int i=0;  int k=position;
  char ch;
  int bracketCount=0;
  while((ch=input[k++])!='{')
  content[i++]=ch;
  content[i++]=ch;
  while(1)
  {
    if(ch=='{')bracketCount++;
    if(ch=='}')bracketCount--;
    ch=input[k++];
    content[i++]=ch;
    if(bracketCount==0)break;
  }  
  while((ch=input[k++])!='{')
  content[i++]=ch;
  content[i++]=ch;
  while(1)
  {
    if(ch=='{')bracketCount++;
    if(ch=='}')bracketCount--;
    ch=input[k++];
    content[i++]=ch;
    if(bracketCount==0)break;
  }  
  content[i++]='\0';
}
*/


void extractWhile_For_SwitchContent(char content[],char input[],int* position)
{

  int i=0;  int k=*position;
  char ch;
  int bracketCount=0;

  while((ch=input[k++])!='{')
  content[i++]=ch;

  content[i++]=ch;

  while(1)
  {

    if(ch=='{')bracketCount++;
    if(ch=='}')bracketCount--;
    ch=input[k++];
    content[i++]=ch;
    if(bracketCount==0)break;
  }  
  *position=k;
  content[i++]='\0';
}


void extractDoContent(char content[],char input[],int* position)
{

  int i=0;  int k=*position;
  char ch;
  int bracketCount=0;

  while((ch=input[k++])!='{')
  content[i++]=ch;

  content[i++]=ch;

  while(1)
  {

    if(ch=='{')bracketCount++;
    if(ch=='}')bracketCount--;
    ch=input[k++];
    content[i++]=ch;
    if(bracketCount==0)break;
  }  

  while((ch=input[k++])!=';')
  {
   content[i++]=ch;
  }
   *position=k;
  content[i++]='\0';

}

void extractContent(char content[],char input[],int* position,int constructNumber)
{
	 switch(constructNumber)
	 {
			  case 1:extractIfContent(content,input,position);break;
			  case 2:extractWhile_For_SwitchContent(content,input,position);break;
			  case 3:extractDoContent(content,input,position);break;
			  case 4:extractWhile_For_SwitchContent(content,input,position);break;
			  case 5:extractWhile_For_SwitchContent(content,input,position);break;
	 }
}


/*
void main(int argc,char* argv[])
{
  char input[],int position;
  char contentInput[1000];
  fp=fopen("IfExample.c","r");printf("Reached Here\n");
  extractIfContent(contentInput,fp);
  printf("%s",contentInput);
}
*/ 
