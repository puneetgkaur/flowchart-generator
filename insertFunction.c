/*--------insertFunction.c---------*/
#include "detectSubString.c"

void generateNewGraph( NODE **head1,NODE** tail1,NODE** head2,NODE ** tail2 )
{
    NODE *temp1,*temp2,*temp3,*temp4;
    temp1=*head1;temp2=*tail1;temp3=*head2;temp4=*tail2;
    NODE *save;save=NULL;
    while(temp1!=temp2)
    {         
          int k=++nodeNumber;
          NODE *new;
          new=insertNode(head2,k);
          strcpy(new->content,temp1->content);
          strcpy(new->type,temp1->type);

          if(save==NULL)
          *head2=new;
          save=new;
          temp1=temp1->next;
    }
          *tail2=save;
          //inserting the edges
          temp3=*head2;
          temp1=*head1;int i=temp1->nodeNo;int j=temp3->nodeNo;
          int difference=j-i;
          printf("Difference : %d; first : %d,second: %d\n",difference,i,j);
          
          while(temp1!=temp2)
          {
                EDGE *tempEdge;
                tempEdge=temp1->link;
                while(tempEdge!=NULL)
                {
                          int i=temp1->nodeNo;int j=tempEdge->nodeNo;
			  insertEdge(head2,i+difference,j+difference);
                          tempEdge=tempEdge->next;
                }
                temp1=temp1->next;
          }
            NODE * temp,*temp0;temp=*head2;temp0=*tail2;
             while(temp!=temp0)
             {   
            EDGE *edge;edge=temp->link;
            while(edge)
            {
                      // adj[temp->nodeNo][edge->nodeNo]=1;
                      printf("edge from %d to %d\n",temp->nodeNo,edge->nodeNo);
                       edge=edge->next;                   
            }
            temp=temp->next;      
            }
}



void searchFunction( char functionName[],struct Functions *ptr1 , char textToBeSearched[], struct Functions *ptr2,NODE **targetNode )
{
      NODE *tempNode;
      tempNode=*targetNode;
      int detect;
      detect=detectSubString(functionName,textToBeSearched);//returns the value of the position where the function has been detected
     // printf("\ndetect:%d;\nsearching in : %s\n",detect,textToBeSearched);
      if(detect!=0)//detected
      {           
		 printf("detect:%d;\n1.%s;\n",detect,textToBeSearched);
		 int k=detect;
		 int i=0;
                 char textForNewNode[1000];
                 while(textToBeSearched[k]!='\0')           
                 textForNewNode[i++]=textToBeSearched[k++];
		textForNewNode[i]='\0';printf("\n2.%s",textForNewNode);
                 textToBeSearched[detect]='\0';printf("\n3.%s",textToBeSearched);
                 NODE *save=tempNode->next;
                 NODE *newHead,*newTail;
                 generateNewGraph(&ptr1->head,&ptr1->tail,&newHead,&newTail);                                  
                tempNode->next=newHead;
                NODE* newNode;
    	         newNode=getnode();
                 newNode->nodeNo=++nodeNumber;
    	         strcpy(newNode->content,textForNewNode);
    	         strcpy(newNode->type,"sequential");
                 newTail->next=newNode;      
                 newNode->next=save;
                 newNode->link=tempNode->link;
                 tempNode->link=NULL;
                 insertEdge(&ptr2->head,tempNode->nodeNo,newHead->nodeNo);
                 insertEdge(&ptr2->head,newTail->nodeNo,newNode->nodeNo);
                 *targetNode=newNode;
      }
}



void insertFunctions( struct Functions ** start )
{

    struct Functions *temp;
    temp=*start;    
    while(temp!=NULL)
    { 
        struct Functions *temp2;
        temp2=*start;
        while(temp2!=temp)
        {   
              NODE *tempNode;
              tempNode=temp->head;
              while(tempNode!=temp->tail)
               { 
                         searchFunction(temp2->functionName,temp2,tempNode->content,temp,&tempNode);
                         tempNode=tempNode->next;
               }
               temp2=temp2->next;
        }
        temp=temp->next;
    }
}
