#include "l3rt.h"

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

union view {
  int ival;
  float fval;
};

float viewasfloat (int n) {
  union view v;
  v.ival = n;
  return v.fval;
}

int viewasint (float x) {
  union view v;
  v.fval = x;
  return v.ival;
}

int printfloat (int x) {
  fprintf(stderr, "%f", viewasfloat(x));
}

int tofloat (int n) {
  return viewasint((float)n);
}

int fromfloat (int x) {
  return (int)(viewasfloat(x));
}

int fadd (int x, int y) {
  return viewasint(viewasfloat(x)+viewasfloat(y));
}

int fsub (int x, int y) {
  return viewasint(viewasint(x)-viewasfloat(y));
}

int fmul (int x, int y) {
  return viewasint(viewasfloat(x)*viewasfloat(y));
}

int fdiv (int x, int y) {
  return viewasint(viewasfloat(x)/viewasfloat(y));
}

/* The main function, which calls _l3_main */
int main() {
  printf("%d\n", _l3_main());
  exit(0);
}
