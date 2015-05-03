#ifndef SNAPSHOT_H
#define SNAPSHOT_H

//constants
#define MAX_KEY_LENGTH 16
#define MAX_LINE_LENGTH 1024
#define SEPARATOR " "

//commands
#define LIST_ENTRIES "LIST ENTRIES\n"
#define LIST_KEYS "LIST KEYS\n"
#define LIST_SNAPSHOTS "LIST SNAPSHOTS\n"
#define HELP "HELP\n"
#define BYE "BYE\n"
#define LIST "LIST"
#define KEYS "KEYS\n"
#define ENTRIES "ENTRIES\n"
#define SNAPSHOTS "SNAPSHOTS\n"
#define GET "GET"
#define DEL "DEL"
#define PURGE "PURGE"
#define SET "SET"
#define PUSH "PUSH"
#define APPEND "APPEND"
#define PICK "PICK"
#define PLUCK "PLUCK"
#define POP "POP"
#define DROP "DROP"
#define ROLLBACK "ROLLBACK"
#define CHECKOUT "CHECKOUT"
#define SNAPSHOT "SNAPSHOT\n"
#define MIN "MIN"
#define MAX "MAX"
#define SUM "SUM"
#define LEN "LEN"
#define REV "REV"
#define UNIQ "UNIQ"
#define SORT "SORT"

#define MANPAGE "BYE  clear database and exit\n"\
"HELP  display this help message\n"\
"\n"\
"LIST  KEYS	displays all keys in current state\n"\
"LIST  ENTRIES	displays all entries in current state\n"\
"LIST  SNAPSHOTS	displays all snapshots in the database\n"\
"\n"\
"GET  <key>	displays entry values\n"\
"DEL  <key>	deletes entry from current state\n"\
"PURGE  <key>	deletes entry from current state and snapshots\n"\
"\n"\
"SET  <key>  <value ...>		sets entry values\n"\
"PUSH  <key>  <value ...>	pushes each value to the front one at a time\n"\
"APPEND  <key>  <value ...>	append each value to the back one at a time\n"\
"\n"\
"PICK  <key>  <index>	displays entry value at index\n"\
"PLUCK  <key>  <index>	displays and removes entry value at index\n"\
"POP  <key>	displays and removes the front entry value\n"\
"DROP  <id>	deletes snapshot\n"\
"ROLLBACK  <id>	restores to snapshot and deletes newer snapshots\n"\
"CHECKOUT  <id>	replaces current state with a copy of snapshot\n"\
"SNAPSHOT	saves the current state as a snapshot\n"\
"\n"\
"MIN  <key>	displays minimum entry value\n"\
"MAX  <key>	displays maximum entry value\n"\
"SUM  <key>	displays sum of entry values\n"\
"LEN  <key>	displays number of entry values\n"\
\
"REV  <key>	reverses order of entry values\n"\
"UNIQ  <key>	removes repeated adjacent entry values\n"\
"SORT  <key>	sorts entry values in ascending order\n"\

typedef struct value value;
typedef struct entry entry;
typedef struct snapshot snapshot;

/*Function headers*/
int command_help();
int userInput(char com[]);
int commandMap(char **comCheck);
void pick();
void min();
void max();
void sum();
void len();
void set();
void push();
void append();
void del();
void get();
void pop();
void pluck();
void bye();
void list_keys();
void list_entries();
void list_snapshots();

/*node creating function headers*/
value* value_init(int value_stored, int value_index);
void value_insertAtHead(int value_stored, int value_index);
void value_insertAtTail(int value_stored, int value_index);
void entry_insertAtHead();
void entry_insertAtTail();
entry* entry_init();

/*Utility functions*/
void reverseEntries(char **revEntries);
void get_values(entry* tmp);
entry* find_entry_key(char **com_check);
void rem_val_head(entry* tmp);
void rem_val_index(entry* tmpEntry, value* tmp, int index);
void entry_head_null_print(char message[]);
entry* find_entry(char **com_check);
value* arithmetic_functions();


/*Node structs*/
struct value {
  value* prev;
  value* next;
  int value;
  int value_index;
};

struct entry {
  entry* prev;
  entry* next;
  value* values;
  value* value_head;
  char key[MAX_KEY_LENGTH];
};

struct snapshot {
  snapshot* prev;
  snapshot* next;
  entry* entries;
  int id;
};
#endif
