#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include "snapshot.h"
//head nodes for lists
value* value_head = NULL;
entry* entry_head = NULL;
snapshot* snapshot_head = NULL;

//node needed for appending
value* appValue = NULL;

int value_stored = 0; //integer value for value node
int value_index = 1; //index for value in LL
int value_array_index = 0; //index for values in passing array

//iterators
int i = 0;
int l = 0;
int j = 0;
int k = 0;

//boolean/integer 1/0 variables
int is_entry_head = 0; //to determine whether to add to head or tail
int is_value_head = 0;
int value_entries_counter = 0;
bool list_entries_called = false;
bool tail_called = false;

//arrays used
int value_entries[MAX_LINE_LENGTH];
char *revEntries[MAX_LINE_LENGTH];
char key[MAX_KEY_LENGTH];
char com[MAX_LINE_LENGTH]; //store initial command/input
char *com_check[MAX_LINE_LENGTH]; //stores current command/input

//entry node initialising struct
entry* entry_init(){
	entry* newEntry = (entry*)malloc(sizeof(struct entry));
	newEntry->next = NULL;
	newEntry->prev = NULL;
	newEntry->values = value_head;
	newEntry->value_head = value_head;
	value_index = 1;
	strcpy(newEntry->key,com_check[1]);
	return newEntry;

}

//called only if adding an entry head
void entry_insertAtHead(){
	entry_head = entry_init();
	is_entry_head = 1;
	return;
}

//otherwise inserted at the end of the tail
void entry_insertAtTail(){
	entry* temp = entry_head;
	entry* newEntry = entry_init();
	int key_length = strlen(newEntry->key);
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newEntry;
	newEntry->prev = temp;
	//deleting if there is a pre-existing key
	while(temp->prev != NULL){
		if(strncmp(temp->key,newEntry->key,key_length)==0){
			com_check[1] = (temp->key);
			tail_called = true;
			del(); //call delete with the to delete node's key
			return;
		}
		if(temp->prev == NULL) break;
		temp = temp->prev;
	} if(strncmp(temp->key,newEntry->key,key_length)==0){
		com_check[1] = (temp->key);
		tail_called = true;
		del();
		return;
	}

}

//value node initialising struct
value* value_init(int value_stored, int value_index){
	value* newValue = (value*)malloc(sizeof(struct value));
	newValue->next = NULL;
	newValue->prev = NULL;
	newValue->value = value_stored;
	newValue->value_index = value_index;
	return newValue;
}

//called only if adding an entry head
void value_insertAtHead(int value_stored, int value_index){
	value_head = value_init(value_stored, value_index);
	is_value_head = 1;
	return;
}

//else called to add value to the tail
void value_insertAtTail(int value_stored, int value_index){
	value* temp = value_head;
	value* newValue = value_init(value_stored, value_index);
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newValue;
	newValue->prev = temp;

}

/*Command Map Function.
	Uses multiple IF statement's to determine
	which function to call based on the given
	input. */
