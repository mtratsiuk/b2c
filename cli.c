#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "darray.h"

Cli cli_create(void *state) {
  assert(state);

  Darray entries = darray_create(sizeof(CliEntry), 8);
  Cli cli = {.menu_entries = entries, .state = state};

  return cli;
}

CliEntry cli_create_entry(KeyCode code, char *prompt,
                          void (*action)(void *state)) {
  assert(action);
  assert(prompt);

  CliEntry entry = {.code = code, .prompt = prompt, .action = action};

  return entry;
}

void cli_add_entry(Cli *cli, CliEntry entry) {
  assert(cli);

  darray_push(&cli->menu_entries, &entry);
}

void print_entry_callback(void *entry, size_t index) {
  CliEntry *cli_entry = entry;

  printf("%d) %s\n", cli_entry->code - '0', cli_entry->prompt);
}

int find_entry_callback(void *key, void *element) {
  return *(KeyCode *)key - ((CliEntry *)element)->code;
}

void cli_start(Cli *cli) {
  assert(cli);

  int key_code = KeyCode_Enter;

  while (1) {
    if (key_code == KeyCode_Enter) {
      darray_foreach(&cli->menu_entries, &print_entry_callback);
    }

    key_code = getchar();

    if (key_code == KeyCode_Esc) {
      break;
    }

    CliEntry *entry =
        darray_find(&cli->menu_entries, &key_code, &find_entry_callback);

    if (entry) {
      entry->action(cli->state);
    }

    puts("\n");
  }
}

char *cli_read_str(char *prompt) {
  puts(prompt);

  size_t entry_size = sizeof(char);
  size_t capacity = 16;
  char *str = malloc(entry_size * capacity);
  size_t size = 0;
  char ch = getchar();

  if (ch == KeyCode_Enter) {
    ch = getchar();
  }

  while (1) {
    if (ch == EOF || ch == KeyCode_Enter) {
      break;
    }

    if (size == capacity) {
      capacity *= 2;
      str = realloc(str, entry_size * capacity);
    }

    str[size] = ch;
    size += 1;

    ch = getchar();
  }

  return realloc(str, entry_size * (strlen(str) + 1));
}
