/*-------extractPart2.c--------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int match(char input1[],char input2[])
{
  
  int i=0;
  int flag=1;
  int len1,len2;

  len1=strlen(input1);
  len2=strlen(input2);
  
  if(len1!=len2)
  {
   //printf("%s not match with %s as length not match\n",input1,input2);
   return 0;
  }
  while(input1[i]!='\0')
  {
    if(input1[i]==input2[i])i++;
    else
     {
    // printf("%c not match with %c\n",input1[i],input2[i]);
     flag=0;
     break;
     }
  }
  return flag;
}

int detectBreak(char content[])
{ 
 int i=0,k;
 char storeToMatchWithBreak[6];
 while(content[i]!='\0')
 {
   for(k=0;k<5;k++)
   storeToMatchWithBreak[k]=content[k+i];
   storeToMatchWithBreak[k]='\0';
   if(match(storeToMatchWithBreak,"break")==1)
   return 1;
   i++;
 }
 return 0;
}

int detectDefault(char content[])
{ 
 int i=0,k;
 char storeToMatchWithDefault[8];
 while(content[i]!='\0')
 {
   for(k=0;k<7;k++)
   storeToMatchWithDefault[k]=content[k+i];
   storeToMatchWithDefault[k]='\0';
   if(match(storeToMatchWithDefault,"default")==1)
   return 1;
   i++;
 }
 return 0;
}
int countCases(char input[])
{
 int i=0,j;
 char storeToMatchWithCase[5];
 int count=0;
 while(input[i]!='\0')
 {
   for(j=0;j<4;j++)
   storeToMatchWithCase[j]=input[i+j];
   storeToMatchWithCase[j]='\0';
   //printf("%s\n",storeToMatchWithCase);
   if(match(storeToMatchWithCase,"case")==1)
   {
       //printf("Count of case incremented\n");       
       ++count;
   } 
   i++;  
 }
 return count;
}
void extractDefaultInfo(char output[],char input[])
{
 int i=0,k,l=0;
 char storeToMatchWithDefault[8];
 while(input[i]!='\0')
 {
   for(k=0;k<7;k++)
   storeToMatchWithDefault[k]=input[k+i];
   storeToMatchWithDefault[k]='\0';
   if(match(storeToMatchWithDefault,"default")==1)
   break;
   i++;
 }
 while(input[i]!=':')i++;
 while(input[i]!='}')
 {
  output[l++]=input[i++];
 }
 output[l]='\0';
}
void extractCaseContent(char output[],char outputCondition[],char input[],int numberOfCase)
{
 char storeToMatchWithCase[100],storeToMatchWithDefault[100];
 int p=0;
 int count;
 char storeContent[200];
 int j=0,k=0,i=0,l=0;
 while(input[i]!='\0')
 {
  storeContent[j++]=input[i];

   if(numberOfCase==countCases(storeContent))
   {
        //printf("%s\n",storeContent);
        break; 
   }
  i++;
 }
 /*while(input[i]!='\0')
 {
  printf("%c",input[i]);i++;
 }
 */
 while(input[i]!=':')
 {
   if((input[i]!=' ')&&(input[i]<=57&&input[i]>=48))
   {
    outputCondition[l++]=input[i];

   } 
    i++;
 }
     outputCondition[l]='\0';
 
 while(1)
 {
   for(k=0;k<4;k++)
   storeToMatchWithCase[k]=input[i+k];
   storeToMatchWithCase[k]='\0';
   for(k=0;k<7;k++)
   storeToMatchWithDefault[k]=input[i+k];
   storeToMatchWithDefault[k]='\0';
   if(match(storeToMatchWithCase,"case")==1)break;
   if(match(storeToMatchWithDefault,"default")==1)break;
   if(input[i]=='}')break;
   
   output[p++]=input[i++];
 }
 output[p]='\0';
}


void extractForInitializationInfo(char output[],char input[])
{
  int i=0,j=0;

  while(input[i]!='(')
  i++;

  while(input[i]!=';')
  {
   output[j++]=input[++i];
  }
  output[j]='\0';
}
void extractForConditionInfo(char output[],char input[])
{
  int i=0,j=0;
  while(input[i]!='(')
  i++;
  while(input[i]!=';')
  i++;
  i++;//skip ';'
  while(input[i]!=';')
  {
   output[j++]=input[i];i++;
  }
  output[j]='\0';
}

void extractForIncrementInfo(char output[],char input[])
{
  int i=0,j=0;
  while(input[i]!='(')
  i++;
  while(input[i]!=';')
  i++;
  i++;
  while(input[i]!=';')
  i++;
  i++;
  while(input[i]!=')')
  {
   output[j++]=input[i];i++;
  }
  output[j]='\0';
}

