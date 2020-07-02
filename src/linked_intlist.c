#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "linked_intlist.h"

IntNode *create_node(void) {
  IntNode *node = malloc(sizeof(IntNode));
  node->prev = node->next = NULL;
  return node;
}

void setNode(IntNode *node, int value, IntNode *prev, IntNode *next) {
  node->value = value;
  node->prev = prev; node->next = next;
}

void free_node(IntNode *node) {
  free_node(node->next);
  free(node);
}

IntNode *getNode(LinkedIntList *list, int index) {
  assert(list); IntNode *curr = list->head;
  for (int i = 0; i < index && curr; i++)
    curr = curr->next;
  assert(curr);
  return curr;
}

void free_linkedlist(LinkedIntList *list) {
  free_node(list->head);
  free(list);
}

// Returns a pointer to a new LinkedIntList

LinkedIntList *linked_intlist(void) {
  LinkedIntList *list = malloc(sizeof(LinkedIntList));
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
  return list;
}

LinkedIntList *empty_list(int n) {
  assert(n >= 0);
  LinkedIntList *list = linked_intlist();
  list->head = create_node();
  IntNode *prev = NULL, *curr = list->head, *next = create_node();

  for (int i = 0; i < n; i++) {
    curr->prev = prev;
    curr->next = next;

    prev = curr;
    curr = next;
    next = create_node();
  }
  return list;
}

// Creates a new LinkedIntList with the values in the given array
LinkedIntList *linkedintlist_array(int *arr, int length) {
  assert(arr); assert(length >= 0);
  LinkedIntList *list = empty_list(length);
  int i = 0;
  for (IntNode *curr = list->head; curr; curr = curr->next) {
    curr->value = arr[i]; i++;
  }
  return list;
}

//Returns length of the list
int size(LinkedIntList *list) {
  assert(list);
  return list->length;
}

void appendHead(LinkedIntList *list, int item) {
  assert(list);
  IntNode *node = create_node();
  setNode(node, item, NULL, list->head);
  if (list->tail == NULL)
    list->tail = list->head;
  if (list->head != NULL)
    list->head->prev = node;
  list->head = node;
  list->length++;
}


void appendTail(LinkedIntList *list, int item) {
  assert(list);
  IntNode *node = create_node();
  setNode(node, item, list->tail, NULL);
  if (list->head == NULL)
    list->head = list->tail;
  if (list->tail != NULL)
    list->tail->next = node;
  list->tail = node;
  list->length++;
}

int linkedlist_get(LinkedIntList *list, int index) {
  assert(list); assert(index >= 0 && index < list->length);
  IntNode *node = getNode(list, index);
  return node->value;
}

void linkedlist_insert(LinkedIntList *list, int item, int index) {
  assert(list); assert(index >= 0 && index < list->length);
  IntNode *node = create_node();
  IntNode *curr = getNode(list, index);
  curr->prev->next = node;
  setNode(node, item, curr->prev, curr);
  curr->prev = node;
  list->length++;
}

int linkedlist_peek(LinkedIntList *list) {
  return list->tail->value;
}

int linkedlist_pop(LinkedIntList *list) {
  assert(list->length > 0);
  int value = list->tail->value;
  list->tail = list->tail->prev;
  list->tail->next = NULL;
  return value;
}

void linkedlist_delete(LinkedIntList *list, int index) {
  IntNode *curr = getNode(list, index);
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  list->length--;
}

void linkedlist_set(LinkedIntList *list, int index, int item) {
  assert(list);
  IntNode *curr = getNode(list, index);
  curr->value = item;
}

void print_linkedlist(LinkedIntList *list) {
  printf("[");
  IntNode *curr = list->head;
  for (int i = 0; curr; i++) {
    printf("%d", curr->value);
    if (i < list->length - 1) {
      printf(", ");
    }
  }
  printf("]");
}


