/*---------generateRandomTestCase.c---------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>

int randomInt()
{
int randomNumber;
int LOW;
LOW=-32,768;
int HIGH;
HIGH=+32,767;
sleep(1);
time_t seconds;
time(&seconds);
srand((unsigned int) seconds);
randomNumber = rand() % (HIGH - LOW + 1) + LOW;
return randomNumber;
}

char randomChar()
{
int LOW;
LOW=97;
int HIGH;
HIGH=122;
int randomNumber;
time_t seconds;
sleep(1);
time(&seconds);
srand((unsigned int) seconds);
randomNumber = rand() % (HIGH - LOW + 1) + LOW;
return (char)randomNumber;
}

float randomFloat()
{
float first;
float second;
int LOW;
int HIGH;
LOW=-32768;
HIGH=+32767;
time_t seconds;
sleep(1);
srand((float) seconds);
first = (float)(rand() % (HIGH - LOW + 1) + LOW);
second=(float)(rand() % (HIGH - LOW + 1) + LOW);
first=first+(second/100000);
return first;
}

unsigned int randomUnsignedInt()
{
unsigned int randomNumber;
unsigned int LOW;
LOW=0;
unsigned int HIGH;
HIGH=+65535;
time_t seconds;
sleep(1);
time(&seconds);
srand((unsigned int) seconds);
randomNumber = rand() % (HIGH - LOW + 1) + LOW;
printf("%u",randomNumber);
return randomNumber;
}
void  generateRandomTestCase (char str[],int numInt,int numFloat,int numChar,int numString,int limitForString[])
{
 
 int i,j,k,m=0,flag;
 //declaration 1 : length of arrays for storing test cases
 char ch;

 FILE *fp;
 str[m]='\0';
 fp=fopen("TempRandomFile","w");

 for(i=0;i<numInt;i++)
 {
  //printf("%d ",randomInt());
  fprintf(fp,"%d ",randomInt()); 
 }

 for(i=0;i<numChar;i++)
 {
  //printf("%c ",randomChar());
  fprintf(fp,"%c ",randomChar());
 }
 for(i=0;i<numFloat;i++)
 {
  fprintf(fp,"%f ",randomFloat());
 }
 for(i=0;i<numString;i++)
 {
  for(j=0;j<limitForString[i];j++)
  {
   fprintf(fp,"%c",randomChar());
  }
  fprintf(fp,"%c",' ');
 }
/*
 for(i=0;i<numUnsignedInt;i++)
 {
  fprintf(fp,"%u ",randomUnsignedInt());
 }
*/
 fclose(fp);

  fp=fopen("TempRandomFile","r");
 // str[0]='\0';
  i=0;
  while((ch=fgetc(fp))!=EOF)  
  {
       /*if(flag==0)
       {
         initializeStr(str);
         flag=1;
       }*/
       str[i++]=ch;
  }
  str[i]='\0';
  fclose(fp);
}
/*
void main()
{
 char str1[1000];
 int arr[2]={5,6};
 generateRandomTestCase (str1,3,0,0,2,arr);
 printf("%s",str1);
}
*/
