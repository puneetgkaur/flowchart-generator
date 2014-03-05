/*---generateAllTestCases.c---*/
#include "generateRandomTestCase.c"
#include "TestCaseLinkedList.c"
char TestCase[1000];
char GeneratedPath[10000];
void compile()
{
       char compileCommand[1000];
       strcpy(compileCommand,"gcc -o obj1 ");
       strcat(compileCommand,"Modified.c"); 
       printf("compile command : \n%s\n",compileCommand);
       system(compileCommand);  
}
void run()
{
       char runCommand[1000];
       strcpy(runCommand,"./obj1 ");
       strcat(runCommand,TestCase);
       printf("Run Command : \n%s\n",runCommand);
       system(runCommand);
}
void generatePath()
{
       compile();
       run();
       char ch;
       int i=0;
       FILE *fp;
       fp=fopen("PathGenerated.txt","r");
       while((ch=fgetc(fp))!=EOF)
       {
               GeneratedPath[i++]=ch;
       }                 
       GeneratedPath[i]='\0';
       fclose(fp);
}
int uniqueTestCase(struct TestCaseList **start)
{
      struct TestCaseList *temp;
      temp=*start;
      while(temp!=NULL)
      {
             if(strcmp(temp->TestCaseData,GeneratedPath)==0) return 0;
             temp=temp->next;
      }
      return 1;
}

generateTestCases(int paths,int numOfIntInput,int numOfFloatInput,int numOfCharInput,int numOfStringInput,int LimitForEachString[] )
{
   struct TestCaseList *start,*start2;
   start=NULL;start2=NULL;
   char randomTestCase[1000];
   int numberOfTestCases=0;
   generateRandomTestCase(randomTestCase,numOfIntInput,numOfFloatInput,numOfCharInput,numOfStringInput,LimitForEachString);
   strcpy(TestCase,randomTestCase);
   insertTestCase(&start,randomTestCase);
   generatePath();printf("\nGenerated Path : %s\n",GeneratedPath);
   insertTestCase(&start2,GeneratedPath);
   while(numberOfTestCases<(paths-1))
   {
   if(uniqueTestCase(&start2))
   {
          insertTestCase(&start,randomTestCase);
          insertTestCase(&start2,GeneratedPath);
          numberOfTestCases++;
   }
   else
   {
          generateRandomTestCase(randomTestCase,numOfIntInput,numOfFloatInput,numOfCharInput,numOfStringInput,LimitForEachString);
          strcpy(TestCase,randomTestCase);
          generatePath();printf("\nGenerated Path : %s\n",GeneratedPath);
   }
   }
   printf("\nPaths Generated \n");
   traverseTestCases(&start2);
   printf("\nTest Cases \n");
   traverseTestCases(&start);
}
