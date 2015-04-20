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
	puts("command_help called");
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
