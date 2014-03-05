/*----------modifyCode.c-----------*/
#include <stdio.h>
void main()//remove comments add checkmarks
{
          char ch;
          FILE *fp,*fp2,*fp3;
          fp=fopen("test.c","r");
          fp2=fopen("Modified.c","w+");
          fp3=fopen("Modified1.c","w+");
   	  while((ch=fgetc(fp))!=EOF)
	  {
			     if(ch=='/')
			     {
							ch=fgetc(fp);
							if((ch=='*')||(ch=='/'))
							{
										    if(ch=='*')
										    {
													  while(1)
													  {
                                                                                                                        ch=fgetc(fp);
                           											 	if(ch=='*')
															{
																ch=fgetc(fp);
																if(ch=='/')
																break;
																fseek(fp,-1,SEEK_CUR);
															}	
													  }
										    }
										    if(ch=='/')
										    {
													  while(ch!='\n')
													  ch=fgetc(fp);
										    }
							}
							else
							{
										    fseek(fp,-1,SEEK_CUR);
										    ch='/';
							}          
			     }
                             fputc(ch,fp2);
                             
	  }
         rewind(fp2);
         int num=0;
          while((ch=fgetc(fp2))!=EOF)
          {
              if(ch=='{')
               {
                  fputc(ch,fp3);fprintf(fp3,"\nfprintf(fpPathFile,\"%d-\");",++num );continue;
               }
               fputc(ch,fp3);
          }
         rewind(fp2);
         rewind(fp3);
         char str[10000];
          while((ch=fgetc(fp3))!=EOF)
          {if(ch!='m'){fputc(ch,fp2);continue;}
        if(ch=='m')
         {
                ch=fgetc(fp3);
                if(ch=='a')
                {
                      ch=fgetc(fp3);
                      if(ch=='i')
                      {  
                                 ch=fgetc(fp3);
                                 if(ch=='n')
                                 {
                                       
                                       while(ch!='{')
                                       {
                                            ch=fgetc(fp3);
                                       }
                                       ch=fgetc(fp3);//skip the starting '{'
                                     fprintf(fp2,"main(int argc,char *argv[])\n{\nFILE *fpPathFile;\nfpPathFile=fopen(\"PathGenerated.txt\",\"w\");\n");                
                                 }else{fprintf(fp2,"mai");fputc(ch,fp2);}
                      }else{fprintf(fp2,"ma");fputc(ch,fp2);}
                }else{fputc('m',fp2);fputc(ch,fp2);}
         }
         
     }
   
         
                 
  
}
