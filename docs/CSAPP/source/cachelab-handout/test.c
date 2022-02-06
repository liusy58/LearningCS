#define  _GNU_SOURCE
#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

int main(){
    char* m = " M 10345438,8\n";
    char operation;
    uintptr_t address;
    int size;
    sscanf(m," %c %lx,%d",&operation,&address,&size);
    printf("parse result :  %c -- %lx %d\n",operation,address,size);
}