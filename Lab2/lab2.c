#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct s{
	char district[20];
	float rain[12];
}raindata;
char *month[12] = {"JAN","FEB","MAR","ARP","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
void makeHistogram(raindata *d, int totalrows){
	int histogram[7]={0,0,0,0,0,0,0};
	int row,col;
	for(row=0;row<totalrows;row++)
		for(col=0;col<12;col++){
			if(d[row].rain[col]<100)
				histogram[0]++;
			else if(d[row].rain[col]<200)
				histogram[1]++;
			else if(d[row].rain[col]<300)
				histogram[2]++;
			else if(d[row].rain[col]<400)
				histogram[3]++;
			else if(d[row].rain[col]<500)
				histogram[4]++;
			else if(d[row].rain[col]<600)
				histogram[5]++;
			else if(d[row].rain[col]<700)
				histogram[6]++;
		}
	printf("\tClass-Interval(mm)\t\t|\tNumber of Rainfall Values (Count)\n\n");
	printf("\t\t00-100\t\t\t|\t\t\t%d\n",histogram[0]);
	printf("\t\t100-200\t\t\t|\t\t\t%d\n",histogram[1]);
	printf("\t\t200-300\t\t\t|\t\t\t%d\n",histogram[2]);
	printf("\t\t300-400\t\t\t|\t\t\t%d\n",histogram[3]);
	printf("\t\t400-500\t\t\t|\t\t\t%d\n",histogram[4]);
	printf("\t\t500-600\t\t\t|\t\t\t%d\n",histogram[5]);
	printf("\t\t600-700\t\t\t|\t\t\t%d\n",histogram[6]);
}
void upper(char *s){
   int c = 0;
   while (s[c] != 0) {
      if (s[c] >= 'a' && s[c] <= 'z')
         s[c] -= 32;
      c++;
   }
}
int districtToIndex(char *s, raindata *d, int total){
	int i=0;
	for(i;i<total;i++)
		if(!strcmp(s,d[i].district))
			return i;
}
int monthToIndex(char *s){
	int i=0;
	for(i;i<12;i++)
		if(!strcmp(s,month[i]))
			return i;
}
void districtMinMaxAvg(raindata *d, int index, float *min, float *max, float* avg, char *sMin, char *sMax){
	*min = d[index].rain[0];
	*max = d[index].rain[0];
	float sum=0;
	int i,min_index=0,max_index=0;
	for(i=0;i<12;i++){
		if(d[index].rain[i]<*min){
			*min = d[index].rain[i];
			min_index=i;
		}
		if(d[index].rain[i]>*max){
			*max = d[index].rain[i];
			max_index=i;
		}
		sum+=d[index].rain[i];
	}
	*avg=sum/12;
	strcpy(sMin,month[min_index]);
	strcpy(sMax,month[max_index]);
}
void monthMinMaxAvg(raindata *d,int index,int total, float *min, float *max, float *avg, char *sMin, char *sMax){
	*min = d[0].rain[index];
	*max = d[0].rain[index];
	float sum=0;
	int i,min_index=0,max_index=0;
	for(i=0;i<total;i++){
		if(d[i].rain[index]<*min){
			*min = d[i].rain[index];
			min_index=i;
		}
		if(d[i].rain[index]>*max){
			*max = d[i].rain[index];
			max_index=i;
		}
		sum+=d[i].rain[index];
	}
	*avg=sum/12;
	strcpy(sMin,d[min_index].district);
	strcpy(sMax,d[max_index].district);
}
int main(){
	raindata Data[20];
	FILE *fgetdata = fopen("Rainfall.txt","r");
	char line[1000];
	char *record;
	int totalno=0,i;
	fgets(line,1000,fgetdata);
	while(fgets(line,1000,fgetdata)){
		record=strtok(line,"\t");
		strcpy(Data[totalno].district,record);
		//printf("%s ",Data[totalno].district);
		for(i=0;i<12;i++){
			record=strtok(NULL,"\t");
			Data[totalno].rain[i]=atof(record);
		//	printf("%.1f ",Data[totalno].rain[i]);
		}
		//printf("\n");
		totalno++;		
	}
	char input[20];
	int serialNo;
	printf("Enter the serial no of the operation to be performed:\n");
	printf("1.\tFind min/max rainfall that occured in a paticular district.\n");
	printf("2.\tFind average of the rainfall that occured in a paticular district.\n");
	printf("3.\tFind min/max rainfall that occured in a paticular month.\n");
	printf("4.\tFind average of the rainfall that occured in a paticular month.\n");
	printf("5.\tMake a histogram using data.\n");
	scanf("%d",&serialNo);
	if(serialNo==5){
		makeHistogram(Data,totalno);
		return 0;
	}switch(serialNo){
		case 1:
		case 2: printf("Enter the District name:\n");break;
		case 3:
		case 4: printf("Enter the Month name:\n");break;
	}
	scanf("%s",input);
	upper(input);
	//printf("%s",input);
	float min,max,avg;
	int index;
	char sMin[20], sMax[20];
	if(serialNo==1 || serialNo==2){
		index=districtToIndex(input,Data,totalno);
		districtMinMaxAvg(Data,index,&min,&max,&avg,sMin,sMax);
		switch(serialNo){
			case 1:	printf("The Min and Max rainfall occured in %s is %.2fmm and %.2fmm in the month of %s and %s respectively.\n",input,min,max,sMin,sMax); break;
			default: printf("The Average rainfall occured in %s across the year is %.2fmm.\n",input,avg); break;
		}
	}
	else if(serialNo==3 || serialNo==4){
		index=monthToIndex(input);
		monthMinMaxAvg(Data,index,totalno,&min,&max,&avg,sMin,sMax);
		switch(serialNo){
			case 3:	printf("The Min and Max rainfall occured in the month of %s is %.2fmm and %.2fmm in the district %s and %s respectively.\n",input,min,max,sMin,sMax); break;
			default: printf("The Average rainfall occured in the month of %s across all districts is %.2fmm.\n",input,avg); break;
		}
	}
	return 0;
}
