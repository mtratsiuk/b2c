#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct Darray {
  size_t element_size;
  size_t count;
  size_t capacity;
  void *data;
} Darray;

Darray darray_create(size_t element_size, size_t capacity);

void *darray_get(Darray *darray, size_t index);
void darray_set(Darray *darray, size_t index, void *element);
void darray_push(Darray *darray, void *element);
void darray_foreach(Darray *darray,
                    void (*action)(void *element, size_t index));
void *darray_find(Darray *darray, void *key,
                  int (*cmp)(void *key, void *element));
void darray_sort(Darray *darray,
                 int (*cmp)(const void *left, const void *right));

#endif