int commandMap(char **com_check){
	if (strcasecmp(*com_check, HELP)==0){
		command_help();
		userInput(com);
	}
	if (strcasecmp(*com_check, SET	)==0){
		set();
		userInput(com);
	}
	if (strcasecmp(*com_check, GET)==0){
		get();
		userInput(com);
	}
	if ((strcasecmp(*com_check, SNAPSHOT)==0)){
		userInput(com);
	}
	if (strcasecmp(*com_check, DEL)==0){
		del();
		printf("ok\n\n");
		userInput(com);
	}
	if (strcasecmp(*com_check, MIN)==0){
		min();
		userInput(com);
	}
	if (strcasecmp(*com_check, MAX)==0){
		max();
		userInput(com);
	}
	if (strcasecmp(*com_check, SUM)==0){
		sum();
		userInput(com);
	}
	if (strcasecmp(*com_check, LEN)==0){
		len();
		userInput(com);
	}
	if (strcasecmp(*com_check, POP)==0){
		pop();
		userInput(com);
	}

	if (strcasecmp(*com_check, PLUCK)==0){
		pluck();
		userInput(com);
	}

	if (strcasecmp(*com_check, PICK)==0){
		pick();
		userInput(com);
	}

	if (strcasecmp(*com_check, PUSH)==0){
		push();
		userInput(com);
	}


	if (strcasecmp(*com_check, APPEND)==0){
		append();
		userInput(com);
	}

	/*List Keys/Entries/Snapshots all have
		two commands which need to be processed
		so they require a nested IF statement.*/
	if (strcasecmp(*com_check, LIST)==0){
		char *tempCommand[MAX_LINE_LENGTH];
		*tempCommand = *++com_check;
		if (strcasecmp(*tempCommand, KEYS) == 0){
			list_keys();
			userInput(com);
		}
		if (strcasecmp(*tempCommand, ENTRIES) == 0){
			list_entries();
			userInput(com);
		}
		if (strcasecmp(*tempCommand, SNAPSHOTS) == 0){
			list_snapshots();
			userInput(com);
		}
	}

	if (strcasecmp(*com_check, BYE) == 0){
		bye();
	}
	//If given input doesn't match any commands.
	printf("no such command\n\n");
	userInput(com);
	return 0;
}


/*Finds entry for commands with just 1 given parameter
	e.g. PUSH, MIN, MAX, etc*/
entry* find_entry_key(){
	entry* temp_entry = entry_head;
	bool found = false;
	int key_length = strlen(com_check[1])-1; //-1 needed for null-terminator counting
	int temp_length = strlen(temp_entry->key);
	//if both key and given input are the same upto the input's length -1 and their
	//sizes are the same then return entry.
	if(strncmp(temp_entry->key,com_check[1],key_length) == 0 && key_length == temp_length){
		found = true;
		return temp_entry;
	}
	while (found == false){
		temp_entry = temp_entry->next; //keep iterating until found or end of list
		if(temp_entry == NULL){
			printf("no such key\n\n");
			break;
		}
		temp_length = strlen(temp_entry->key);
		if(strncmp(temp_entry->key,com_check[1],key_length) == 0 && key_length == temp_length){
			found = true;
			return temp_entry;
		}
		if (temp_entry->next == NULL && found == false){
			printf("no such key\n\n");
			break;
		}
	}
	return NULL;
}

/*Created since most of the arithmetic functions
	begin in the same way. This simply cheeky if
	the input is valid and then returns a pointer
	to the request entry's values.*/
value* arithmetic_functions(){
	char message[] = "no such key";
	entry_head_null_print(message);
	entry* temp_entry = find_entry_key(&com_check[1]);
	if(temp_entry==NULL){
		userInput(com);
	}
	value* temp_value = temp_entry->values;
	return temp_value;
}

//counts total values in an entry
void len(){
	value* temp_value = arithmetic_functions();
	int length = 0;
	while(temp_value->next != NULL){
		length++;
		temp_value = temp_value->next;
	}
	length++;
	printf("%d\n\n",length);
	userInput(com);
}

//counts total sum of values in an entry
void sum(){
	value* temp_value = arithmetic_functions();
	int sum = 0;
	while(temp_value->next != NULL){
		sum+=temp_value->value;
		temp_value = temp_value->next;
	}
	sum+=temp_value->value;
	printf("%d\n\n",sum);
	userInput(com);
}

//searches for the max value in an entry
void max(){
	value* temp_value = arithmetic_functions();
	int max = temp_value->value;
	while(temp_value->next != NULL){
		if(temp_value->value < temp_value->next->value){
			max = temp_value->next->value;
		}
		temp_value = temp_value->next;
	}
	if(max < temp_value->value){
		max = temp_value->value;
	}
	printf("%d\n\n",max);
	userInput(com);
}

