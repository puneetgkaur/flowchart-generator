/*-----graph.c-----*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int nodeNumber=0;//global variable
int countFile=0;//global Variable
struct node
{
  int nodeNo;
  char content[1000];
  char type[15];//Sequential,processing,condition,data,incremental,initialization,processing
  struct node *next;
  struct edge *link;
};

typedef struct node NODE;

struct edge
{
  int nodeNo;
  struct edge *next;
};
typedef struct edge EDGE;



NODE* getnode()
{
  NODE *new_node=(NODE*)malloc(sizeof(NODE));
  if(new_node==0)
  {
   printf("Memory not allocated\n");
   exit(0);
  }

  return new_node;
}

EDGE* getedge()
{
 
  EDGE *new_edge=(EDGE*)malloc(sizeof(EDGE));
  if(new_edge==0)
  {
   printf("Memory not allocated\n");
   exit(0);
  }

  return new_edge;
}

NODE* findNode(NODE **graph,int item)
{
  
  NODE *temp;

  temp=*graph;
 
  while( temp!=0 && temp->nodeNo!=item)
  {
    temp=temp->next;
  }
  if(item==temp->nodeNo)
  {
    //printf("%d Found!",item);
    return temp;
  }
  return 0;
}

int isNodeAvailable(NODE **graph,int item)
{
  NODE *temp;
  temp=*graph;
  if(temp==NULL){return 0;}
  else
  {
    
    while( temp!=NULL && temp->nodeNo!=item)
    {
      temp=temp->next;
      
    }
    if(temp->nodeNo==item)
    {return 1;}
    else {return 0;}
  }
  
} 
 
EDGE* findEdge(NODE **graph,int item1,int item2)
{
  NODE *temp;
  temp=*graph;
  temp=temp->next;
  if(isNodeAvailable(graph,item1) && isNodeAvailable(graph,item2))
  {
        NODE *node1;
        EDGE *tempEdge;
        node1=findNode(graph,item1);
        tempEdge=node1->link;
        while(tempEdge!=0 && tempEdge->nodeNo!=item2)
        {
              tempEdge=tempEdge->next;
        }
        if(tempEdge->nodeNo==item2)
        {
              //printf("The edge from %d to %d found\n",item1,item2);
              return tempEdge;
        }  
  }
  return 0;
}
  

int isEdgeAvailable(NODE **graph,int item1,int item2)
{
  NODE *temp;temp=*graph;
  if(graph==0)
  return 0;

        NODE *node1;
        EDGE *tempEdge;
        node1=findNode(graph,item1);
        tempEdge=node1->link;
        while(tempEdge)
        {
              if(tempEdge->nodeNo==item2)
              return 1;
              tempEdge=tempEdge->next;
        }
        

  return 0;
}

void display(NODE** node);
NODE* insertNode(NODE **graph,int item)
{
   NODE *temp,*new;
   temp=*graph;
   

   if(temp==NULL)               //first no
   {        new=getnode();
           new->nodeNo=item;
            new->next=NULL;
           *graph=new;
                 
   }
   else
   {
          
           while(((temp->next)!=0)&&(temp->nodeNo!=item))
           {
           temp=temp->next;
           }
               
                    

           if(temp->nodeNo!=item)
           {
                  new=getnode();
                  new->nodeNo=item;     
                  temp->next=new;
                  new->next=NULL;
           }
           else 
           printf("%d node already exists..\n",item);
   }
   return new;

}

void insertEdge(NODE** graph,int item1,int item2)
{
    
    NODE* temp1=0;
    EDGE* temp2=0;
     
    if(*graph==NULL)
    { 
    return;
    }
    if(isNodeAvailable(graph,item1)&&isNodeAvailable(graph,item2))
    {
                 temp1=findNode(graph,item1);
                 if(isEdgeAvailable(graph,item1,item2))
                 {
                           printf("Edge is already present\n");
                           return;
                 }
             temp2=getedge();
             temp2->next=temp1->link;
             temp2->nodeNo=item2;
             temp1->link=temp2;
    }
    else
    {
         printf("Edge cannot be inserted\n");
    }
}

int countNodes(NODE **graph)
{
   int count=1;
   NODE *temp;
   temp=*graph;
   temp=temp->next;
   while(temp!=0)
   {
           temp=temp->next;
           count++;
   } 
   return count;
}

int countEdges(NODE ** graph)
{
   int count=0;
   EDGE* edge;
   NODE *temp;
   temp=*graph;
   temp=temp->next;
   while(temp!=0)
   {
          edge=temp->link;
          while(edge!=0)
          {
                edge=edge->next;
                count++;
          } 
          temp=temp->next;
   }
   return count;
}

void display(NODE** node)
{
 NODE *tempNode;
 tempNode=*node;
 printf("nodeNumber : %d\n",tempNode->nodeNo);
 printf("node type: %s\n",tempNode->type);
 printf("node content : %s\n",tempNode->content);
 printf("\n\n\n");
}


void printAdjacencyMatrix(/*int **adj,*/NODE** graph/*,int maxNodes*/)
{
    
     NODE *temp;
     EDGE *edge;
 /*    int **adj;
    adj=(int**)malloc(maxNodes*sizeof(int*));
    for(i=1;i<=maxNodes;i++)adj[i]=(int*)malloc(maxNodes*sizeof(int)); 
    for(i=1;i<=maxNodes;i++)for(j=1;j<=maxNodes;j++){adj[i][j]=0;}       
*/
     temp=*graph;
     while(temp)
     {   
            edge=temp->link;
            while(edge)
            {
                       // adj[temp->nodeNo][edge->nodeNo]=1;
                       printf("edge from %d to %d\n",temp->nodeNo,edge->nodeNo);
                       edge=edge->next;                   
            }
            temp=temp->next;      
     }
/*
     printf("This is the adjacency matrix...\n");   
     printf("   "); 
     for(j=1;j<=maxNodes;j++)
     {
       if((j/10)<1)
       printf("  %d  ",j);
       else 
       printf("  %d ",j);
     }
     printf("\n\n");
     for(i=1;i<=maxNodes;i++)
     {
             if((i/10)<1)
             printf("%d  ",i);
             else 
             printf("%d ",i);      
             for(j=1;j<=maxNodes;j++)
             printf("  %d  ",adj[i][j]);
             printf("\n\n");
     }
*/     
}


