#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
//fscan,scanf,strtoc,strsep, delimiter is spaces
//free all memory

#include "snapshot.h"
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
int value_entries_counter = 0;

int value_entries[MAX_LINE_LENGTH];
char key[MAX_KEY_LENGTH];
char com[MAX_LINE_LENGTH]; //store initial command/input
char *comCheck[MAX_LINE_LENGTH]; //stores current command/input


value* value_init(int value_int){
	value* newValue = (value*)malloc(sizeof(struct value));
	newValue->next = NULL;
	newValue->prev = NULL;
	newValue->value = value_int;
	newValue->value_index = value_index;
	printf("value %d index is %d", newValue->value, newValue->value_index);
	value_index++;
	return newValue;
}
/*initialising our the linkedList's new node*/
//will implement functionality of passing it the
//value linked list
entry* entry_init(value** value_head){
	entry* newEntry = (entry*)malloc(sizeof(struct entry));
	newEntry->next = NULL;
	newEntry->prev = NULL;
	newEntry->values = *value_head;
	strcpy(newEntry->key,comCheck[1]);
	return newEntry;
}

void entry_insertAtHead(value **value_head){
	entry* newEntry = entry_init(value_head);
	if(entry_head == NULL){
		entry_head = newEntry;
		printf("entry_head is %s\n", entry_head->key);
		printf("newEntry is %s\n", newEntry->key);
		is_entry_head = 1;
		return;
	}
	entry_head->prev = newEntry;
	newEntry->next = entry_head;
	entry_head = newEntry;
	is_entry_head = 1;
}


void entry_insertAtTail(value **value_head){
	entry* temp = entry_head;
	entry* newEntry = entry_init(value_head);
	while(temp->next != NULL){
		temp = temp->next;
	}
	// printf("temp key is: %s\nnewEntry.key is: %s\n",
	// temp->key, newEntry->key);
	temp->next = newEntry;
	newEntry->prev = temp;
	// printf("temp key is: %s\nnewEntry.key is: %s\n",
	// temp->key, newEntry->key);
}

void value_insertAtHead(int value){
	entry* newEntry = entry_init(&value_head);
	if(entry_head == NULL){
		entry_head = newEntry;
		printf("entry_head is %s\n", entry_head->key);
		printf("newEntry is %s\n", newEntry->key);
		is_entry_head = 1;
		return;
	}
	entry_head->prev = newEntry;
	newEntry->next = entry_head;
	entry_head = newEntry;
	is_entry_head = 1;
}


// void value_insertAtTail(int value){
// 	value* temp = value_head;
// 	value* newValue = value_init(value);
// 	while(temp->next != NULL){
// 		temp = temp->next;
// 	}
// 	temp->next = newValue;
// 	newValue->prev = temp;
// 	}

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
	for (int k = 2; k < value_entries_counter+2; k++){ //+2 for arg name and "set"
	value_entries[value_array_index] = atoi(comCheck[k]);
	value_array_index++;
	printf("%d: %d\n", value_array_index, value_entries[value_array_index-1]);
}
value_array_index = 0; //index for passed value array (pass to entry node)
if (is_entry_head == 0){
	entry_insertAtHead(&value_head);
}
else {
	entry_insertAtTail(&value_head);
}
value_insertAtHead(value_stored); //point to null initially
/*We will need to pass the entire array of values to the entry
	node that it has been assigned to. e.g. A will get value_entries,
	then next sweep around B will get value_entries (as its just user input).
	First value becomes head, then the rest get added to tail.
	so element 1 becomes head, 2 becomes tail, then 3 becomes tail making the
	order 1 -> 2 -> 3.
	Can insert tails with a for-loop of adding nodes.*/
printf("ok\n");
}

int command_help(){
	printf("%s", MANPAGE);
	userInput(com);
	return 0;
}


int userInput(char com[]){
	printf(">");
	k = j + k;
	while(1){
		fgets(com, MAX_LINE_LENGTH, stdin);
		char *tokPtr = strtok(com, " ");
		while (tokPtr != NULL){
			comCheck[i] = tokPtr;
			tokPtr = strtok(NULL, " ");
			i++;
		}
		j = i - k; //iterator used for entries array passing
		if (i > 1) value_entries_counter = j - 2;
		free(tokPtr);
		commandMap(comCheck);
	}
	return 0;
}

int main(void) {
	userInput(com);
	return 0;
}
