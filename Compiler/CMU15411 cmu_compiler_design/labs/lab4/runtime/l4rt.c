#include "l4rt.h"

int printchar (int c) {
  fputc(c, stderr);
  return c;
}

int printint (int n) {
  fprintf(stderr, "%d", n);
}

int printhex (int n) {
  fprintf(stderr, "0x%X", n);
}

int printbool (int b) {
  fprintf(stderr, b ? "true" : "false");
}

/* The main function, which calls _l4_main */
int main() {
  printf("%d\n", _l4_main());
  exit(0);
}
