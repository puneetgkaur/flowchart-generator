/*--------TestCaseLinkedList.c--------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct TestCaseList
{
  char TestCaseData[1000];
  struct TestCaseList *next;
};

void insertTestCase(struct TestCaseList **start,char str[])
{

  struct TestCaseList *temp,*new;
  temp=*start;
  if(temp==NULL)
  {
      struct TestCaseList *new;
      new=(struct TestCaseList *)malloc(sizeof(struct TestCaseList)); 
      strcpy(new->TestCaseData,str);
      new->next=NULL;
      *start=new;
  }
  else
  {
  //    struct TestCase *temp;
      //temp=*start;
      while(temp->next!=NULL)temp=temp->next;
      new=(struct TestCaseList*)malloc(sizeof(struct TestCaseList)); 
     strcpy(new->TestCaseData,str);
     new->next=NULL;
      temp->next=new;
  }
}
void traverseTestCases(struct TestCaseList **start)
{
  struct TestCaseList *temp;
  temp=*start;
  while(temp!=NULL)
  {
   printf("%s\n",temp->TestCaseData);
   temp=temp->next;
  }
}
/*
void main()
{
   struct TestCaseList *start;
   start=NULL;
   char str[1000];
   strcpy(str,"Hello");
   insert(&start,str);
   strcpy(str,"Good");
   insert(&start,str);
   traverse(&start);
}
*/