//searches for the min value in an entry
void min(){
	value* temp_value = arithmetic_functions();
	int min = temp_value->value;
	while(temp_value->next != NULL){
		if(temp_value->value > temp_value->next->value){
			min = temp_value->next->value;
		}
		temp_value = temp_value->next;
	}
	if(min > temp_value->value){
		min = temp_value->value;
	}
	printf("%d\n\n",min);
	userInput(com);
}

/*"cleans up" the program via iteraitng through
	every single node (both value and entry),
	deleting the node after it has assigned a temp
	node to its value.*/
void bye(){
	printf("bye\n\n");
	while(entry_head){
		entry* entry_delete = entry_head->next;
		while(entry_head->values){
			value* value_delete = entry_head->values->next;
			free(entry_head->values);
			entry_head->values = value_delete;
		}
		free(entry_head);
		entry_head = entry_delete;
	}
	free(snapshot_head);
	exit(0); //0 indicates successful exit
}

/*basic function to check whether or not the entry's head
	node is null, and prints the message given as an argument.*/
void entry_head_null_print(char message[]){
	if(entry_head == NULL){
		printf("%s\n\n", message);
		userInput(com);
	}
}

/*similar to find_entry_key() except it is used for
	functions which require >1 command e.g. PUSH and
	APPEND.*/
entry* find_entry(){
	entry* temp_entry = entry_head;
	bool found = false;
	//no -1 needed here
	int key_length = strlen(com_check[1]);
	int temp_length = strlen(temp_entry->key);
	//if sizes and string (upto key_length) are the same evaluates to true
	if(strncmp(temp_entry->key,com_check[1],key_length) == 0 && key_length == temp_length){
		found = true;
		return temp_entry;
	}
	//keep iterating until we find it or end of list
	while (found == false){
		temp_entry = temp_entry->next;
		if(temp_entry == NULL){
			printf("invalid input\n\n");
			userInput(com);
		}
		temp_length = strlen(temp_entry->key);
		if(strncmp(temp_entry->key,com_check[1],key_length) == 0 && key_length == temp_length){
			found = true;
			return temp_entry;
		}
		//end of list and we haven't found it
		if (temp_entry->next == NULL && found == false){
			printf("invalid input\n\n");
			userInput(com);
		}
	}
	return temp_entry;
}

//Function to pick value from supplied input
void pick(){
	char message[] = "no such key";
	entry_head_null_print(message);
	entry* temp_entry = find_entry(&com_check[1]);
	value* temp_value = temp_entry->values;
	int index = atoi(com_check[2]); //index 2nd argument
	if(index < 1){ //can't have <= 0 indices
		printf("index out of range\n\n");
		return;
	}
	bool found = false; //found flag
	while(temp_value->next != NULL){
		if(temp_value->value_index == index){
			printf("%d\n\n", temp_value->value);
			found = true;
			break;
		} //iterating to find entry value
		else {
			temp_value = temp_value->next;
		}
	} //if it's at the end of the list (last node)
	if((temp_value->value_index == index)&&(found == false)){
		found = true;
		printf("%d\n\n", temp_value->value);
	} else if (found == false){
		printf("index out of range\n\n");
	}
	return;
}

//Function to delete index for pluck (not complete)
void rem_val_index(entry* temp_entry, value* temp_value, int index){
	bool found = false;
	while(temp_value->next != NULL){
		if(temp_value->value_index == index){
			printf("%d\n\n", temp_value->value);
			found = true;
		}
		temp_value = temp_value->next;
	}
	if((temp_value->value_index == index)&&(found == false)){
		found = true;
		printf("%d\n\n", temp_value->value);
	} else if (found == false){
		printf("index out of range\n\n");
	}
	userInput(com);
}

