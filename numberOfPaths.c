/*--------numberOfPaths.c---------*/
void multiply(int** A,int ** B,int **C,int row1,int column1,int column2)
{
 int i,j,k,p;

 for(i=1;i<=row1;i++)
 {
  for(j=1;j<=column2;j++)
  {
    C[i][j]=0;
    for(k=1;k<=column1;k++)
    C[i][j]=C[i][j]+A[i][k]*B[k][j];
  }
 }
}  

int findPaths(int **adj,int start,int end,int max )
{
  int paths=0,i,j;
  int **adj1;
  adj1=(int**)malloc(max*sizeof(int*));
  for(i=1;i<=max;i++)adj1[i]=(int*)malloc(max*sizeof(int)); 
  int **temp;
  temp=(int**)malloc(max*sizeof(int*));
  for(i=1;i<=max;i++)temp[i]=(int*)malloc(max*sizeof(int)); 
      
  adj1=adj;
  for(i=1;i<=max;i++)
  {
     multiply(adj,adj1,temp,max,max,max);
     adj1=temp;   
     paths+=temp[start][end];
  }
  printf("\n%d\n",paths);
  return paths;
}


int numberOfPaths(struct Functions ** start)
{
  struct Functions *temp;
   temp=*start;
   char name[1000];
   strcpy(name,temp->functionName);
   while( detectSubString("main",name)==0 )
   {
        temp=temp->next;
        strcpy(name,temp->functionName);
   }
   
   NODE *tempNode;
   tempNode=temp->head;
   int max,min;max=-1;min=10000;
   while( tempNode!=NULL )
   {
        int k=tempNode->nodeNo;
        if(max<k)max=k;
        if(min>k)min=k;
        tempNode=tempNode->next;
   }
   int difference=max-min;
   int i,j;
   int **adj;
   adj=(int**)malloc(max*sizeof(int*));
   for(i=1;i<=max;i++)adj[i]=(int*)malloc(max*sizeof(int)); 
   for(i=1;i<=max;i++)for(j=1;j<=max;j++){adj[i][j]=0;}       
  
     tempNode=temp->head;
     while(tempNode!=NULL)
     {   
                EDGE *edge;
            edge=tempNode->link;
            while(edge!=NULL)
            {
                        int i=tempNode->nodeNo;int j=edge->nodeNo;
                        adj[i][j]=1;
                       //printf("edge from %d to %d\n",temp->nodeNo,edge->nodeNo);
                       edge=edge->next;                   
            }
            tempNode=tempNode->next;      
     }
  
     for(i=min;i<max;i++)
     {
     for(j=min;j<max;j++)
     {          
         printf("%d ",adj[i][j]);
     }
      printf("\n");
     }
     tempNode=temp->head;
     int startNodeNo=tempNode->nodeNo;
     while(tempNode->next!=NULL)tempNode=tempNode->next;
     int endNodeNo=tempNode->nodeNo;
     int paths=findPaths(adj,startNodeNo,endNodeNo,max);
     return paths;
}
