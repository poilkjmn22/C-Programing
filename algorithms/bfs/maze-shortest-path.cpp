/* O(N * M) [O(4 * N * M)] */
using namespace std;

#include <cstdio>
#include <iostream>
#include <queue>
#define MAX_N  100
#define MAX_M  100

const int INF = 100000000;
typedef pair<int, int> P;

int N = 10;
int M = 10;
char maze[MAX_N][MAX_M + 1] = {
  {'#', 'S', '#', '#', '#', '#', '#', '#', '.', '#'},
  {'.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
  {'.', '#', '.', '#', '#', '.', '#', '#', '.', '#'},
  {'.', '#', '.', '.', '.', '.', '.', '.', '.', '.'},
  {'#', '#', '.', '#', '#', '.', '#', '#', '#', '#'},
  {'.', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
  {'.', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
  {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
  {'.', '#', '#', '#', '#', '.', '#', '#', '#', '.'},
  {'.', '.', '.', '.', '#', '.', '.', '.', 'G', '#'}
};
int sx = 0;
int sy = 1;
int gx = 9;
int gy = 8;

int d[MAX_N][MAX_M];
int dv[4][2] = {
  {1, 0},
  {0, 1},
  {-1, 0},
  {0, -1}
};

void solve();

int main() {
  solve();
  return 0;
}

int bfs() {
  queue<P> que;

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      d[i][j] = INF;
    }
  }

  que.push(P(sx, sy));
  d[sx][sy] = 0;

  while(que.size()) {
    P p = que.front();
    que.pop();

    if(p.first == gx && p.second == gy) {
      break;
    }

    for(int i = 0; i < 4; i++) {
      int nx = p.first + dv[i][0];
      int ny = p.second + dv[i][1];

      if(0 <= nx && nx < N && 0 <= ny && ny < M && maze[nx][ny] != '#' && d[nx][ny] == INF) {
        que.push(P(nx, ny));
        d[nx][ny] = d[p.first][p.second] + 1;
      }
    }

  }

  return d[gx][gy];
}

void solve() {
  int res = bfs();
  
  printf("%d\n", res);
}