//Pluck function to retrieve key at index and delete said index value
//(Not complete)
void pluck(){
	char message[] = "no such key";
	entry_head_null_print(message);
	entry* temp_entry = find_entry(&com_check[1]); //entry
	value* temp_value = temp_entry->value_head;
	int index = atoi(com_check[2]);
	if(index < 1){
		printf("index out of range\n\n");
		return;
	}
	rem_val_index(temp_entry, temp_value, index);
	return;
}

//APPEND function to add values to the end of an entry
void append(){
	char message[] = "no such key";
	entry_head_null_print(message);
	entry* temp_entry = find_entry(&com_check[1]); //entry
	int pre_swp_int = 0;
	int count = 0;
	int ar[MAX_LINE_LENGTH];
	//Add each value to an array of maximum line length (1024)
	for (int l = 2; l < value_entries_counter; l++){
		value_entries[value_array_index] = atoi(com_check[l]);
		value_array_index++;
		value_stored = value_entries[value_array_index-1];
		pre_swp_int = value_stored;
		ar[count] = value_stored;
		count++;
	}

	for(int i = 0; i < count; i++){
		value* temp = temp_entry->values;
		value_index++;
		//create new value node with value of array's i
		appValue = value_init(ar[i], value_index);
		//add it to the tail
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = appValue;
		appValue->prev = temp;
	}


	printf("ok\n\n");
	userInput(com);
}

//POP function which dispalys front value and removes it
void pop(){
	char message[] = "nil";
	entry_head_null_print(message);
	entry* temp_entry = entry_head;
	bool found = false;
	int key_length = strlen(com_check[1])-1; //since we're only passing it key
	int temp_length = strlen(temp_entry->key);
	if(strncmp(temp_entry->key,com_check[1],key_length) == 0 &&
	key_length == temp_length){
		found = true;
		rem_val_head(temp_entry); //call function to remove head now
		userInput(com);
	}
	while (found == false){ //keep iterating until found or end of list
		temp_entry = temp_entry->next;
		if(temp_entry == NULL){
			printf("nil\n\n");
			break;
		}
		temp_length = strlen(temp_entry->key); //"refresh" temp_length
		if(strncmp(temp_entry->key,com_check[1],key_length) == 0 &&
		key_length == temp_length){
			found = true;
			rem_val_head(temp_entry);
			userInput(com);
		}
		if (temp_entry->next == NULL && found == false){
			printf("nil\n\n");
			break;
		}
	}
	userInput(com);
}

//Function to remove the head node for push
void rem_val_head(entry* tmp){
	value* tmpValue = tmp->values;
	if(tmp->values == NULL){ //check to see a node exists
		printf("nil\n\n");
		free(tmpValue);
		return;
	}
	printf("%d\n\n", tmp->values->value);
	//head becomes head's next node
	tmp->values = tmp->values->next;
	tmpValue->next = NULL;
	tmpValue->prev = NULL;
	free(tmpValue);
}

//PUSH function which adds new value nodes to the front of the line
void push(){
	char message[] = "no such key";
	entry_head_null_print(message);
	entry* temp_entry = find_entry(&com_check[1]);
	int pre_swp_int = 0;
	int count = 0;
	int ar[MAX_LINE_LENGTH];
	//Add each value to an array of maximum line length (1024)
	for (int l = 2; l < value_entries_counter; l++){
		value_entries[value_array_index] = atoi(com_check[l]);
		value_array_index++;
		value_stored = value_entries[value_array_index-1];
		pre_swp_int = value_stored;
		ar[count] = value_stored;
		count++;
	}

	for(int i = 0; i < count; i++){
		value_index++;
		value* head_ptr = temp_entry->values;
		//create new value node
		value* newValue = value_init(ar[i], value_index);
		//add it to the front
		temp_entry->values = newValue;
		//move previous one to 'next'
		temp_entry->values->next = head_ptr;
	}

	printf("ok\n\n");
	userInput(com);
}

