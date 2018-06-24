#include<stdio.h>
#include<string.h>
/*char* upperCase(char *word,int i,int j){
	char *returnword;
	for(i;i<=j;i++)
		returnword[i]=word[i]-32;
	return returnword;
}
*/
int fileLineLength(char *line){
	int i=0;
	while(line[i]!=0)
		i++;
	return i;
}
int main(int argc, char** argv){
	char *word=NULL, *inputfilename=NULL, *outputfilename=NULL;
	char fileline[1000];
	word=(char*)argv[1];
	int word_length = strlen(word);
	inputfilename=argv[2];
	outputfilename=argv[3];
	FILE *finput = fopen(inputfilename,"r");
	FILE *foutput = fopen(outputfilename,"w");
	fgets(fileline,1000,finput);
	int filepointer=0,wordpointer=0;
	int startindex=0,endindex=0;
	int filelinelength = fileLineLength(fileline);
	while(!feof(finput)){
		while(!(fileline[filepointer]==word[wordpointer] || fileline[filepointer]==(word[wordpointer]-32) ) && fileline[filepointer]!='\n')
			filepointer++;
		
		if(filepointer==filelinelength-1){
			fprintf(foutput,"%s",fileline);
			fgets(fileline,1000,finput);
			filelinelength = fileLineLength(fileline);
			//printf("%d\n",filelinelength);
			filepointer=0;
			wordpointer=0;
			continue;
		}
		if(fileline[filepointer]==word[wordpointer] || fileline[filepointer]==(word[wordpointer]-32)){
			startindex=filepointer;
			filepointer++;
			wordpointer++;
			while(fileline[filepointer]==word[wordpointer]){
				filepointer++;
				wordpointer++;
			
				if(wordpointer==word_length){
					int i;
					endindex=startindex+word_length;
					if(fileline[startindex]>='A' && fileline[startindex]<='Z')
						i=startindex+1;
					else
						i=startindex;
					for(i;i<endindex;i++)
						fileline[i]-=32;
				}	
			}
			
		wordpointer=0;
		}
	}
	return 0;
}
