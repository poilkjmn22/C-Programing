/* O(N * M) [O(8 * N * M)] */

#include <cstdio>
#define MAX_N  100
#define MAX_M  100
#define LAKE  'W'

using namespace std;
void dfs();
void solve();

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

int main() {
  solve();
  return 0;
}

void dfs(int x, int y) {
  field[x][y] = '.';

  for(int dx = -1; dx <= 1; dx++) {
    for(int dy = -1; dy <= 1; dy++) {
      int nx = x + dx;
      int ny = y + dy;

      if(0 <= nx && nx < N && 0 <= ny && ny < M && field[nx][ny] == LAKE) {
        dfs(nx, ny);
      }
    }
  }
  return ;
}

void solve() {
  int res = 0;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      if(field[i][j] == LAKE) {
        dfs(i, j);
        res++;
      }
    }
  }
  
  printf("%d\n", res);
}
