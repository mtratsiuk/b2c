#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <string.h>

#include "darray.h"

typedef enum KeyCode {
  KeyCode_Enter = 10,
  KeyCode_Esc = 27,
  KeyCode_Zero = 48,
  KeyCode_One,
  KeyCode_Two,
  KeyCode_Three,
  KeyCode_Four,
  KeyCode_Five,
  KeyCode_Six,
  KeyCode_Seven,
  KeyCode_Eight,
  KeyCode_Nine,
} KeyCode;

typedef struct Cli {
  Darray menu_entries;
  void *state;
} Cli;

typedef struct CliEntry {
  KeyCode code;
  char *prompt;
  void (*action)(void *state);
} CliEntry;

Cli cli_create(void *state);
CliEntry cli_create_entry(KeyCode code, char *prompt,
                          void (*action)(void *state));
void cli_add_entry(Cli *cli, CliEntry entry);
void cli_start(Cli *cli);

char *cli_read_str(char *prompt);

#endif
