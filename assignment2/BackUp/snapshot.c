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

int commandMap(char **comCheck){
	if (strcasecmp(*comCheck, HELP)==0){
		command_help();
	}
	if (strcasecmp(*comCheck, SET)==0){
		printf("SET called\n");
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
//only works if command has a space
//theres a new line character somehwere mucking it all up
int userInput(char com[]){
	fgets(com, MAX_LINE_LENGTH, stdin);
	char *tokPtr = com;
	tokPtr = strtok(com, " ");
	while (tokPtr != NULL){
		printf("%s\n", tokPtr);
		comCheck[i] = tokPtr;
		tokPtr = strtok (NULL, " ");
		i++;
	}
	commandMap(comCheck);
	return 0;
}

int main(void) {
	userInput(com);
	return 0;
}
