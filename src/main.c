#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define regsize char
#define flagsize short
#define bufsize long long int
#define MEMSIZE 8192
#define PROGSIZE MEMSIZE

#include "vm.h"

int main(int argc, char** argv) {
  char src[PROGSIZE];
  FILE* fl = fopen(argv[1], "r");
  fread(src, PROGSIZE, 1, fl);
  int exitCode = vm(src);

  return exitCode;
}