void extractStartingRoundBracketData(char output[],char input[])
{
  int i=0,j=0,k,l,len;
  int bracketCount=0;
  
  while(input[i]!='(')
  i++;
  
  while(1)
  {
    if(input[i]=='(')bracketCount++;
    if(input[i]==')')bracketCount--;
    output[j++]=input[i];
    if(bracketCount==0)break;
    i=i+1;
  }
  output[j]='\0';
  
} 

void extractEndingRoundBracketData(char output[],char input[])
{
  int i=0,j=0,k,l,len;
  int bracketCount=0;

  
  while(input[i]!='{')
  i++;
  
  while(1)
  {
    if(input[i]=='{')bracketCount++;
    if(input[i]=='}')bracketCount--;
    if(bracketCount==0)break;
    i=i+1;
  }

  while(input[i]!='(')
  i++;
  
  while(1)
  {
    if(input[i]=='(')bracketCount++;
    if(input[i]==')')bracketCount--;
    output[j++]=input[i];
    if(bracketCount==0)break;
    i=i+1;
  }
  output[j++]='\0';
} 


void extractIfConditionByNumber(int number,char input[],char output[])
{
  int k=0,countIf=0,i=0,j=0,bracketCount=0;printf("LOOK :%s",input);
  while(input[k]!='\0')
  {
    if((input[k]=='i')&&(input[k+1]=='f'))
    {printf("detected if");
        countIf++;
        if(countIf>=number)
        {
		  while(input[k]!='(')
		  k++;
		  
		  while(1)
		  {
		    if(input[k]=='(')bracketCount++;
		    if(input[k]==')')bracketCount--;
		    output[j++]=input[k];
		    if(bracketCount==0){output[j]='\0';return;}
		    k=k+1;
		  }
		  
        }
    }
    k++;
  } 
}


void extractProcessingInfo(char output[],char input[])
{
  int i=0,j=0,k,l,len;
  int bracketCount=0;
  len=strlen(input);
  
  while(input[i]!='{')
  i++;
  
  while(1)
  {
    if(input[i]=='{')bracketCount++;
    if(input[i]=='}')bracketCount--;
    output[j++]=input[i];
    if(bracketCount==0)break;
    i=i+1;
  }
  output[j]='\0';
} 

void extractProcessingInfoByNumber(int number,char output[],char input[])
{
  int i=0,j=0,k=0,len;
  int bracketCount=0;
  len=strlen(input);
  
     while(k<number)
     {
	  while(input[i]!='{')
	  i++;	
	  
	  while(1)
	  {
		    if(input[i]=='{')bracketCount++;
		    if(input[i]=='}')bracketCount--;
		   // output[j++]=input[i];
		    if(bracketCount==0)break;
		    i=i+1;
	  }
	  //output[j]='\0';
	  i++;
	  k++;
      }


	while(input[i]!='{')
			i++;
  
  	while(1)
  	{
	    		if(input[i]=='{')bracketCount++;
	    		if(input[i]=='}')bracketCount--;
	    		output[j++]=input[i];
	    		if(bracketCount==0)break;
	    		i=i+1;
  	}

       output[j]='\0';

}

void extractElseProcessingInfo(char output[],char input[])
{
  int i=0,j=0;
  int bracketCount=0;

  while(input[i]!='{')
  {
   i++;
  }
  while(1)
  {
    if(input[i]=='{')bracketCount++;
    if(input[i]=='}')bracketCount--; 
    if(bracketCount==0)break;
    i++;
  }
    
  //if node ended
  while(input[i]!='{')
  i++;
  
  while(1)
  {
    if(input[i]=='{')bracketCount++;
    if(input[i]=='}')bracketCount--;
    output[j++]=input[i];
    if(bracketCount==0)break;
    i=i+1;
  }
  output[j]='\0';
} 
/*
void main()
{
  FILE *fp;
  char defaultContent[100],content[100],contentInput[100],caseContent[100],caseCondition[100];
  int numberOfCases;
  int i=1;

  fp=fopen("sampleFile","r");
  extractWhile_For_SwitchContent(contentInput,fp);
  printf("%s\n\n\n\n",contentInput);
  numberOfCases=countCases(contentInput);
  while(i<=numberOfCases)
  {
    extractCaseContent(caseContent,caseCondition,contentInput,i);
    printf("Break present? : %d\n",detectBreak(caseContent));
  }
  extractDefaultInfo(defaultContent,contentInput);
  printf("%s\n",defaultContent);
}
*/
