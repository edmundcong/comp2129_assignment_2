#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
//fscan,scanf,strtoc,strsep, delimiter is spaces
//free all memory

#include "snapshot.h"
value* value_head;
entry* entry_head; //pointer to DLL head
snapshot* snapshot_head;


int value_stored = 0; //integer value for value node
int value_index = 0;
int i = 0;
int is_entry_head = 0; //to determine whether to add to head or tail

char key[MAX_KEY_LENGTH];
char com[MAX_LINE_LENGTH]; //store initial command/input
char *comCheck[MAX_LINE_LENGTH]; //stores current command/input
int entries[MAX_LINE_LENGTH];

value value_init(int value_int){
	value* newValue = (value*)malloc(sizeof(struct value));
	newValue->next = NULL;
	newValue->prev = NULL;
	newValue->value = value_int;
	newValue->value_index = value_index;
	value_index++;
	return *newValue;
}
/*initialising our the linkedList's new node*/
//will implement functionality of passing it the
//value linked list
entry entry_init(value* value_head){
	entry* newEntry = (entry*)malloc(sizeof(struct entry));
	newEntry->next = NULL;
	newEntry->prev = NULL;
	newEntry->values = value_head;
	strcpy(newEntry->key,comCheck[1]);
	printf("1: %s created\n", newEntry->key);
	return *newEntry;
}

void entry_insertAtHead(value *value_head){
	entry newEntry = entry_init(value_head);
	printf("2: %s created - ", newEntry.key);
	if(entry_head == NULL){
		entry_head = &newEntry;
		printf("entry_head is null\n");
		is_entry_head = 1;
		return;
	}
	entry_head->prev = &newEntry;
	newEntry.next = entry_head;
	entry_head = &newEntry;
	is_entry_head = 1;
	printf("entry_head not null\n");
}


void entry_insertAtTail(value *value_head){
	entry *temp = entry_head;
	entry newEntry = entry_init(value_head);
	printf("3: %s created\n", newEntry.key);
	while(temp->next != NULL){
		printf("4: %s temp key\n", temp->key);
		temp = temp->next;
	}
	temp->next = &newEntry;
	newEntry.prev = temp;
	// printf("5: %s created\n", newEntry.key);
	// printf("6: %s prev key\n", newEntry.prev->key);

}

void value_insertAtHead(int value){
	// struct value newValue = value_init(value_stored);
}

int commandMap(char **comCheck){
	if (strcasecmp(*comCheck, HELP)==0){
		command_help();
		userInput(com);
	}

	if (strcasecmp(*comCheck, SET	)==0){
		set(entry_head, value_head);
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
	//will need to cycle through to get all values later
	value_stored = atoi(comCheck[2]); //first arg is head
	printf("set called\n");
	if (is_entry_head == 0){
		entry_insertAtHead(value_head);
	}
	else {
		entry_insertAtTail(value_head);
	}
	// value_insertAtHead(value_stored);
	// printf("key is %s\n", newEntry.key);
	printf("ok\n");
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
	//empty list to start off
	entry_head = NULL;
	value_head = NULL;
	snapshot_head = NULL;

	userInput(com);
	return 0;
}
