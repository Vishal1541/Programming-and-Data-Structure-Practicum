#include<glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>
int main(int argc, char** argv){
	char* word = NULL;
	word = (char*)(argv[1]);
	g_printf("%s\n",word);
	char* inputfile = NULL;
	inputfile = (char*) g_string_new(argv[2]);
	FILE *finput = g_fopen(inputfile,"r");
	char* outputfile = NULL;
	outputfile = (char*) g_string_new(argv[3]);
	FILE *foutput = g_fopen(outputfile,"w");
	//g_string_ascii_up(word);
	return 0;
}
