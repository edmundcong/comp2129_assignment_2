#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
//fscan,scanf,strtoc,strsep, delimiter is spaces
//free all memory

//note: use str_length not sizeof(only works at compile time)
//cant overwrite entry if its the first element of the list - del function maybe

#include "snapshot.h"
value* values_temp = NULL;
value* value_head = NULL;
entry* entry_head = NULL; //pointer to DLL head
snapshot* snapshot_head = NULL;

int value_stored = 0; //integer value for value node
int value_index = 1; //index for value in LL
int value_array_index = 0; //index for values in passing array

int entries_listed = 0;
int i = 0;
int l = 0;
int j = 0;
int k = 0;

int is_entry_head = 0; //to determine whether to add to head or tail
int is_value_head = 0;
int value_entries_counter = 0;
bool list_entries_called = false;
bool tail_called = false;

int value_entries[MAX_LINE_LENGTH];
char *revEntries[MAX_LINE_LENGTH];
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
	// printf("newEntry is %s\n", newEntry->key);
	return;
}


void entry_insertAtTail(){
	entry* temp = entry_head;
	entry* newEntry = entry_init();
	int keyLength = strlen(newEntry->key);
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newEntry;
	newEntry->prev = temp;

	while(temp->prev != NULL){
		if(strncmp(temp->key,newEntry->key,keyLength)==0){
			comCheck[1] = (temp->key);
			tail_called = true;
			del();
			return;
		}
		if(temp->prev == NULL) break;
		temp = temp->prev;
	}
}

// if(temp->prev == NULL){
// 	if(strncmp(temp->key,entry_head->key,keyLength)==0){
// 		comCheck[1] = (temp->key);
// 		tail_called = true; //this can delete head but causes list entries to break
// 		del();
// 		return;
// 	}
// }

void value_insertAtHead(int value_stored){
	value* newValue = value_init(value_stored);
	value_head = newValue;
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
	// printf("value_insertAtTail: prev value is %d and newValue is %d\n",
	// temp->value, newValue->value);
}

int commandMap(char **comCheck){
	if (strcasecmp(*comCheck, HELP)==0){
		command_help();
		userInput(com);
	}
	if (strcasecmp(*comCheck, SET	)==0){
		set();
		userInput(com);
	}
	if (strcasecmp(*comCheck, GET)==0){
		get();
		userInput(com);
	}
	if ((strcasecmp(*comCheck, SNAPSHOT)==0)){
		printf("SNAPSHOT called\n");
		userInput(com);
	}
	if (strcasecmp(*comCheck, DEL)==0){
		del();
		printf("ok\n\n");
		userInput(com);
	}

	if (strcasecmp(*comCheck, POP)==0){
		pop();
		userInput(com);
	}

	if (strcasecmp(*comCheck, PUSH)==0){
		push();
		userInput(com);
	}

	if (strcasecmp(*comCheck, APPEND)==0){
		append();
		userInput(com);
	}

	if (strcasecmp(*comCheck, LIST)==0){
		char *tempCommand[MAX_LINE_LENGTH];
		*tempCommand = *++comCheck;
		if (strcasecmp(*tempCommand, KEYS) == 0){
			list_keys();
			userInput(com);
		}
		if (strcasecmp(*tempCommand, ENTRIES) == 0){
			list_entries();
			userInput(com);
		}
	}

	if (strcasecmp(*comCheck, BYE) == 0){
		printf("bye\n\n");
		// while(entry_head){
		// 	entry* entry_delete = entry_head->next;
		// 	while(value_head){
		// 		value* value_delete = value_head->next;
		// 		free(value_head);
		// 		value_head = value_delete;
		// 	}
		// 	free(entry_head);
		// 	entry_head = entry_delete;
		// }
		exit(0);
	}
	printf("no such command\n\n");
	userInput(com);
	return 0;
}

void entry_head_null_print(char message[]){
	if(entry_head == NULL){
		printf("%s\n\n", message);
		userInput(com);
	}
}

entry* find_entry(){ //use for push and append
	entry* tempEntry = entry_head;
	bool found = false;
	int keyLength = strlen(comCheck[1]);
	int tempLength = strlen(tempEntry->key);
	if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
		found = true;
		return tempEntry;
	}
	while (found == false){
		tempEntry = tempEntry->next;
		if(tempEntry == NULL){
			printf("invalid input\n\n");
			userInput(com);
		}
		tempLength = strlen(tempEntry->key);
		if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
			found = true;
			return tempEntry;
		}
		if (tempEntry->next == NULL && found == false){
			printf("invalid input\n\n");
			userInput(com);
		}
	}
	return tempEntry;
}

