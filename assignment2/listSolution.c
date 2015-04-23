#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

struct list_head {
    int data;
    struct list_head *prev, *next;
};

/** Initialises "head" to be the head of a circular linked list */
void list_init(struct list_head *head) {
    head->next = head;
    head->prev = head;
}

/** Inserts a new entry after "head" */
void list_add(struct list_head *new, struct list_head *head) {
    new->prev = head;
    new->next = head->next;

    new->next->prev = new;
    new->prev->next = new;
}

/** Inserts a new entry before "head" */
void list_add_tail(struct list_head *new, struct list_head *head) {
    new->prev = head->prev;
    new->next = head;

    new->prev->next = new;
    new->next->prev = new;
}

/** Removes "entry" from the list */
void list_del(struct list_head *entry) {
    entry->prev->next = entry->next;
    entry->next->prev = entry->prev;

    list_init(entry); // change entry into an empty list for convenience
}

/** Checks if the list is empty */
bool list_empty(struct list_head *head) {
    return head->prev == head;
}

int main(void) {
    struct list_head list;
    list_init(&list);

    int x;
    while (scanf("%d", &x) == 1) {
        struct list_head *tail = malloc(sizeof(struct list_head));
        tail->data = x;
        list_add_tail(tail, &list);
    }

    // traverse the list backwards
    for (struct list_head *elem = list.prev; elem != &list; ) {
        printf("%d\n", elem->data);

        // save the previous element
        struct list_head *prev = elem->prev;

        // remove the element and free
        list_del(elem);
        free(elem);

        elem = prev;
    }

    // just to make sure we aren't crazy
    assert(list_empty(&list));

    return 0;
}