int linkelist_contains(LinkedIntList *list, int x) {
  IntNode *curr = list->head;
  for (int i = 0; curr; i++) {
    if (x == curr->value)
      return i + 1;
    curr = curr->next;
  }
  return 0;
}

int linkedlist_occurrences(LinkedIntList *list, int x) {
  int sum = 0;
  for (IntNode *curr = list->head; curr; curr = curr->next) {
    if (x == curr->value)
      sum++;
  }
  return sum;
}

 // Returns the first non-zero between corressponding elements in both arrays

int compare_linkedlists(LinkedIntList *this, LinkedIntList *that) {
  assert(this); assert(that);
  int diff;
  IntNode *node1 = this->head, *node2 = that->head;
  for (; node1 && node2;) {
    diff = node1->value - node2->value;
    if (!diff)
      return diff;
    node1 = node1->next; node2 = node2->next;
  }
  if (node1 && !node2)
    return 1;
  if (node2 && !node1)
    return -1;
  return 0;
}

int equal_linkedlists(LinkedIntList *this, LinkedIntList *that) {
  return !compare_linkedlists(this, that);
}

int sum_linkedlist(LinkedIntList *list) {
  assert(list);
  int sum = 0;
  for (IntNode *curr = list->head; curr; curr = curr->next)
    sum += curr->value;
  return sum;
}


void map_linkedlist(unaryF func, LinkedIntList *xs) {
  assert(xs); assert(func);
  for (IntNode *curr = xs->head; curr; curr = curr->next)
    curr->value = func(curr->value);
}


LinkedIntList *zipWith_linkedlists(binaryF func, LinkedIntList *as, LinkedIntList *bs) {
  LinkedIntList *zs = empty_list(as->length < bs->length ? as->length : bs->length);
  IntNode *nodeA = as->head, *nodeB = bs->head, *nodeZ = zs->head;
  while (nodeA && nodeB) {
    nodeZ->value = func(nodeA->value, nodeB->value);
    nodeA = nodeA->next;
    nodeB = nodeA->next;
    nodeZ = nodeZ->next;
  }
  return zs;
}


int linkedlist_minimum(LinkedIntList *list) {
  assert(list); assert(list->head);
  IntNode *curr = list->head;
  int minimum = curr->value;
  for (; curr; curr = curr->next) {
    minimum = minimum < curr->value ? minimum : curr->value;
  }
  return minimum;
}

int linkedlist_maximum(LinkedIntList *list) {
  assert(list); assert(list->head);
  IntNode *curr = list->head;
  int maximum = curr->value;
  for (; curr; curr = curr->next) {
    maximum = maximum > curr->value ? maximum : curr->value;
  }
  return maximum;
}


int foldl_linkedlist(binaryF func, int x, LinkedIntList *xs) {
  assert(xs);
  int result = x;
  for (IntNode *curr = xs->head; curr; curr = curr->next)
    result = func(result, curr->value);
  return result;
}

int foldl1_linkedlist(binaryF func, LinkedIntList *xs) {
  assert(func); assert(xs); assert(xs->head);
  int result = xs->head->value;
  for (IntNode *curr = xs->head->next; curr; curr = curr->next)
    result = func(result, curr->value);
  return result;
}

int foldr_linkedlist(binaryF func, int x, LinkedIntList *xs) {
  assert(func); assert(xs);
  int result = x;
  for (IntNode *curr = xs->tail; curr; curr = curr->prev)
    result = func(curr->value, result);
  return result;
}

