#include<stdio.h>
#include<stdlib.h>
int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
void insert(int* array, int len, int new, int* return_array){
	int index=0,i=0;
	while(new>array[index])
		index++;
	for(i;i<index;i++)
		return_array[i]=array[i];
	return_array[i++]=new;
	for(i;i<=len;i++)
		return_array[i]=array[i-1];
}
int main(int argc,char** argv){
	int size = atoi(argv[2]);
	int newint = atoi(argv[3]);
	FILE *finput = fopen(argv[1],"r");
	FILE *foutput = fopen(argv[4],"w");
	int numbers_input[size];
	int numbers_output[size+1];
	int i;
	for(i=0;i<size;i++)
		fscanf(finput,"%d",&numbers_input[i]);
	qsort(numbers_input,size,4, cmpfunc);
	insert(numbers_input,size,newint,numbers_output);
	for(i=0;i<=size;i++)
		fprintf(foutput,"%d\n",numbers_output[i]);
    fclose(finput);
    fclose(foutput);
	return 0;
}
