#include <stdio.h>
#include "print.h"

void print_char(char *string, char separator) {
  for(char *i = string; *i != '\0'; i++) {
    printf("%c", *i);
  }
  printf("\n");
}

void print_uint8_t(uint8_t *string, int length, char separator) {
  for (int i = 0; i < length; i++)
  {
    printf("%x%c", string[i], separator);
  }
  printf("\n");
}