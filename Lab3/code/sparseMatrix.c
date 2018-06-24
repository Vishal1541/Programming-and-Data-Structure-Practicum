#include <stdio.h>
#include <stdlib.h>
#define MAX_COL 100
#define MAX_TERMS 500
#include "SM.h"

void print(SMatrix *S1) //printing the matrix
{
int i;

for (i=0;i<=S1[0].value;i++)
{

    printf("S1[%d],\t%d \t%d \t %f\n",i,S1[i].row,S1[i].col,S1[i].value);
}
}


void sort(SMatrix* S1)
{ int i,c,d;
int size=S1[0].value;
SMatrix S3[size],t;

for(i=1;i<=size;i++)
    {
        S3[i-1].col=S1[i].col;
        S3[i-1].row=S1[i].row;
        S3[i-1].value=S1[i].value;
    }
//Insertion Sort
 for (c = 1 ; c <= size-1; c++) {
    d = c;

    while ( d > 0 && (S3[d].row*10+S3[d].col) < (S3[d-1].row*10+S3[d-1].col)) {
      t          = S3[d];
      S3[d]   = S3[d-1];
      S3[d-1] = t;

      d--;
    }
  }
}


//Matrix creation
SMatrix* Create(int MaxRow,int MaxCol,int MaxVal)
{
SMatrix *SM;
int i;
int MaxElem;
MaxElem=MaxCol*MaxRow;
if(MaxVal<=MaxElem)
{
SM=(SMatrix*)malloc(sizeof(SMatrix)*(MAX_TERMS));
SM[0].row=MaxRow;
SM[0].col=MaxCol;
SM[0].value=MaxVal;
return SM;
}
else{
    printf("Index out of range");
    exit(1);
}

for(i=1;i<=SM[0].value;i++)
    SM[0].value=0;
}


void deleteSM(SMatrix *S1,int r_index,int c_index)
{ int i;
	for (i=1;i<=S1[0].value;i++)
	{
		if(S1[i].row==r_index && S1[i].col==c_index)
		{   
			S1[i].value=0;
			//S1[i].row=-1;	
			//S1[i].col=-1;
			printf("Entry deleted,kindly enter a new element");
		}	
	}
}



//Inserting in a matrix
void insertSM(SMatrix *S1,int r_index,int c_index,float value)
{
int i,count=0;
for (i=1;i<=S1[0].value;i++){
    if(S1[i].value==0 && count<1 )
    {
        count++;
    if(r_index<S1[0].row && c_index<S1[0].col){
        S1[i].row=r_index;
        S1[i].col=c_index;
        S1[i].value=value;
    }
    else{
        printf("Invalid row or column number");
        exit(1);}

}
else if (S1[i].value!=0 && S1[i].row==r_index && S1[i].col==c_index){
	S1[i].value=value;
}
}
sort(S1);
}


SMatrix* transpose (SMatrix *a)
    {
        SMatrix *b;
        b=(SMatrix*)malloc(sizeof(SMatrix)*(a[0].value+1));
        int rowTerms[MAX_COL],startingPos[MAX_COL];
        int i,j,numCols=a[0].col,numTerms=a[0].value;
        b[0].row=numCols;
        b[0].col=a[0].row;
        b[0].value=numTerms;
        if(numTerms>0)
        {
            for(i=0;i<numCols;i++)
                rowTerms[i]=0;
            for(i=1;i<=numTerms;i++)
                rowTerms[a[i].col]++;
            startingPos[0]=1;
            for(i=1;i<numCols;i++)
                startingPos[i]=startingPos[i-1]+rowTerms[i-1];
            for(i=1;i<=numTerms;i++)
            {
                j=startingPos[a[i].col]++;
                b[j].row=a[i].col;
                b[j].col=a[i].row;
                b[j].value=a[i].value;
            }
        }



     return b;
    }

float getvalue(SMatrix *Sm,int row,int col)
{
  float value=0;
    int i,j;
    int limit=(int)Sm[0].value;

    for(i=1;i<=limit;i++)
    {
        if(Sm[i].row==row && Sm[i].col==col){
            value=Sm[i].value;
        }

}
if(value!=0)
    return value;
else return 0;
}

