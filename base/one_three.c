#include <stdio.h>

void two(void);

int main(void) {
  printf("starting now: \n");
  printf("one\n");
  two();
  printf("three\n");
  printf("done!\n");
  return 0;
}

void two(void) {
  printf("two\n");
}
