#include<stdio.h>
#include<string.h>
typedef struct s{
	char* word;
	int count;
}data;
int main(int argc, char** argv){
	data input_words[100];
	int i=0,j=0;
	input_words[0].word=argv[1];
	input_words[0].count=1;
	int entry_index=1;
	while(j!=argc){
		for(j=2;j<argc;j++){
			for(i=0;i<entry_index;i++){
				if(!strcmp(argv[j],input_words[i].word)){
					input_words[i].count++;
					break;
				}
				else if(entry_index-i==1){
					input_words[entry_index].word=argv[j];
					input_words[entry_index++].count=1;
					break;
				}
			}
		}
	}
	for(i=0;i<entry_index;i++)
		printf("%-10s%15d\n",input_words[i].word,input_words[i].count);
	for(i=0;i<entry_index;i++)
		if(input_words[i].count>10)
			printf("The word \"%s\" exceeds the limit of 10.\n",input_words[i].word);
	return 0;
}
