#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "darray.h"

Darray darray_create(size_t element_size, size_t capacity) {
  Darray array = {.element_size = element_size,
                  .count = 0,
                  .capacity = capacity,
                  .data = malloc(element_size * capacity)};

  assert(array.data);

  return array;
}

void *darray_get(Darray *darray, size_t index) {
  assert(darray);
  assert(index >= 0 && index < darray->count);

  return darray->data + darray->element_size * index;
}

void darray_set(Darray *darray, size_t index, void *element) {
  assert(darray);
  assert(index >= 0 && index < darray->count);
  assert(element);

  memcpy(darray->data + darray->element_size * index, element,
         darray->element_size);
}

void darray_push(Darray *darray, void *element) {
  assert(darray);
  assert(element);

  if (darray->count == darray->capacity) {
    size_t new_capacity = darray->capacity * 2;
    darray->data = realloc(darray->data, new_capacity * darray->element_size);

    assert(darray->data);

    darray->capacity = new_capacity;
  }

  memcpy(darray->data + darray->element_size * darray->count, element,
         darray->element_size);

  darray->count += 1;
}

void darray_foreach(Darray *darray,
                    void (*action)(void *element, size_t index)) {
  assert(darray);
  assert(action);

  for (size_t i = 0; i < darray->count; ++i) {
    action(darray->data + darray->element_size * i, i);
  }
}

void *darray_find(Darray *darray, void *key,
                  int (*cmp)(void *key, void *element)) {
  assert(darray);
  assert(key);
  assert(cmp);

  for (size_t i = 0; i < darray->count; ++i) {
    void *element = darray->data + darray->element_size * i;

    if (cmp(key, element) == 0) {
      return element;
    }
  }

  return NULL;
}

void darray_sort(Darray *darray, int (*cmp)(const void *left, const void *right)) {
  assert(darray);
  assert(cmp);

  qsort(darray->data, darray->count, darray->element_size, cmp);
}
