#include <stdio.h>
#define MAX_N  100
#define MAX_M  100
#define LAKE  'W'

int N = 10;
int M = 12;
char field[MAX_N][MAX_M + 1] = {
  {LAKE, '.', '.', '.', '.', '.', '.', '.', '.', LAKE, LAKE, '.'},
  {'.', LAKE, LAKE, LAKE, '.', '.', '.', '.', '.', LAKE, LAKE, LAKE},
  {'.', '.', '.', '.', LAKE, LAKE, '.', '.', '.', LAKE, LAKE, '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', LAKE, LAKE, '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', LAKE, '.', '.'},
  {'.', '.', LAKE, '.', '.', '.', '.', '.', '.', LAKE, '.', '.'},
  {'.', LAKE, '.', LAKE, '.', '.', '.', '.', '.', LAKE, LAKE, '.'},
  {LAKE, '.', LAKE, '.', LAKE, '.', '.', '.', '.', '.', LAKE, '.'},
  {'.', LAKE, '.', LAKE, '.', '.', '.', '.', '.', '.', LAKE, '.'},
  {'.', '.', LAKE, '.', '.', '.', '.', '.', '.', '.', LAKE, '.'}
};

int main(void) {
  /* printf("%d", field[0][1] == LAKE); */
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      if(field[i][j] == LAKE) {
        printf("%c\n", field[i][j]);
      }
    }
  }
  return 0;
}
