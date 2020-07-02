#include "array_intlist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

/* Returns a pointer to a new ArrayIntList
 */
ArrayIntList *new_intlist(void) {
  ArrayIntList *list = malloc(sizeof(ArrayIntList));
  list->max_size = 10;
  list->items = malloc(list->max_size * sizeof(int));
  list->length = 0;
  return list;
}

void adjustLength(ArrayIntList *list) {
  list->max_size = list->length;
  list->max_size *= 1.5;
  list->items = realloc(list->items, list->max_size * sizeof(int));
  assert(list->items);
}

/* Creates a new ArrayIntList with the values in the given array
 */
ArrayIntList *intlist_from_array(int *arr, int length) {
  assert(arr);
  assert(length >= 0);

  ArrayIntList *list = new_intlist();
  list->length = length;
  adjustLength(list);
  for (int i = 0; i < length; i++) {
    list->items[i] = arr[i];
  }
  return list;
}

/* Returns pointer to a Int-List with exact same values
 */
ArrayIntList *clone(ArrayIntList *list) {
  return intlist_from_array(list->items, list->length);
}

/* Frees memory allocated in ArrayIntList
 */
void freeIntList(ArrayIntList *list) {
  free(list->items);
  free(list);
}

/*Returns length of the list
 */
int length(ArrayIntList *list) {
  assert(list);
  return list->length;
}

void append(ArrayIntList *list, int item) {
  assert(list != NULL);
  list->length++;
  adjustLength(list);
  list->items[list->length - 1] = item;
}

int get(ArrayIntList *list, int index) {
  assert(list != NULL);

  if (index < 0 || index >= list->length) {
    perror("Index out of bounds");
    return -1;
  }
  return list->items[index];
}

void insert(ArrayIntList *list, int item, int index) {
  assert(list != NULL);
  assert(index >= 0 && index < list->length);
  append(list, 0);
  for (int i = list->length - 1; i > index; i--) {
    list->items[i] = list->items[i - 1];
  }
  list->items[index] = item;
}

int peek(ArrayIntList *list) {
  if (list->length == 0) {
    perror("peek: empty list");
    return -1;
  }
  return list->items[list->length - 1];
}

int pop(ArrayIntList *list) {
  if (list->length == 0) {
    perror("pop: underflow");
    return -1;
  }
  int value = list->items[list->length - 1];
  list->length--;
  return value;
}

void delete(ArrayIntList *list, int index) {
  assert(list);
  for (int i = index; i < list->length - 1; i++) {
    list->items[i] = list->items[i + 1];
  }
  list->length--;
}

void set(ArrayIntList *list, int index, int item) {
  assert(list);
  assert(index >= 0 && index < list->length);
  list->items[index] = item;

}

void print_list(ArrayIntList *list) {
  printf("[");
  for (int i = 0; i < list->length; i++) {
    printf("%d", list->items[i]);
    if (i < list->length - 1) {
      printf(", ");
    }
  }
  printf("]");
}

int contains(ArrayIntList *list, int x) {
  for (int i = 0; i < list->length; i++) {
    if (x == list->items[i])
      return i + 1;
   }
  return 0;
}

int occurrences(ArrayIntList *list, int x) {
  int sum = 0;
  for (int i = 0; i < list->length; i++) {
    if (x == list->items[i])
      sum++;
  }
  return sum;
}

// Returns the first non-zero difference between corressponding elements in both arrays
int compare(ArrayIntList *this, ArrayIntList *that) {
  assert(this); assert(that);
  int diff, len = min(this->length, that->length);
  for (int i = 0; i < len; i++) {
    diff = this->items[i] - that->items[i];
    if (diff != 0)
      return diff;
  }
  return 0;
}

int equals(ArrayIntList *this, ArrayIntList *that) {
  return !compare(this, that);
}

int sum(ArrayIntList *list) {
  assert(list);
  int sum = 0;
  for (int i = 0; i < list->length; i++)
    sum += list->items[i];
  return sum;
}

void map(unaryF func, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items;
  for (int i = 0; i < len; i++)
    items[i] = func(items[i]);
}


ArrayIntList *zipWith(binaryF func, ArrayIntList *as, ArrayIntList *bs) {
  int len = min(as->length, bs->length), *itemsA = as->items, *itemsB = bs->items;
  int *zs = malloc(len * sizeof(int));
  for (int i = 0; i < len; i++)
    zs[i] = func(itemsA[i], itemsB[i]);
  return intlist_from_array(zs, len);
}


int minimum(ArrayIntList *list) {
  int l = length(list);
  assert(l != 0);
  int minimum = list->items[0];
  for (int i = 1; i < l; i++) {
    minimum = min(minimum, list->items[i]);
  }
  return minimum;
}

