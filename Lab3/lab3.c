#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"smatrix.h"
SMatrix ref[2][15], data1[9][15], data2[6][15], addition[30];


int main(){
	FILE *ref1=fopen("vectors/ref1/x1.txt","r");
	FILE *ref2=fopen("vectors/ref2/x2.txt","r");

	SMInsert(ref[0],ref1);
	SMInsert(ref[1],ref2);

	char fileLocD1[25] = "vectors/data1/y1.txt";
	char fileLocD2[25] = "vectors/data2/y1.txt";
	char fName[5] = "y1";
	int i,cmp;

	printf("Data1: ");
	for(i=0;i<9;i++){
		FILE *d1 = fopen(fileLocD1,"r");
		SMInsert(data1[i],d1);
		cmp = SMCompare(data1[i],ref[0]);
		if(cmp)
			printf("%s, ",fName);
        fileNameIncrement(fName);
		fileLocationChange(fileLocD1);
		fclose(d1);
	}
	printf("belong to the class of x1.\n");

	strcpy(fName,"y1");
	printf("Data2: ");
	for(i=0;i<6;i++){
		FILE *d2 = fopen(fileLocD2,"r");
		SMInsert(data2[i],d2);
		cmp = SMCompare(data2[i],ref[1]);
		if(cmp)
			printf("%s, ",fName);
        fileNameIncrement(fName);
		fileLocationChange(fileLocD2);
		fclose(d2);
	}
	printf("belong to the class of x2.\n");
	printf("Enter the location of the two Matrices to be added:\n");
    char location1[25], location2[25];
    scanf("%s%s",location1,location2);
    FILE *f1 = fopen(location1,"r");
    FILE *f2 = fopen(location2,"r");
    SMAddition(f1,f2,addition);
    SMPrint(addition);
	return 0;
}
