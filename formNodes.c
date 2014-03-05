/*----formNodes.c------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "graph.c"
#include "extractConstruct.c"
#include "extractPart2.c"

NODE* formDummyNode(NODE **startNode);
NODE* formIndividualNode(NODE ** startNode,NODE** previousNode,char content[],char type[]);
NODE* formProcessingNode(NODE **startNode,NODE** previousNode,char content[]);

NODE* formIf1(NODE **startNode,NODE **previousNode,char content[])
{
  char content1[1000],content2[1000];
  NODE * conditionNode;
  NODE * ifNode;
  NODE * dummyNode;printf("if 1 form");
  //seperating content
  extractStartingRoundBracketData(content1,content);//Info between '(' and ')' 
   printf("conditionInfo : %s",content1);
  extractProcessingInfo(content2,content);//Info between '{' and '}'  
   printf("processingInfo : %s",content2);
  //creating nodes
  conditionNode=formIndividualNode(startNode,previousNode,content1,"condition");display(&conditionNode);
  ifNode=formProcessingNode(startNode,&conditionNode,content2);display(&ifNode);
  dummyNode=formDummyNode(startNode);display(&dummyNode);

  insertEdge(startNode,ifNode->nodeNo,dummyNode->nodeNo);
  insertEdge(startNode,conditionNode->nodeNo,dummyNode->nodeNo);

  return dummyNode; 
}

NODE* formIf2(NODE **startNode,NODE **previousNode,char content[])
{
  int i=0;
  char content1[1000],content2[1000],content3[1000];
  NODE * conditionNode;
  NODE * ifNode;
  NODE * elseNode;
  NODE * dummyNode;
 
  //seperating content
  extractStartingRoundBracketData(content1,content);//Info between '(' and ')' 
  extractProcessingInfo(content2,content);//Info between '{' and '}'  
  extractElseProcessingInfo(content3,content);//Info between '{' and '}' 
  
  //creating nodes
  conditionNode=formIndividualNode(startNode,previousNode,content1,"condition");
  //printf("9\n");
  ifNode=formProcessingNode(startNode,&conditionNode,content2);
  elseNode=formProcessingNode(startNode,&conditionNode,content3);
  dummyNode=formDummyNode(startNode);
  
  //creating edges
  insertEdge(startNode,ifNode->nodeNo,dummyNode->nodeNo);
  insertEdge(startNode,elseNode->nodeNo,dummyNode->nodeNo);

  return dummyNode; 
}

NODE* formIf3(NODE **startNode,NODE **previousNode,char content[])
{
  int k;
  char tempContent1[2000],tempContent2[2000],tempContent[2000],tempContent3[2000];
  NODE  * tempNode1,*tempNode2,*conditionNode,*ifNode,*elseNode,*dummyNode;
  tempNode1=NULL;tempNode2=NULL;int flag=0;
  k=detectNumOfElse(content);//printf("Else :%d",k);  
       printf("SEE _ %s",content);
   while(1)
  {
     if(flag==0)
     {
       extractProcessingInfoByNumber(k,tempContent1,content);printf("NOTE 1:%s",tempContent1);
       extractProcessingInfoByNumber(k-1,tempContent2,content);printf("NOTE 2:%s",tempContent2);
       extractIfConditionByNumber(k,content,tempContent3);printf("NOTE 3:%d;%s",k,tempContent3);
       conditionNode=insertNode(startNode,++nodeNumber);
       strcpy(conditionNode->type,"condition");
       strcpy(conditionNode->content,tempContent3);display(&conditionNode);
       ifNode=formProcessingNode(startNode,&conditionNode,tempContent2);display(&ifNode);
       elseNode=formProcessingNode(startNode,&conditionNode,tempContent1);display(&elseNode);
       tempNode1=conditionNode;
       tempNode2=dummyNode=formDummyNode(startNode);display(&dummyNode);
       insertEdge(startNode,ifNode->nodeNo,dummyNode->nodeNo);
       insertEdge(startNode,elseNode->nodeNo,dummyNode->nodeNo);
       k=k-2;flag=1;
     }
     else
     {
       extractProcessingInfoByNumber(k,tempContent1,content);printf("NOTE 4:%s",tempContent1);
       extractIfConditionByNumber(k+1,content,tempContent3);printf("NOTE 5:%d;%s",k,tempContent3);
       conditionNode=insertNode(startNode,++nodeNumber);
       strcpy(conditionNode->type,"condition");
       strcpy(conditionNode->content,tempContent3);display(&conditionNode);
       ifNode=formProcessingNode(startNode,&conditionNode,tempContent1);    display(&ifNode);
       dummyNode=formDummyNode(startNode);display(&dummyNode);
       insertEdge(startNode,conditionNode->nodeNo,tempNode1->nodeNo);
       insertEdge(startNode,ifNode->nodeNo,dummyNode->nodeNo);
       insertEdge(startNode,tempNode2->nodeNo,dummyNode->nodeNo);
       tempNode2=dummyNode; tempNode1=conditionNode;
       if(k<=0)
       break;
       k=k-1;
     }    
     
     
  }
  NODE *tempNode3;tempNode3=*previousNode;
  insertEdge(startNode,tempNode3->nodeNo,tempNode1->nodeNo );
 // return tempNode2;
return tempNode2;
}

NODE* formIfNode(NODE **startNode,NODE **previousNode,char content[])
{
  int ifType;NODE * lastOfAllIfNodes;//lastOfAllIfNodes=formDummyNode(startNode);
  ifType=detectIfType(content);//1.if without else,2.if with else,3.if with else if's
printf("IfType : %d",ifType);
  switch(ifType)
  {
     case 1:lastOfAllIfNodes=formIf1(startNode,previousNode,content);break;
     case 2:lastOfAllIfNodes=formIf2(startNode,previousNode,content);break;
     case 3:printf(":)");lastOfAllIfNodes=formIf3(startNode,previousNode,content);break;
  }
  return lastOfAllIfNodes;
}

NODE* formWhileNode(NODE **startNode,NODE **previousNode,char content[])
{
  char content1[1000];
  char content2[1000];
  NODE* conditionNode;
  NODE* processingNode;
  NODE * dummyNode;
  //seperating content
  extractStartingRoundBracketData(content1,content);//Info between '(' and ')' 
  extractProcessingInfo(content2,content);//Info between '{' and '}' 
  //forming Nodes
  conditionNode=formIndividualNode(startNode,previousNode,content1,"condition");
  processingNode=formProcessingNode(startNode,&conditionNode,content2);
  dummyNode=formDummyNode(startNode);
  insertEdge(startNode,processingNode->nodeNo,dummyNode->nodeNo);
  insertEdge(startNode,dummyNode->nodeNo,conditionNode->nodeNo);
  return conditionNode;
}

NODE* formDoNode(NODE **startNode,NODE **previousNode,char content[])
{ 
  char content1[1000],content2[1000];
  NODE * dummyNode;
  NODE* conditionNode;
  NODE* processingNode;

  //seperating content
  extractProcessingInfo(content1,content);
  extractEndingRoundBracketData(content2,content);
 
  //forming Nodes
  dummyNode=formDummyNode(startNode);
  processingNode=formProcessingNode(startNode,&dummyNode,content1);
  conditionNode=formIndividualNode(startNode,&processingNode,content2,"condition");

  //insert Edges of construct
  insertEdge(startNode,(*previousNode)->nodeNo,dummyNode->nodeNo); 
  insertEdge(startNode,conditionNode->nodeNo,dummyNode->nodeNo);

  return conditionNode;
}

NODE* formForNode(NODE **startNode,NODE **previousNode,char content[])
{
   char content1[1000],content2[1000],content3[1000],content4[1000];
   NODE* initializationNode;
   NODE* conditionNode;
   NODE* processingNode;
   NODE* incrementalNode;
   
   //seperating content
   
   extractForInitializationInfo(content1,content);
   //printf("%s",content1);
   extractForConditionInfo(content2,content);
   extractForIncrementInfo(content3,content);
   extractProcessingInfo(content4,content);
   //printf("%s",content4);
   //forming Nodes
printf("%s",content3);
   initializationNode=formIndividualNode(startNode,previousNode,content1,"initialization");
   display(&initializationNode);
   conditionNode=formIndividualNode(startNode,&initializationNode,content2,"condition");
   display(&conditionNode);
   processingNode=formProcessingNode(startNode,&conditionNode,content4);
   display(&processingNode);
   incrementalNode=formIndividualNode(startNode,&processingNode,content3,"incremental");
   display(&incrementalNode);

   //insert the edge for creating a loop
   insertEdge(startNode,incrementalNode->nodeNo,conditionNode->nodeNo);
       
return conditionNode;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
}

NODE* formSwitchNode(NODE **startNode,NODE **previousNode,char content[])
{
   char content1[1000],caseProcess[1000],caseCondition[1000],defaultInfo[1000];
   int i=1,numberOfCases;
   NODE* dataNode;
   NODE* defaultPreviousNode;
   NODE* dummyNode,*defaultDummyNode;
   NODE* prevCaseNode,*prevProcessNode;
   NODE* defaultProcessingNode;
   NODE* caseNode;
   NODE* processNode;
      
      
   //seperating content
   extractStartingRoundBracketData(content1,content);
   
   //forming Nodes
   dataNode=formIndividualNode(startNode,previousNode,content1,"data");
   dummyNode=formDummyNode(startNode);  
 

   numberOfCases=countCases(content); //includes the default node too 
   prevCaseNode=dataNode;  
   prevProcessNode=NULL;
   while(i<=numberOfCases)
   {
  
      //Extracting content of the case node
      extractCaseContent(caseProcess,caseCondition,content,i);

      //Form the nodes
      caseNode=formIndividualNode(startNode,&prevCaseNode,caseCondition,"condition");
      display(&caseNode);
      processNode=formIndividualNode(startNode,&caseNode,caseProcess,"processing");
      display(&processNode);
      //To be careful for first one
      //Inserting Edges
            if(prevProcessNode!=NULL)
      {
       insertEdge(startNode,prevProcessNode->nodeNo,processNode->nodeNo);     
      }

      if(detectBreak(caseProcess)==1)
      {
         prevProcessNode=NULL;
         insertEdge(startNode,processNode->nodeNo,dummyNode->nodeNo);
         defaultPreviousNode=NULL;
      }
      else
      {
         prevProcessNode=processNode;
         defaultPreviousNode=processNode;       
      }
      

      //updating prevCaseNode and prevProcessNode
      prevCaseNode=caseNode;     
      i++;
   }   
 

   if(detectDefault(content)==1)
   {
     defaultDummyNode=formDummyNode(startNode);
     display(&defaultDummyNode);
     insertEdge(startNode,prevCaseNode->nodeNo,defaultDummyNode->nodeNo);
    extractDefaultInfo(defaultInfo,content);
     defaultProcessingNode=formIndividualNode(startNode,&defaultDummyNode,defaultInfo,"processing");
     display(&defaultProcessingNode);
     if(defaultPreviousNode!=NULL)
     insertEdge(startNode,defaultPreviousNode->nodeNo,defaultProcessingNode->nodeNo);   
     insertEdge(startNode,defaultProcessingNode->nodeNo,dummyNode->nodeNo);
   } 
   return dummyNode;  
}

NODE* formNode(NODE **startNode,NODE **previousNode,int construct,char content[])
{
  switch(construct)
  {
    case 1:return formIfNode(startNode,previousNode,content);
    case 2:return formWhileNode(startNode,previousNode,content);
    case 3:return formDoNode(startNode,previousNode,content);
    case 4:return formForNode(startNode,previousNode,content);
    case 5:return formSwitchNode(startNode,previousNode,content);
  }
}
NODE* formDummyNode(NODE **startNode)
{
 NODE *newNode;
 newNode=insertNode(startNode,++nodeNumber);
 strcpy(newNode->type,"dummy");
 return newNode;
}

NODE* formIndividualNode(NODE ** startNode,NODE** previousNode,char content[],char type[])
{
 NODE *newNode,*tempPreviousNode;
 tempPreviousNode=*previousNode;
 newNode=insertNode(startNode,++nodeNumber);
 if(previousNode!=NULL)
 insertEdge(startNode,tempPreviousNode->nodeNo,newNode->nodeNo);
 strcpy(newNode->content,content);
 strcpy(newNode->type,type);
 return newNode;
}
NODE* formProcessingNode(NODE **startNode,NODE** previousNode,char content[])
{
 int i ;
 char ch;
 char extractedContent[10000];
 int length;
 int constructNumber;
 NODE *newNode,*tempPreviousNode;
 tempPreviousNode=*previousNode;
 printf("C=--%s--",content);
 int k=0;
 while((ch=content[k])!='\0')
 {
    newNode=insertNode(startNode,++nodeNumber);
    strcpy(newNode->type,"processing");
    insertEdge(startNode,tempPreviousNode->nodeNo,newNode->nodeNo);
    int j=0;
    newNode->content[0]='\0';
    while(((constructNumber=detectConstruct(content,k))==0))/*&&(ch!='}')*/
  {
   ch=content[k++];
   if(ch=='\0'){printf("returning..NewNode..");display(&newNode);newNode->content[j]='\0';return newNode;}
   newNode->content[j++]=ch;
   }printf("NewNode");display(&newNode);
   newNode->content[j]='\0';printf("detected : %d",constructNumber);
   extractContent(extractedContent,content,&k,constructNumber);
   tempPreviousNode=formNode(startNode,&newNode,constructNumber,extractedContent);          
 }
  return tempPreviousNode;
}
