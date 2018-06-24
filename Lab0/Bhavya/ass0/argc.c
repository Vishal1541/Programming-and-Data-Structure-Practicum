#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[])
{
   int n,size,con,i,j,k,l,index;
   char arr[100],name[100];
   bool flag;
   strcpy(name,argv[1]);
   FILE *f,*fp;
   f=fopen(argv[2],"r");
   fp=fopen(argv[3],"w");
   while(fgets(arr,100,f)!=NULL)
   {
      i=0;
      size=sizeof(arr);
      while(arr[i]!='\0')
      {
         flag=false;
         if(arr[i]==name[0])
         {
            l=1;
            index=i;
            j=i+1;
            while(name[l]!='\0')
            {
               if(arr[j]!=name[l])
               {
                 flag=true;
                 break;
               }
               l++;
               j++;
            }
            if(!flag)
            {
               j=0;
               k=index;
               while(name[j]!='\0')
               {
                  con=name[j];
                  arr[k]=con-97+65;
                  k++;
                  j++;
               }
               break;
            }
         }
         i++;
      }
   fputs(arr,fp);
   }
   fclose(f);
   return 0;
}
