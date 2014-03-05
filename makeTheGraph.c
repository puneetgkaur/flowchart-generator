/*----------makeTheGraph.c-----------*/
#include "formNodes.c"
void makeTheGraph(char functionBody[],NODE **head,NODE **tail)
{
   int i=0;int firstTime=0,flag=0;char ch;char contentOfFunctionDetected[10000];int constructNumber;
  NODE *previousNode,*startNode,*newNode;
  startNode=NULL;
  startNode=insertNode(&startNode,++nodeNumber);
  previousNode=startNode;
  *head=startNode;
  
   while((ch=functionBody[i])!='\0')
   {
       NODE* newNode;
       newNode=insertNode(&startNode,++nodeNumber);
       insertEdge(&startNode,previousNode->nodeNo,newNode->nodeNo); 
       //newNode->content[0]='\0';
       int k=0;
       while(((constructNumber=detectConstruct(functionBody,i))==0))/*&&(ch!='}')*/
       {       
         ch=functionBody[i++];
         if(ch=='\0'){flag=1;break;} 
         newNode->content[k++]=ch;//insertCharacter(newNode->content,ch);
       }display(&newNode);
       if(flag==1){newNode->content[k]='\0';break;}
	newNode->content[k]='\0';
       extractContent(contentOfFunctionDetected,functionBody,&i,constructNumber);printf("--%s--",contentOfFunctionDetected);
       previousNode=formNode(&startNode,&newNode,constructNumber,contentOfFunctionDetected);  display(&previousNode);
   }
   if(flag==1)*tail=newNode;
   else
   *tail=previousNode;
   // printAdjacencyMatrix(head);
}

