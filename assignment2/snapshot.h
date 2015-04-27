#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#define MAX_KEY_LENGTH 16
#define MAX_LINE_LENGTH 1024
#define SEPARATOR " "

#define HELP "HELP\n"
#define BYE "BYE\n"
#define LIST_KEYS "LIST KEYS\n"
#define LIST_ENTRIES "LIST ENTRIES\n"
#define LIST_SNAPSHOTS "LIST SNAPSHOTS\n"
#define GET "GET"
#define DEL "DEL"
#define PURGE "PURGE"
#define SET "SET"
#define PUSH "PUSH"
#define APPEND "APPEND"
#define PICK "PICK"
#define PLUCK "PLUS"
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

value* value_init(int value_stored);
void value_insertAtHead(int value_stored);
void value_insertAtTail(int value_stored);

entry* entry_init(value **value_head);
void entry_insertAtHead(value **value_head);
void entry_insertAtTail(value **value_head);
/*once i've finished this linkedlist i will need to pass this a linked
list of values instead of nothing*/
void set(entry *entry_head, value *value_head);
void push(entry *list, value *value);
void append(entry *list, value *value);

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
  char key[MAX_KEY_LENGTH];
};

struct snapshot {
  snapshot* prev;
  snapshot* next;
  entry* entries;
  int id;
};
#endif
