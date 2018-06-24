#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct s{
	int index;
	char fname[20], lname[20], dob[20], location[20], dept[20];
}data;
void inputData(data *d,int s, FILE *f){
	char *temp=malloc(300), *rec=malloc(20);
	int i;
	for(i=0;i<s;i++){
		fgets(temp,300,f);
		rec = strtok(temp,"\t");
		d[i].index=atoi(rec);
		rec = strtok(NULL," ");
		strcpy(d[i].fname,rec);
		rec = strtok(NULL," ");
		strcpy(d[i].lname,rec);
		rec = strtok(NULL," ");
		strcpy(d[i].dob,rec);
		rec = strtok(NULL," ");
		strcpy(d[i].location,rec);
		rec = strtok(NULL,"\n");
		strcpy(d[i].dept,rec);
	}
}
void mergeSort(data *d, int l, int u){
	int m = (l+u)/2,i;
	if(l<u){
		mergeSort(d,l,m);
		mergeSort(d,m+1,u);
		merge(d,l,m,u);
	}
}
void merge(data *d, int l, int m, int u){
	int p1 = l, p2 = m+1;
	data r[u-l+2];
	int i=0,k,x;
	while(!(p1==(m+1) || p2==(u+1) )){
		if(d[p1].index < d[p2].index)	r[i++] = d[p1++];
		else				r[i++] = d[p2++];
	}
	if(p1==m+1)
		for(k=p2;k<=u;k++)		r[i++] = d[k];
	else
		for(k=p1;k<=m;k++)		r[i++] = d[k];
	i=0;
	for(x=l;x<=u;x++)			d[x] = r[i++];
}
int main(int argc, char** argv){
	
	if(argc==1){
		printf("Usage: lab5_2 infile outfile numberOfRecords\n");
		return 0;
	}
	printf("Reading file data...\n");
	FILE *fin=fopen(argv[1],"r");
	FILE *fout=fopen(argv[2],"w");
	int size=atoi(argv[3]);
	data *records = malloc(sizeof(data)*size);
	inputData(records,size,fin);
	printf("Performing merge sort on array...\n");
	clock_t begin = clock();
	mergeSort(records,0,size-1);
	clock_t end = clock();
	int i;
	printf("Output written into file sortedData...\n");
	for(i=0;i<size;i++){
		fprintf(fout,"%d\t",records[i].index);
		fprintf(fout,"%s\t",records[i].fname);
		fprintf(fout,"%s\t",records[i].lname);
		fprintf(fout,"%s\t",records[i].dob);
		fprintf(fout,"%s\t",records[i].location);
		fprintf(fout,"%s\n",records[i].dept);
	}
	printf("Done\n");
	
	float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;
	printf("EXECUTION TIME : %f\n",time_spent);	
	return 0;
}
