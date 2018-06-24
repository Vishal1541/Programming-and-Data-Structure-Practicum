#include<stdio.h>
#include<stdlib.h>

void arrayInput(int arr[], int size, FILE *f){
	int i;
	for(i=0;i<size;i++){
		fscanf(f,"%d\n",&arr[i]);
		}
}
int mergeArray(int arr1[], int s1, int arr2[], int s2,int arr3[]){
	//int arr3[s1+s2];
	int p1=0,p2=0,i=0,j;
	while(!(p1==s1 || p2==s2)){
		if(arr1[p1]<arr2[p2])
			arr3[i++]=arr1[p1++];
		else if(arr1[p1]>arr2[p2])
			arr3[i++]=arr2[p2++];
		else{
			arr3[i++]=arr2[p2++];
			p1++;
		}
	}
	if(p1==s1)
		for(j=p2;j<s2;j++)
			arr3[i++]=arr2[j];
	else if(p2==s2)
		for(j=p1;j<s1;j++)
			arr3[i++]=arr1[j];
	return i;							//size
}
int main(int argc, char** argv){
	FILE *f1 = fopen(argv[1],"r");
	FILE *f2 = fopen(argv[2],"r");
	int size1=0, size2=0;
	char *temp=malloc(100);
	while(fgets(temp,100,f1))
		size1++;
	while(fgets(temp,100,f2))
		size2++;
	fclose(f1);
	fclose(f2);
	FILE *finput1 = fopen(argv[1],"r");
	FILE *finput2 = fopen(argv[2],"r");
	int arr1[size1],arr2[size2],arr3[size1+size2];
	arrayInput(arr1,size1,finput1);
	arrayInput(arr2,size2,finput2);
	int size3 = mergeArray(arr1,size1,arr2,size2,arr3);
	int i;
	for(i=0;i<size3;i++)
		printf("%d\n",arr3[i]);
	return 0;
}