//DEL function to delete given entry
void del(){
	entry* temp_entry = entry_head;
	int key_length = strlen(com_check[1])-1; //only given 1 argument
	bool found = false;
	if (temp_entry==NULL){ //if no head exists
		printf("no such key\n\n");
		userInput(com);
	}

	int temp_length = strlen(temp_entry->key);
	//finding node to delete
	if (temp_entry->next == NULL && (strncmp(temp_entry->key,com_check[1],key_length) == 0 &&
	(key_length == temp_length))){ //we've found it on the first go
	found = true;
}
while(found == false){
	if(temp_entry == NULL){
		printf("no such key\n\n");
		userInput(com);
	}
	temp_length = strlen(temp_entry->key);
	if (tail_called == true){ //incase called by insert_atTail function
		key_length = key_length+1;
		tail_called = false;
	}
	if (strncmp(temp_entry->key,com_check[1],key_length) == 0
	&& (key_length == temp_length)){ //found key (same lengths)
		found = true;
		break;
	}
	if ((temp_entry->next == NULL) && (found = false)){
		printf("no such key\n\n");
		userInput(com);
	}
	temp_entry = temp_entry->next;
}

// single noded list
if((temp_entry->next == NULL)&&(temp_entry->prev == NULL)){
	while(entry_head->values){//while true
		if(temp_entry->values->next != NULL){
			value* value_delete = temp_entry->values->next; //temp value
			free(temp_entry->values);
			temp_entry->values = value_delete;
		} else {
			free(entry_head->values);
			break;
		}

	}
	entry_head = NULL;
	free(temp_entry); //clean up remaining nodes
	free(entry_head);
	is_entry_head = 0; //so our next node is head
	return;
}

// at the head
if((temp_entry->next != NULL)&&(temp_entry->prev == NULL)){
	entry_head = temp_entry->next; //connect new head to null
	temp_entry->next->prev = NULL;
	while(temp_entry->values){ //while true
		value* value_delete = temp_entry->values->next;
		free(temp_entry->values);
		temp_entry->values = value_delete; //temp value
	}
	is_entry_head = 0;
	free(temp_entry); //so our next node is head
	return;
}

//in the middle
if((temp_entry->next != NULL)&&(temp_entry->prev != NULL)){
	temp_entry->prev->next = temp_entry->next; //reconnect prev & next
	temp_entry->next->prev = temp_entry->prev; //to each other
	while(temp_entry->values){ //while true
		value* value_delete = temp_entry->values->next;
		free(temp_entry->values);
		temp_entry->values = value_delete;
	}
	free(temp_entry);
	return;
}

// at the tail
if((temp_entry->next == NULL)&&(temp_entry->prev != NULL)){
	temp_entry->prev->next = NULL; //connect new tail to null
	while(temp_entry->values){
		value* value_delete = temp_entry->values->next;
		free(temp_entry->values);
		temp_entry->values = value_delete;
	}
	free(temp_entry);
	return;
}
}

//SET function to set new entry values
void set(){
	value_index = 1;
	for (int l = 2; l < value_entries_counter; l++){
		value_entries[value_array_index] = atoi(com_check[l]);
		value_array_index++;
		value_stored = value_entries[value_array_index-1];
		if (l == 2) { //at l == 2 we get the first entry
			value_index = 1;
			value_insertAtHead(value_stored, value_index); //new head node
		}  else {
			value_index++;
			value_insertAtTail(value_stored, value_index); //new nodes at tail
		}
	}
	value_array_index = 0; //index for passed value array (pass to entry node)
	if (is_entry_head == 0){ //boolean to know when to make it a head
		entry_insertAtHead();
	}
	else {
		entry_insertAtTail();
	}
	value_index = 0;
	printf("ok\n\n");
	userInput(com);
}

//LIST SNAPSHOTS functon not complete
void list_snapshots(){
	if(is_entry_head == 0){
		printf("no snapshots\n\n");
		return;
	}
}

//LIST ENTRIES function lists all keys and their values
void list_entries(){
	//will just call keys with an added flag
	list_entries_called = true;
	list_keys();
}


