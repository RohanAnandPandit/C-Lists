#include <stdbool.h>

typedef struct intlist {
  int max_size;
  int length;
  int *items;
} ArrayIntList;

typedef int (*unaryF)(int);
typedef int (*binaryF)(int, int);
typedef bool (*predF) (int);

#ifndef ARRAYINTLIST_H
#define ARRAYINTLIST_H

ArrayIntList *new_intlist(void);
ArrayIntList *intlist_from_array(int *arr, int length);
ArrayIntList *clone(ArrayIntList *list);
int length(ArrayIntList *list);
void freeIntList(ArrayIntList *list);
void append(ArrayIntList *list, int item);
int get(ArrayIntList *list, int index);
void insert(ArrayIntList *list, int item, int index);
int peek(ArrayIntList *list);
int pop(ArrayIntList *list);
void delete(ArrayIntList *list, int index);
void set(ArrayIntList *list, int index, int item);
void print_list(ArrayIntList *list);
int contains(ArrayIntList *list, int x);
int occurrences(ArrayIntList *list, int x);
int compare(ArrayIntList *this, ArrayIntList *that);
int equals(ArrayIntList *this, ArrayIntList *that);
int sum(ArrayIntList *list);
void map(unaryF func, ArrayIntList *list);
ArrayIntList *zipWith(binaryF func, ArrayIntList *as, ArrayIntList *bs);
int minimum(ArrayIntList *list);
int maximum(ArrayIntList *list);
int foldl(binaryF func, int x, ArrayIntList *list);
int foldl1(binaryF func, ArrayIntList *list);
int foldr(binaryF func, int x, ArrayIntList *list);
int foldr1(binaryF func, ArrayIntList *list);
ArrayIntList *scanl(binaryF func, int x, ArrayIntList *list);
ArrayIntList *scanl1(binaryF func, ArrayIntList *list);
ArrayIntList *scanr(binaryF func, int x, ArrayIntList *list);
ArrayIntList *scanr1(binaryF func, ArrayIntList *list);
void reverse(ArrayIntList *list);
ArrayIntList *concat(ArrayIntList *xs, ArrayIntList *ys);
void intersperse(int x, ArrayIntList *xs);
ArrayIntList *repeat(int x, int n);
ArrayIntList *slice(ArrayIntList *list, int start, int end);
ArrayIntList *take(int n, ArrayIntList *list);
ArrayIntList *drop(int n, ArrayIntList *list);
ArrayIntList *filter(predF func, ArrayIntList *xs);
ArrayIntList *takeWhile(predF func, ArrayIntList *xs);
ArrayIntList *dropWhile(predF func, ArrayIntList *xs);
ArrayIntList *iterate(int n, unaryF func, int x);
#endif

