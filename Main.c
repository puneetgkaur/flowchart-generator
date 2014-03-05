/*----------------Main.c-----------------*/
#include<stdio.h>
#include<string.h>
#include "makeTheGraph.c"
#include "FunctionList.c"
#include "insertFunction.c"
#include "numberOfPaths.c"
#include "generateAllTestCases.c"
void main(int argc,char* argv[])
{

  //The command line input represent the number of int, float, char ,string in the input of the teacher code
  int numOfInt,numOfFloat,numOfChar,numOfString;
  numOfInt=atoi(argv[1]);
  numOfFloat=atoi(argv[2]);
  numOfChar=atoi(argv[3]);
  numOfString=atoi(argv[4]);
  //Then if numOfString is greater than zero the following digits depict the maimum length of each string possible
  int *limitForEachString;
  limitForEachString=(int*)malloc(numOfString*sizeof(int));
  int i;
  for(i=0;i<numOfString;i++)
  {
       limitForEachString[i]=atoi(argv[5+i]);
  }

  char ch;
  struct Functions *startFunctionNode;
  startFunctionNode=NULL;
  FILE *fp=fopen("test.c","r");
  while((ch=getc(fp))!=EOF)
  {
	int bracketCount=0;
	//NODE *head,*tail;
        if(ch=='{')
        {printf("1");
	char functionName[10000];
	char functionBody[10000];
        int flag=0;
        while((ch!=';')&&(ch!='}')&&(ch!='>'))
	{
           fseek(fp,-1,SEEK_CUR);ch=fgetc(fp);fseek(fp,-1,SEEK_CUR);//as fgetc increments fp !
        }
        fseek(fp,+1,SEEK_CUR);
	int i=0;
        int j=0;
	while(ch!='{')
	{printf("2");
		functionName[i++]=ch;ch=fgetc(fp);//printf("ch=%c",ch);
	}
	 functionName[i]='\0';
         int bracketCount=0;printf("ch=%c",ch);
         do
	{
				if(ch=='}')bracketCount--;
				functionBody[j++]=ch;
				if(ch=='{')bracketCount++;
		                ch=fgetc(fp);
				if(bracketCount==0)break;
	}while(bracketCount!=0);
        functionBody[j]='\0';
        printf("Function Name \n: %s  \nFunction Body :\n %s\n\n",functionName,functionBody);
        NODE *head,*tail;
	makeTheGraph(functionBody,&head,&tail);
        addFunction(&startFunctionNode,functionName,&head,&tail);	
     }
  }
  traverseFunctions(&startFunctionNode);
  insertFunctions(&startFunctionNode);
  traverseFunctions(&startFunctionNode);
  int paths=numberOfPaths(&startFunctionNode); 
  printf("Number of paths : %d",paths);
  generateTestCases(paths,numOfInt,numOfFloat,numOfChar,numOfString,limitForEachString);
}
