#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
//fscan,scanf,strtoc,strsep, delimiter is spaces
//free all memory

#include "snapshot.h"
//global linked list pointers to head
value* value_head;

entry* entry_head;

snapshot* snapshot_head;

char key[MAX_KEY_LENGTH];
char com[MAX_LINE_LENGTH]; //store initial command/input
char *comCheck[MAX_LINE_LENGTH]; //stores current command/input
int i = 0;
int entries[MAX_LINE_LENGTH];

/*initialising our the linkedList's new node*/
//will implement functionality of passing it the
//value linked list
entry entry_init(value* value_head){
	entry* newEntry = (entry*)malloc(sizeof(struct entry));
	newEntry->next = entry_head;
	newEntry->prev = NULL;
	newEntry->values = NULL;
	strcpy(newEntry->key,comCheck[1]);
	return *newEntry;
}

int commandMap(char **comCheck){
	if (strcasecmp(*comCheck, HELP)==0){
		command_help();
		userInput(com);
	}

	if (strcasecmp(*comCheck, SET	)==0){
		//segmentation leak
		entry newEntry = entry_init(value_head);
		printf("key is %s", newEntry.key);
		printf("ok\n");
		userInput(com);
	}

	if (strcasecmp(*comCheck, SNAPSHOT)==0){
		printf("SNAPSHOT called\n");
		userInput(com);
	}

	if (strcasecmp(*comCheck, BYE) == 0){
		printf("bye\n");
		//need to clear and close DB here
		exit(0);
	}
	printf("no such command\n");
	printf(">");
	return 0;
}

void set(entry *entry_head, value *value_head){
	// value *value = calloc(1, sizeof(value));
	// valueList->value =
}

int command_help(){
	printf("%s", MANPAGE);
	userInput(com);
	return 0;
}


int userInput(char com[]){
	printf(">");
	while(1){
		fgets(com, MAX_LINE_LENGTH, stdin);
		char *tokPtr = strtok(com, " ");
		while (tokPtr != NULL){
			comCheck[i] = tokPtr;
			tokPtr = strtok(NULL, " ");
			i++;
		}
		free(tokPtr);
		commandMap(comCheck);
	}
	return 0;
}

int main(void) {
	userInput(com);
	return 0;
}
