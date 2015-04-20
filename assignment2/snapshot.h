#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#define MAX_KEY_LENGTH 16
#define MAX_LINE_LENGTH 1024

//function headers
int command_help();
int userInput(char arg1[]);
void print_manualFile();

typedef struct value value;
typedef struct entry entry;
typedef struct snapshot snapshot;

struct value {
  value* prev;
  value* next;
  int value;
};

struct entry {
  entry* prev;
  entry* next;
  value* values;
  char key[MAX_KEY_LENGTH];
};

struct snapshot {
  snapshot* prev;
  snapshot* next;
  entry* entries;
  int id;
};

#endif
