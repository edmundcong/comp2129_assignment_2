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

char com[MAX_LINE_LENGTH]; //store initial input
char *comCheck[MAX_LINE_LENGTH];
int i = 0;

char key[MAX_KEY_LENGTH];
int entries[MAX_LINE_LENGTH];

int commandMap(char **comCheck){
	printf("strcasecmp returns %d\n", strcasecmp(*comCheck, SET));
	if (strcasecmp(*comCheck, HELP)==0){
		command_help();
	}
	if (strcasecmp(*comCheck, SET)==0){
		printf("SET called\n");
	}
	if (strcasecmp(*comCheck, BYE) == 0){
		printf("bye\n");
		return 0;
	}
	userInput(comCheck);
	return 0;
}

int command_help(){
	printf("%s", MANPAGE);
	fgets(com, MAX_LINE_LENGTH, stdin);
	commandMap(comCheck);
	return 0;
}
//only works if command has a space
//theres a new line character somehwere mucking it all up
int userInput(char **comCheck){
	while(1){
		printf("%s<comCheck\n", *comCheck);
		fgets(*comCheck, MAX_LINE_LENGTH, stdin);
		char *tokPtr = strtok(*comCheck, " ");
		while (tokPtr != NULL){
			comCheck[i] = tokPtr;
			printf("tokptr is: %s\n", tokPtr);
			// printf("comCheck[%d]: %s\n", i, comCheck[i]);
			tokPtr = strtok(NULL, " ");
			printf("size: %lu\n",sizeof(tokPtr));
			i++;
		}
		commandMap(comCheck);
	}
	return 0;
}

int main(void) {
	userInput(comCheck);
	return 0;
}
