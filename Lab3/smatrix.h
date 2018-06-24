#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct s{
	int row;
	float value;
}SMatrix;
void SMInsert(SMatrix* s,FILE* f){
	int r=0,index=0;
	float b;
	while(!feof(f)){
		fscanf(f,"%f",&b);
		if(b!=0){
			s[index].row=r;
			s[index].value=b;
			index++;
		}
		r++;
	}
}
void SMAddition(FILE* f1, FILE* f2, SMatrix add[]){
    int i=0,r=0;
    float value1,value2;
    while(!feof(f1)){
            fscanf(f1,"%f",&value1);
            fscanf(f2,"%f",&value2);
            if((value1+value2)!=0){
                add[i].row=r;
                add[i].value=value1+value2;
                //printf("\t%d\t%f\n",add[i].row,add[i].value);
                i++;
            }
            //else
            	
                //printf("\t%d\t%f\n",r,0.0);
            r++;
    }
}
void SMPrint(SMatrix *m){
    int r,i=0;
    printf("\tRow\t|\tValue\n\n");
    for(r=0;r<100;r++){
        if(m[i].row==r){
            printf("\t%d\t|\t%f\n",r+1,m[i].value);
            i++;
        }
        else
            printf("\t%d\t|\t%f\n",r+1,0.0);
    }
}
int SMCompare(SMatrix *data, SMatrix *ref){
	return (data[0].row>=ref[0].row-3 && data[0].row<=ref[0].row+3);
}
void fileLocationChange(char a[]){
	a[15]++;
}
void fileNameIncrement(char a[]){
	a[1]++;
}