void append(){
	char message[] = "invalid input";
	entry_head_null_print(message);
	entry* tempEntry = find_entry(&comCheck[1]); //entry
	int pre_swp_int = 0;
	int count = 0;
	int ar[MAX_LINE_LENGTH];
	for (int l = 2; l < value_entries_counter; l++){
		value_entries[value_array_index] = atoi(comCheck[l]);
		value_array_index++;
		value_stored = value_entries[value_array_index-1];
		pre_swp_int = value_stored;
		ar[count] = value_stored;
		count++; //same as value_array_index
	}

	for(int i = 0; i < count; i++){
		value* temp = tempEntry->values;
		value* newValue = value_init(ar[i]);
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newValue;
		newValue->prev = temp;
		// value* head_ptr = tempEntry->values;
		// value* newValue = value_init(ar[i]);
		// while(tempEntry->values->next != NULL){
		// 	value* newValue = value_init(ar[i]);
		// 	tempEntry->values->next = newValue;
		// 	newValue->prev = tempEntry->values;
		// 	tempEntry->values = tempEntry->values->next;
		// }
		// value_insertAtTail(ar[i]);
		// tempEntry->values = head_ptr;
		// tempEntry->values->next = newValue;
	}
	// get_values(tempEntry);
	// newValue = tempEntry->values;
	printf("ok\n\n");
	userInput(com);
}


void push(){
	char message[] = "invalid input";
	entry_head_null_print(message);
	entry* tempEntry = find_entry(&comCheck[1]); //entry
	int pre_swp_int = 0;
	// int tmp = 0;
	int count = 0;
	// int i = 0;
	int ar[MAX_LINE_LENGTH];
	// int post_swp_int = 0;
	for (int l = 2; l < value_entries_counter; l++){
		value_entries[value_array_index] = atoi(comCheck[l]);
		value_array_index++;
		value_stored = value_entries[value_array_index-1];
		pre_swp_int = value_stored;
		ar[count] = value_stored;
		count++; //same as value_array_index
		// value_insertAtTail(value_stored);
		// tempEntry->values->value
	}

	for(int i = 0; i < count; i++){
		value* head_ptr = tempEntry->values;
		value* newValue = value_init(ar[i]);

		tempEntry->values = newValue;
		tempEntry->values->next = head_ptr;
	}

	get_values(tempEntry);
	printf("ok\n\n");
	userInput(com);
}

// printf("l:%d == value_entries_counter:%d\n", l, value_entries_counter);
// if (l == value_entries_counter) {
// 	newValue = value_init(value_stored);
// 	printf("1 newvalue value %d\n", newValue->value);
// }  else {
// newValue = value_init(value_stored);
//
// while(newValue != NULL){
// 	// printf("\ntempEntry value %d\n", newValue->value);
// 	// printf("post_swp_int: %d\n", post_swp_int);
// 	// printf("pre_swp_int: %d\n\n", pre_swp_int);
// 	// post_swp_int = newValue->value;
// 	// newValue->value = pre_swp_int;
// 	// newValue->next->value = pre_swp_int;
// 	// newValue = newValue->next;
// 	if(newValue == NULL){
// 		// printf("tempEntry->value is null\n");
// 		break;
// 	}
// 	if(newValue->next == NULL){
// 		// printf("%d\n", pre_swp_int); //
// 		break;
// 	}
// }
// tempEntry->values->prev = newValue;
// newValue->next = tempEntry->values->next;
// printf("3 newvalue value %d\n", newValue->value);

void pop(){
	char message[] = "nil";
	entry_head_null_print(message);
	entry* tempEntry = entry_head;
	bool found = false;
	int keyLength = strlen(comCheck[1])-1;
	int tempLength = strlen(tempEntry->key);

	if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
		found = true;
		rem_val_head(tempEntry);
		userInput(com);
	}
	while (found == false){
		tempEntry = tempEntry->next;
		if(tempEntry == NULL){
			printf("nil\n\n");
			break;
		}
		tempLength = strlen(tempEntry->key);
		if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
			found = true;
			rem_val_head(tempEntry);
			userInput(com);
		}
		if (tempEntry->next == NULL && found == false){
			printf("nil\n\n");
			break;
		}
	}
	userInput(com);
}

void rem_val_head(entry* tmp){
	value* tmpValue = tmp->values;
	if(tmp->values == NULL){
		printf("nil\n\n");
		free(tmpValue);
		return;
	}

	printf("%d\n\n", tmp->values->value);
	tmp->values = tmp->values->next;
	// tmp->values->prev = tmp->values;

	tmpValue->next = NULL;
	tmpValue->prev = NULL;
	free(tmpValue);

}

