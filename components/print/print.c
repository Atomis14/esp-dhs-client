#include <stdio.h>
#include "print.h"

void print_char(char *string, char separator) {
  for(char *i = string; *i != '\0'; i++) {
    printf("%c", *i);
  }
  printf("\n");
}

void print_uint8_t(uint8_t *string, int length, char separator) {
  printf("%x", string[0]);
  for (int i = 1; i < length; i++)
  {
    printf("%c%x", separator, string[i]);
  }
  printf("\n");
}