#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


#include "snapshot.h"

entry* entry_head = NULL;
entry* entry_tail = NULL;

snapshot* snapshot_head = NULL;
snapshot* snapshot_tail = NULL;

char arg1[6];

int command_help(){
	int c;
	FILE *helpFile;
	helpFile = fopen("HELP.txt", "r");
	if (helpFile) { //evaluates to true since not 0/NULL
		while ((c = getc(helpFile)) != EOF) //but will close once EOF
		putchar(c);
		fclose(helpFile);
	}
	scanf("%s", arg1);
	if (strcasecmp(arg1, "QUIT") == 0){
		userInput(arg1);
	}
	return 0;
}



int userInput(char arg1[]){
	if (strcasecmp(arg1, "HELP") == 0){
		command_help();
	}
	return 0;
}

int main(void) {

	scanf("%s", arg1);

	userInput(arg1);

	return 0;
}