void list_keys(){
	//no keys check
	if((is_entry_head == 0)&&(list_entries_called == false)&&(entry_head == NULL)){
		printf("no keys\n\n");
		return;
	}
	//no keys+entries check
	if((is_entry_head == 0)&&(list_entries_called == true)&&(entry_head == NULL)){
		list_entries_called = false;
		printf("no entries\n\n");
		return;
	}

	//iterators (defined globally)
	l = 0;
	k = 0;

	entry* temp_entry = entry_head;
	while(temp_entry->next != NULL){ //>1 entry
		//assign array elements to entry's keys
		revEntries[l] = temp_entry->key;
		temp_entry = temp_entry->next;
		l++;
	}

	if (temp_entry != NULL){
		revEntries[l] = temp_entry->key;
	}

	reverseEntries(revEntries);


}

/*Reverse entries simply flips all the entries
	and then prints them.*/
void reverseEntries(char **revEntries){
	//if entries needs to be listed
	if(list_entries_called == true){
		while(l >= 0){
			//print each element of the array
			printf("%s", revEntries[l]);
			printf(" ");
			com_check[1] = revEntries[l];
			l--;
			get(); //prints values
		}
	} else {
		for(k = l; k >= 0; k--){
			printf("%s", revEntries[k]); //just print keys
			printf("\n");

		}
	}
	printf("\n");
	list_entries_called = false;
}

//get_values does the actual printing
void get_values(entry* tmp){
	value* temp_value = tmp->values;

	if(temp_value == NULL){
		printf("[]\n\n");
		return;
	}

	printf("[");
	while(temp_value->next != NULL){ //iterate through and print values
		printf("%d", temp_value->value);
		printf(" ");
		temp_value = temp_value->next;
	}
	if (list_entries_called == true){
		//cant have double new line for list entries
		printf("%d]\n", temp_value->value);
	} else {
		printf("%d]\n\n", temp_value->value);
	}
	if (list_entries_called == true){
		reverseEntries((revEntries));
	}
}

//GET function prints the entry and it's values
void get(){
	char message[] = "no such key";
	entry_head_null_print(message);
	entry* temp_entry = entry_head;
	bool found = false;
	int key_length = strlen(com_check[1])-1; //only 1 argument
	int temp_length = strlen(temp_entry->key);
	if (list_entries_called == true){
		key_length = key_length+1;
	}
	//if we've found the key - get values
	if(strncmp(temp_entry->key,com_check[1],key_length) == 0
	&& key_length == temp_length){
		get_values(temp_entry);
		found = true;
		userInput(com);
	}
	//otherwise iterate until we can find it or end of list
	while (found == false){
		temp_entry = temp_entry->next;
		if(temp_entry == NULL){
			printf("no such key\n\n");
			break;
		}
		temp_length = strlen(temp_entry->key);
		if(strncmp(temp_entry->key,com_check[1],key_length) == 0
		&& key_length == temp_length){
			get_values(temp_entry);
			found = true;
			userInput(com);
		}
		//at the end and we never found the key
		if (temp_entry->next == NULL && found == false){
			printf("no such key\n\n");
			break;
		}
	}
	userInput(com);
}

//command_help calls the man page
int command_help(){
	printf("%s\n", MANPAGE);
	userInput(com);
	return 0;
}

//scans and stores the user input
int userInput(char com[]){
	printf(">");
	i = 0;
	while(true){ //will run until user has inputed something
		fgets(com, MAX_LINE_LENGTH, stdin);
		char *tokPtr = strtok(com, " "); //space delimitor
		while (tokPtr != NULL){
			com_check[i] = tokPtr;
			tokPtr = strtok(NULL, " ");
			i++;
		}
		if (i > 1) value_entries_counter = i;
		free(tokPtr);
		commandMap(com_check); //call command (function) map
	}
	return 0;
}

int main(void) {
	userInput(com);
	return 0;
}
