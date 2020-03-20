#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "darray.h"

typedef struct Pupil {
  char *first_name;
  char *last_name;
  char *generic_name;
} Pupil;

typedef struct AppState {
  Darray *pupils;
} AppState;

void add_new_pupil_callback(void *state) {
  AppState *app_state = state;

  Pupil pupil = {.first_name = cli_read_str("Enter first name"),
                 .last_name = cli_read_str("Enter last name"),
                 .generic_name = cli_read_str("Enter generic name")};

  darray_push(app_state->pupils, &pupil);
}

void print_pupil_callback(void *element, size_t index) {
  Pupil *pupil = element;

  puts("\n/----------------------------");
  printf("| %ld | %s %s %s", index, pupil->first_name, pupil->last_name,
         pupil->generic_name);
  puts("\n\\----------------------------");
}

void print_pupils_callback(void *state) {
  AppState *app_state = state;

  darray_foreach(app_state->pupils, &print_pupil_callback);
}

int cmp_pupil_callback(const void *left, const void *right) {
  return strcmp(((Pupil *)left)->first_name, ((Pupil *)right)->first_name);
}

void sort_pupils_callback(void *state) {
  AppState *app_state = state;

  darray_sort(app_state->pupils, &cmp_pupil_callback);
}

int main() {
  Darray pupils = darray_create(sizeof(Pupil), 16);
  AppState state = {.pupils = &pupils};

  Cli cli = cli_create(&state);
  cli_add_entry(&cli, cli_create_entry(KeyCode_One, "Add new entry",
                                       &add_new_pupil_callback));
  cli_add_entry(&cli, cli_create_entry(KeyCode_Two, "Print all entries",
                                       &print_pupils_callback));
  cli_add_entry(&cli, cli_create_entry(KeyCode_Three, "Sort entries",
                                       &sort_pupils_callback));

  cli_start(&cli);

  return 0;
}
