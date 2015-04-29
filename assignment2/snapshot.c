#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
//fscan,scanf,strtoc,strsep, delimiter is spaces
//free all memory

//note: use str_length not sizeof(only works at compile time)

#include "snapshot.h"
value* values_temp = NULL;
value* value_head = NULL;
entry* entry_head = NULL; //pointer to DLL head
snapshot* snapshot_head = NULL;

int value_stored = 0; //integer value for value node
int value_index = 1; //index for value in LL
int value_array_index = 0; //index for values in passing array
int i = 0;
int j = 0;
int k = 0;
int is_entry_head = 0; //to determine whether to add to head or tail
int is_value_head = 0;
int value_entries_counter = 0;

int value_entries[MAX_LINE_LENGTH];
char key[MAX_KEY_LENGTH];
char com[MAX_LINE_LENGTH]; //store initial command/input
char *comCheck[MAX_LINE_LENGTH]; //stores current command/input


value* value_init(int value_stored){ //might incur a shadowing problem
	value* newValue = (value*)malloc(sizeof(struct value));
	newValue->next = NULL;
	newValue->prev = NULL;
	newValue->value = value_stored;
	newValue->value_index = value_index;
	value_index++;
	return newValue;
}
/*initialising our the linkedList's new node*/
//will implement functionality of passing it the
//value linked list
entry* entry_init(){
	entry* newEntry = (entry*)malloc(sizeof(struct entry));
	newEntry->next = NULL;
	newEntry->prev = NULL;
	newEntry->values = value_head;
	strcpy(newEntry->key,comCheck[1]);
	return newEntry;
}

void entry_insertAtHead(){
	entry* newEntry = entry_init();
	entry_head = newEntry;
	is_entry_head = 1;
	printf("newEntry is %s\n", newEntry->key);
	return;
}


void entry_insertAtTail(){
	entry* temp = entry_head;
	// value* valuesTemp = value_head;

	// do {
	// 	if(temp->next == NULL){
	// 		break;
	// 		printf("1 pls\n");
	// 	}
	// 	printf("2 pls\n");
	// 	if(strcmp(temp->key,comCheck[1]) == 0){
	// 		temp->values = value_head;
	// 		return;
	// 	} //need to check prev and next or do i?
	// 	// if (temp->next == NULL) break;
	// 	temp = temp->next;
	// } while (temp->next != NULL);


	entry* newEntry = entry_init();
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newEntry;
	newEntry->prev = temp;
	/*scan back from the end and if it finds a value with the same key, delete it.
	therefore del will need to be done before get can be complete. since we need to
	be able to delete any keys that we modify e.g. set a 1 2 then set a 5 4, we'd
	delete the first entry, then move to the back of the tail and add set a 5 4 there.*/
	printf("newEntry key %s\n", newEntry->key);
	// printf("entry_temp is %s| newEntry is %s\n", temp->key, temp->next->key); //proof their linked
	// printf("entry_temp value %d| newEntry value %d\n", temp->values->next->value, newEntry->values->value);
}

void value_insertAtHead(int value_stored){
	value* newValue = value_init(value_stored);
	value_head = newValue;
	printf("value_insertAtHead: value_head is %d and newValue is %d\n",
	value_head->value, newValue->value);
	is_value_head = 1;
	return;
}


void value_insertAtTail(int value_stored){
	value* temp = value_head;
	value* newValue = value_init(value_stored);
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newValue;
	newValue->prev = temp;
	printf("value_insertAtTail: prev value is %d and newValue is %d\n",
	temp->value, newValue->value);
}

int commandMap(char **comCheck){
	if (strcasecmp(*comCheck, HELP)==0){
		command_help();
		userInput(com);
	}
	if (strcasecmp(*comCheck, SET	)==0){
		set(entry_head);
		userInput(com);
	}
	if (strcasecmp(*comCheck, GET)==0){
		get(entry_head);
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

void set(){ //might not need entry_head
	//want to create a new head LL after any set A x
	for (int l = 2; l < value_entries_counter; l++){
		value_entries[value_array_index] = atoi(comCheck[l]);
		value_array_index++;
		value_stored = value_entries[value_array_index-1];
		if (l == 2) {
			value_insertAtHead(value_stored); //point to null initially
		}  else {
			value_insertAtTail(value_stored);
		}
	}
	// printf("value head value %d\n",value_head->value);
	value_array_index = 0; //index for passed value array (pass to entry node)
	if (is_entry_head == 0){
		entry_insertAtHead();
	}
	else {
		entry_insertAtTail();
	}
	// printf("entry head value %s\n",entry_head->key);
	value_index = 0;
	printf("ok\n");
}

// void get_values(entry* tmp){
//
// }

void get_values(entry* tmp){
	value* tempValue = tmp->values;
	printf("[");
	while(tempValue->next != NULL){
		printf("%d", tempValue->value);
		printf(" ");
		tempValue = tempValue->next; //should reset tempvalue
	}
	printf("%d]\n", tempValue->value);
}

void get(){
	entry* tempEntry = entry_head;
	bool found = false;
	int keyLength = strlen(comCheck[1])-1;
	int tempLength = strlen(tempEntry->key);

	// printf("%s|%s|%d|%lu\n", tempEntry->key, comCheck[1], keyLength, strlen(tempEntry->key));
	if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
		printf("1 keyLength: %d and tempLength: %d\n", keyLength, tempLength);
		get_values(tempEntry);
		found = true;
		userInput(com);
	}
	while (found == false){
		//not getting the one where next is null i.e. tail
		// printf("1.5 keylength: %d and tempLength: %d\n", keyLength, tempLength);
		tempEntry = tempEntry->next;
		tempLength = strlen(tempEntry->key);
		// printf("2 keylength: %d and tempLength: %d\n", keyLength, tempLength);
		if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
			get_values(tempEntry);
			found = true;
			userInput(com);
		}
		tempLength = strlen(tempEntry->key);
		if (tempEntry->next == NULL && found == false){
			printf("no such key\n");
			break;
		}
	}
	userInput(com);
}

int command_help(){
	printf("%s", MANPAGE);
	userInput(com);
	return 0;
}


int userInput(char com[]){
	printf(">");
	i = 0;
	while(true){
		fgets(com, MAX_LINE_LENGTH, stdin);
		char *tokPtr = strtok(com, " ");
		while (tokPtr != NULL){
			comCheck[i] = tokPtr;
			tokPtr = strtok(NULL, " ");
			i++;
			// k++;
		}
		if (i > 1) value_entries_counter = i;
		free(tokPtr);
		k = 0;
		commandMap(comCheck);
	}
	return 0;
}

int main(void) {
	userInput(com);
	return 0;
}