int maximum(ArrayIntList *list) {
  assert(list);
  int len = list->length, *items = list->items;
  assert(len > 0);
  int maximum = items[0];
  for (int i = 1; i < len; i++) {
    maximum = max(maximum, items[i]);
  }
  return maximum;
}

int foldl(binaryF func, int x, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items;
  assert(len > 0);
  int result = x;
  for (int i = 0; i < len; i++)
    result = func(result, items[i]);
  return result;
}

int foldl1(binaryF func, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items;
  assert(len > 1);
  int result = items[0];
  for (int i = 1; i < len; i++)
    result = func(result, items[i]);
  return result;
}

int foldr(binaryF func, int x, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items, result = x;
  for (int i = len - 1; i >= 0; i--)
    result = func(items[i], result);
  return result;
}

int foldr1(binaryF func, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items,  result = items[len - 1];
  for (int i = len - 2; i >= 0; i--)
    result = func(items[i], result);
  return result;
}

ArrayIntList *scanl(binaryF func, int x, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items, l = len + 1, ys[l];
  int result = ys[0] = x;
  for (int i = 1; i < l; i++) {
    result = func(result, items[i - 1]);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}

ArrayIntList *scanl1(binaryF func, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items, ys[len];
  int result = items[0];
  for (int i = 1; i < len; i++) {
    result = func(result, items[i]);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}

ArrayIntList *scanr(binaryF func, int x, ArrayIntList *xs) {
  assert(xs); assert(func);
  int len = xs->length, *items = xs->items, ys[len + 1];
  int result = ys[len] = x;
  for (int i = len - 1; i >= 0; i--) {
    result = func(items[i], result);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}

ArrayIntList *scanr1(binaryF func, ArrayIntList *xs) {
  assert(xs); assert(func);
  int len = xs->length, *items = xs->items, ys[len];
  int result = ys[len - 1] = items[len - 1];
  for (int i = len - 2; i >= 0; i--) {
    result = func(items[i], result);
    ys[i] = result;
  }
  return intlist_from_array(ys, len);
}

void reverse(ArrayIntList *list) {
  assert(list);
  int len = list->length, *items = list->items, temp;
  assert(len >= 0);
  for (int i = 0, j = len - 1; i < j; i++) {
    temp = list->items[i];
    items[i] = items[j];
    items[j--] = temp;
  }
}

ArrayIntList *concat(ArrayIntList *xs, ArrayIntList *ys) {
  int l1 = length(xs), l2 = length(ys);
  int *itemsY = ys->items, *itemsX = xs->items;
  int *cs = calloc(l1 + l2, sizeof(int));
  for (int i = 0; i < l1; i++)
    cs[i] = itemsX[i];
  for (int i = 0; i < l2; i++)
    cs[i + l1] = itemsY[i];
  return intlist_from_array(cs, l1 + l2);
}

void intersperse(int x, ArrayIntList *xs) {
  int len = xs->length;
  xs->length = 2 * len - 1;
  adjustLength(xs);
  int *items = xs->items;
  for (int i = len - 1; i > 0; i--) {
    items[2 * i] = items[i];
    items[2 * i - 1] = x;
  }
}

ArrayIntList *repeat(int x, int n) {
  int xs[n];
  for (int i = 0; i < n; i++)
    xs[i] = x;
  return intlist_from_array(xs, n);
}

ArrayIntList *slice(ArrayIntList *list, int start, int end) {
  assert(list);
  int len = min(list->length, end), *items = list->items;
  int slice[len - start];
  for (int i = 0; start < len; i++) {
    slice[i] = items[start];
    start++;
  }
  return intlist_from_array(slice, len);
}

ArrayIntList *take(int n, ArrayIntList *list) {
  return slice(list, 0, n);
}

ArrayIntList *drop(int n, ArrayIntList *list) {
  return slice(list, n + 1, list->length);
}


ArrayIntList *filter(predF func, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items;
  ArrayIntList *list = new_intlist();
  for (int i = 0; i < len; i++) {
    if (func(items[i]))
      append(list, items[i]);
  }
  return list;
}

ArrayIntList *takeWhile(predF func, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items, i;
  for (i = 0; i < len && func(items[i]); i++);
  return take(i, xs);
}

ArrayIntList *dropWhile(predF func, ArrayIntList *xs) {
  int len = xs->length, *items = xs->items, i;
  for (i = 0; i < len && func(items[i]); i++);
  return drop(i, xs);
}

ArrayIntList *iterate(int n, unaryF func, int x) {
  int xs[n], result = x;
  for (int i = 0; i < n; i++) {
    xs[i] = result;
    result = func(result);
  }
  return intlist_from_array(xs, n);
}


