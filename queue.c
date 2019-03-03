/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q) {
        q->tail = q->head = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        while (q->head) {
            list_ele_t *tmp = q->head;
            q->head = tmp->next;
            free(tmp->value);
            free(tmp);
        }
        /* Free queue structure */
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
*/
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;

    /* Return false if q is NULL or could not allocate space */
    if (!q || (newh = malloc(sizeof(list_ele_t))) == NULL)
        return false;

    /* Allocate space for the string and copy it */
    if ((newh->value = strdup(s)) == NULL) {
        free(newh);
        return false;
    }

    if (!q->head) { /* q is empty */
        /* Hence the tail is the new head */
        q->tail = newh;
    }
    newh->next = q->head;

    /* Update the new head */
    q->head = newh;
    /* Update the new size */
    ++q->size;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt;

    /* Return false if q is NULL or could not allocate space */
    if (!q || (newt = malloc(sizeof(list_ele_t))) == NULL)
        return false;

    /* Allocate space for the string and copy it */
    if ((newt->value = strdup(s)) == NULL) {
        free(newt);
        return false;
    }

    newt->next = NULL;

    if (!q->head) {
        /* Hence the head is the new tail */
        q->head = newt;
    } else {
        q->tail->next = newt;
    }

    /* Update the new tail */
    q->tail = newt;
    /* Undate the new size */
    ++q->size;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;

    if (!sp)
        return false;

    list_ele_t *head = q->head;
    strncpy(sp, head->value, bufsize - 1);
    sp[bufsize - 1] = '\0';

    /* update the new head.*/
    q->head = head->next;

    /* free the orign head.*/
    free(head->value);
    free(head);

    --q->size;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* we only need to deal with the queue having more than 2 elements */
    if (!q || q->size < 2)
        return;

    /* reverse the list */
    q->tail = q->head;

    list_ele_t *tmp, *fast = q->head->next;

    while (fast) {
        tmp = q->head;
        q->head = fast;
        fast = fast->next;
        q->head->next = tmp;
    }
    q->tail->next = NULL;
}