int foldr1_linkedlist(binaryF func, LinkedIntList *xs) {
  assert(func); assert(xs); assert(xs->tail);
  int result = xs->tail->value;
  for (IntNode *curr = xs->tail->prev; curr; curr = curr->prev)
    result = func(curr->value, result);
  return result;
}
/*
LinkedIntList *scanl(binaryF func, int x, LinkedIntList *xs) {
  int len = xs->length, *items = xs->items, l = len + 1, ys[l];
  int result = ys[0] = x;
  for (int i = 1; i < l; i++) {
    result = func(result, items[i - 1]);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}

LinkedIntList *scanl1(binaryF func, LinkedIntList *xs) {
  int len = xs->length, *items = xs->items, ys[len];
  int result = items[0];
  for (int i = 1; i < len; i++) {
    result = func(result, items[i]);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}

LinkedIntList *scanr(binaryF func, int x, LinkedIntList *xs) {
  assert(xs); assert(func);
  int len = xs->length, *items = xs->items, ys[len + 1];
  int result = ys[len] = x;
  for (int i = len - 1; i >= 0; i--) {
    result = func(items[i], result);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}

LinkedIntList *scanr1(binaryF func, LinkedIntList *xs) {
  assert(xs); assert(func);
  int len = xs->length, *items = xs->items, ys[len];
  int result = ys[len - 1] = items[len - 1];
  for (int i = len - 2; i >= 0; i--) {
    result = func(items[i], result);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}
*/

void reverse_linkedlist(LinkedIntList *list) {
  assert(list);
  IntNode *next;
  for (IntNode *curr = list->head; curr;  curr = next) {
    next = curr->next;
    curr->next = curr->prev;
    curr->prev = next;
  }
  next = list->head;
  list->head = list->tail;
  list->tail = next;
}

LinkedIntList *concat_linkedlists(LinkedIntList *xs, LinkedIntList *ys) {
  assert(xs); assert(ys);
  LinkedIntList *cs = empty_list(xs->length + ys->length);
  IntNode *curr = cs->head;
  for (IntNode *nodeX = xs->head; nodeX; nodeX = nodeX->next) {
    curr->value = nodeX->value;
    curr = curr->next;
  }
  for (IntNode *nodeY = ys->head; nodeY; nodeY = nodeY->next) {
    curr->value = nodeY->value;
    curr = curr->next;
  }
  return cs;
}

/*
void intersperse(int x, LinkedIntList *xs) {
  int len = xs->length;
  xs->length = 2 * len - 1;
  adjustSize(xs);
  int *items = xs->items;
  for (int i = len - 1; i > 0; i--) {
    items[2 * i] = items[i];
    items[2 * i - 1] = x;
  }
}

LinkedIntList *repeat(int x, int n) {
  int xs[n];
  for (int i = 0; i < n; i++)
    xs[i] = x;
  return intlist_from_array(xs, n);
}

LinkedIntList *slice(LinkedIntList *list, int start, int end) {
  int len = min(list->length, end), *items = list->items;
  int slice[len - start];
  for (int i = 0; start < len; i++) {
    slice[i] = items[i];
    start++;
  }
  return intlist_from_array(slice, len);
}

LinkedIntList *take(int n, LinkedIntList *list) {
xx  return slice(list, 0, n);
}

LinkedIntList *drop(int n, LinkedIntList *list) {
  return slice(list, n + 1, list->length);
}


LinkedIntList *filter(predF func, LinkedIntList *xs) {
  int len = xs->length, *items = xs->items;
  LinkedIntList *list = new_intlist();
  for (int i = 0; i < len; i++) {
    if (func(items[i]))
      append(list, items[i]);
  }
  return list;
}

LinkedIntList *takeWhile(predF func, LinkedIntList *xs) {
  int len = xs->length, *items = xs->items, i;
  for (i = 0; i < len && func(items[i]); i++);
  return take(i, xs);
}

LinkedIntList *dropWhile(predF func, LinkedIntList *xs) {
  int len = xs->length, *items = xs->items, i;
  for (i = 0; i < len && func(items[i]); i++);
  return drop(i, xs);
}

LinkedIntList *iterate(int n, unaryF func, int x) {
  int xs[n], result = x;
  for (int i = 0; i < n; i++) {
    xs[i] = result;
    result = func(result);
  }
  return intlist_from_array(xs, n);
}


*/
