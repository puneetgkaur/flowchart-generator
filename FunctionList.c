/*----FunctionList.c----*/
struct Functions
{
	char functionName[10000];
        char functionParameterList[10000];
        int count;//number of time the function is used till now in other functions
	struct Functions *next;
        NODE *head;
      	NODE *tail;
};
void extractNameAndParameter(char input[],char output1[],char output2[])
{
    int i=0,k=0,l=0;
    /*while(input[i++]!='(');
    while(input[i]!=' ')i--;
     	i--;
    while(input[i]!='\n')i--;*/
   while(input[i++]!='(');
    while(input[i]!=' ')i--;
     	i++;
   
   while(input[i]!='('){output1[k++]=input[i];i++;}
   output1[k]='\0';
   int bracketCount=0;
   while(1)
   {
      if(input[i]=='(')bracketCount++;
      if(input[i]==')')bracketCount--;
      output2[l++]=input[i++];
      if(bracketCount==0)break;
      
   }
//   while(input[i]!='\0')
 //  {output2[l++]=input[i];i++;}
   output2[l]='\0';
   printf("%s",input);
   printf("SEE  ---%s--- :::%s::::",output1,output2);
}

void addFunction( struct Functions **startaddr,char str[],NODE ** head,NODE ** tail )
{
  struct Functions *new,*temp1;temp1=*startaddr;
  NODE *temp2;temp2=*head;
  NODE *temp3;temp3=*tail;
  char functionName[100];char functionParameterList[100];printf("str : %s",str);
  extractNameAndParameter(str,functionName,functionParameterList);
  if(temp1==NULL)
  {
        new=(struct Functions *)malloc(sizeof(struct Functions));
	strcpy(new->functionName,functionName);
	strcpy(new->functionParameterList,functionParameterList);
        new->count=0;
	new->head=temp2;
	new->tail=temp3;
	new->next=NULL;
	*startaddr=new;
  }
  else
  {
        while(temp1->next!=NULL)
        temp1=temp1->next;
        new=(struct Functions *)malloc(sizeof(struct Functions));
	strcpy(new->functionName,functionName);
	strcpy(new->functionParameterList,functionParameterList);
	new->count=0;
	new->head=temp2;
	new->tail=temp3;
	new->next=NULL;
	temp1->next=new;
  }
}
void traverseFunctions(struct Functions **start)
{
   struct Functions *temp;
   temp=*start;
   while(temp!=NULL)
   {
       printf("Function Header : %s\nFunction Parameter List ; %s\n",temp->functionName,temp->functionParameterList);
       printAdjacencyMatrix( &temp->head );
       temp=temp->next;
   }
}
