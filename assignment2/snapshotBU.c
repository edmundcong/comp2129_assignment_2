#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
//fscan,scanf,strtoc,strsep, delimiter is spaces
//free all memory

#include "snapshot.h"

entry* entry_head = NULL;
entry* entry_tail = NULL;

snapshot* snapshot_head = NULL;
snapshot* snapshot_tail = NULL;

char com[MAX_LINE_LENGTH];

char *comCheck[MAX_LINE_LENGTH];
int i = 0;

char key[MAX_KEY_LENGTH];
int entries[MAX_LINE_LENGTH];

int commandMap(char comCheck[]){
	// printf("-->%s\n", comCheck[0]);
	if (strcasecmp(&comCheck[0], HELP)==0){
		command_help();
	}
	return 0;
}

int command_help(){
	printf("%s", MANPAGE);
	fgets(com, MAX_LINE_LENGTH, stdin);
	if (strcasecmp(com, BYE) == 0){
		printf("bye\n");
		return 0;
	}
	userInput(com);
	return 0;
}

int userInput(char com[]){
	//read stdin and assign to com array
	fgets(com, MAX_LINE_LENGTH, stdin);
	char * tokPtr = strtok (com, " ");
	while (tokPtr != NULL){
		printf("%s\n", tokPtr);
		comCheck[i] = tokPtr;
		tokPtr = strtok (NULL, " ");
		i++;
	}
	printf("-->%s\n", comCheck[0]);
	commandMap(comCheck[0]);


	return 0;
}

int main(void) {
	userInput(com);

	return 0;
}
