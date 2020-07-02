
#include <stdbool.h>



typedef struct intnode {
  int value;
  struct intnode *next;
  struct intnode *prev;
} IntNode;

typedef struct linked_intlist {
  IntNode *head;
  IntNode *tail;
  int length;
} LinkedIntList;


typedef int (*unaryF)(int);
typedef int (*binaryF)(int, int);
typedef bool (*predF) (int);

#ifndef LINKEDINTLIST_H
#define LINKEDINTLIST_H

LinkedIntList *linkedlistintlist(void);
LinkedIntList *linkedlist_from_array(int *arr, int length);
int len(LinkedIntList *list);
void freeList(LinkedIntList *list);
void appendTail(LinkedIntList *list, int item);
int linkedlistget(LinkedIntList *list, int index);
void linkedlistinsert(LinkedIntList *list, int item, int index);
int linkedlistpeek(LinkedIntList *list);
int linkedlistpop(LinkedIntList *list);
void linkedlistdelete(LinkedIntList *list, int index);
void linkedlistset(LinkedIntList *list, int index, int item);
void print_linkedlist(LinkedIntList *list);
int linkedlistcontains(LinkedIntList *list, int x);
int linkedlist_occurrences(LinkedIntList *list, int x);
int compare_linkedlists(LinkedIntList *this, LinkedIntList *that);
int equal_linkedlists(LinkedIntList *this, LinkedIntList *that);
int sum_linkedlist(LinkedIntList *list);
void map_linkedlist(int (*func) (int), LinkedIntList *list);
LinkedIntList *zipWith_linkedlists(binaryF func, LinkedIntList *as, LinkedIntList *bs);
int linkedlist_minimum(LinkedIntList *list);
int linkedlist_maximum(LinkedIntList *list);
int foldl_linkedlist(binaryF func, int x, LinkedIntList *list);
int foldl1_linkedlist(binaryF func, LinkedIntList *list);
int foldr_linkedlist(binaryF func, int x, LinkedIntList *list);
int foldr1_linkedlist(binaryF func, LinkedIntList *list);
void reverse_linkedlist(LinkedIntList *list);
/*
LinkedIntList *scanl(binaryF func, int x, LinkedIntList *list);
LinkedIntList *scanl1(binaryF func, LinkedIntList *list);
LinkedIntList *scanr(binaryF func, int x, LinkedIntList *list);
LinkedIntList *scanr1(binaryF func, LinkedIntList *list);
*/
LinkedIntList *concat_linkedlists(LinkedIntList *xs, LinkedIntList *ys);
/*
void intersperse(int x, LinkedIntList *xs);
LinkedIntList *repeat(int x, int n);
LinkedIntList *slice(LinkedIntList *list, int start, int end);
LinkedIntList *take(int n, LinkedIntList *list);
LinkedIntList *drop(int n, LinkedIntList *list);
LinkedIntList *filter(predF func, LinkedIntList *xs);
LinkedIntList *takeWhile(predF func, LinkedIntList *xs);
LinkedIntList *dropWhile(predF func, LinkedIntList *xs);
LinkedIntList *iterate(int n, unaryF func, int x);
*/
#endif