void del(){
	//double delete past first node doesn't work
	//boundary cases
	//word input has more errors
	entry* tempEntry = entry_head;
	int keyLength = strlen(comCheck[1])-1;
	bool found = false;
	if (tempEntry==NULL){ //if no head exists
		printf("no such key\n\n");
		userInput(com);
	}

	int tempLength = strlen(tempEntry->key);
	/*finding the node to delete*/
	if (tempEntry->next == NULL && (strncmp(tempEntry->key,comCheck[1],keyLength) == 0 &&
	(keyLength == tempLength))){ //we've found it on the first go
	found = true;
}
while(found == false){
	tempLength = strlen(tempEntry->key);
	if (tail_called == true){ //incase called by insert_atTail function
		keyLength = keyLength+1;
		tail_called = false;
	}
	if (strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && (keyLength == tempLength)){
		found = true;
		break;
	}
	if ((tempEntry->next == NULL) && (found = false)){
		printf("no such key\n\n");
		userInput(com);
	}
	tempEntry = tempEntry->next;
}
value* tempValue;

// singular list
if((tempEntry->next == NULL)&&(tempEntry->prev == NULL)){
	while(entry_head->values->next != NULL){
		tempValue = tempEntry->values;
		tempEntry->values = tempEntry->values->next;
		free(tempValue); //need to free all vlaues
	}
	entry_head = NULL;
	free(entry_head);
	is_entry_head = 0;
	return;
}
// at the head
if((tempEntry->next != NULL)&&(tempEntry->prev == NULL)){
	entry_head = tempEntry->next;
	tempEntry->next->prev = NULL;
	while(tempEntry->values->next != NULL){ //entry_head to tempentry
		tempValue = tempEntry->values;
		tempEntry->values = tempEntry->values->next;
		free(tempValue); //need to free all vlaues
	}
	is_entry_head = 0;
	free(tempEntry);
	return;
}

//in the middle
if((tempEntry->next != NULL)&&(tempEntry->prev != NULL)){
	tempEntry->prev->next = tempEntry->next;
	tempEntry->next->prev = tempEntry->prev;
	while(tempEntry->values->next != NULL){ //delete all of entry's values
	//move to next node then delete prev node with temp
	tempValue = tempEntry->values;
	tempEntry->values = tempEntry->values->next;
	free(tempValue); //need to free all vlaues
}
free(tempEntry);
return;
}

// at the tail
if((tempEntry->next == NULL)&&(tempEntry->prev != NULL)){
	while(tempEntry->values->next != NULL){
		tempValue = tempEntry->values;
		tempEntry->values = tempEntry->values->next;
		free(tempValue);
	}
	tempEntry->prev->next = NULL;
	free(tempEntry);
	return;
}
}


void set(){
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
	value_array_index = 0; //index for passed value array (pass to entry node)
	if (is_entry_head == 0){
		entry_insertAtHead();
	}
	else {
		entry_insertAtTail();
	}
	value_index = 0;
	printf("ok\n\n");
	userInput(com);
}

void list_entries(){
	list_entries_called = true;
	list_keys();
}

void list_keys(){
	if((is_entry_head == 0)&&(list_entries_called == false)){
		printf("no keys\n\n");
		return;
	}
	if((is_entry_head == 0)&&(list_entries_called == true)){
		list_entries_called = false;
		printf("no entries\n\n");
		return;
	}

	l = 0;
	k = 0;

	entry* tempEntry = entry_head;
	while(tempEntry->next != NULL){ //>1 entry
		revEntries[l] = tempEntry->key;
		tempEntry = tempEntry->next;
		l++;
	}

	if (tempEntry != NULL){
		revEntries[l] = tempEntry->key;
	}

	reverseEntries(revEntries);


}

void reverseEntries(char **revEntries){
	if(list_entries_called == true){
		while(l >= 0){
			printf("%s", revEntries[l]);
			printf(" ");
			comCheck[1] = revEntries[l];
			l--;
			get();
		}
	} else {
		for(k = l; k >= 0; k--){
			printf("%s", revEntries[k]);
			printf("\n");

		}
	}
	printf("\n");
	list_entries_called = false;
}


void get_values(entry* tmp){
	value* tempValue = tmp->values;

	if(tempValue == NULL){
		printf("[]\n\n");
		return;
	}

	printf("[");
	while(tempValue->next != NULL){
		printf("%d", tempValue->value);
		printf(" ");
		tempValue = tempValue->next; //should reset tempvalue
	}
	if (list_entries_called == true){
		printf("%d]\n", tempValue->value);
	} else {
		printf("%d]\n\n", tempValue->value);
	}
	if (list_entries_called == true){
		entries_listed++;
		reverseEntries((revEntries));
	}
}

void get(){
	char message[] = "no such key";
	entry_head_null_print(message);
	entry* tempEntry = entry_head;
	bool found = false;
	int keyLength = strlen(comCheck[1])-1;
	int tempLength = strlen(tempEntry->key);
	if (list_entries_called == true){
		keyLength = keyLength+1;
	}
	if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
		get_values(tempEntry);
		found = true;
		userInput(com);
	}
	while (found == false){
		// printf("1.5 keylength: %d and tempLength: %d\n", keyLength, tempLength);
		tempEntry = tempEntry->next;
		if(tempEntry == NULL){
			printf("no such key\n\n");
			break;
		}
		tempLength = strlen(tempEntry->key);
		// printf("2 keylength: %d and tempLength: %d\n", keyLength, tempLength);
		if(strncmp(tempEntry->key,comCheck[1],keyLength) == 0 && keyLength == tempLength){
			get_values(tempEntry);
			found = true;
			userInput(com);
		}
		// tempLength = strlen(tempEntry->key);
		if (tempEntry->next == NULL && found == false){
			printf("no such key\n\n");
			break;
		}
	}
	userInput(com);
}

int command_help(){
	printf("%s\n", MANPAGE);
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
		commandMap(comCheck);
	}
	return 0;
}

int main(void) {
	userInput(com);
	return 0;
}
