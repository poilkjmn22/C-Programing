/* 
 * @Author: fangqi
 * @Date: 2021-11-13 22:54:49
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-13 22:54:49
 * @Description: POJ-1979
 * O(n) = N * M[ * 4]
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>

#define MAX_N 20
#define MAX_M 20
#define BLACK '.'
#define RED '#'
#define START '@'
#define WALKED '*'

struct tile {
  int N;
  int M;
  char tiles[MAX_N][MAX_M + 1];
  int reachableCount;
};

using namespace std;

void solve(tile *);
int * findStart(tile);
void dfs(int, int, tile *);
tile * loadSampleInputs();
int stringToInt(string);
void printTile(tile);

int direction[4][2] = {
  {0, -1},
  {1, 0},
  {0, 1},
  {-1, 0}
};

int tileCount = 0;

int main() {
  tile *tileArr;
  tileArr = loadSampleInputs();
  for(int i = 0; i < tileCount; i++) {
    printTile(tileArr[i]);
    solve(&tileArr[i]);
  }

  return 0;
}

void dfs(int i, int j, tile * t) {
  t->tiles[i][j] = WALKED;
  t->reachableCount += 1;

  for(int d = 0;d < 4; d++) {
    int dx = i + direction[d][0];
    int dy = j + direction[d][1];

    if(0 <= dx && dx < t->N && 0 <= dy && dy < t->M && t->tiles[dx][dy] == BLACK) {
      dfs(dx, dy, t);
    }
  }
}

void solve(tile * t) {
  const int * start = findStart(*t);
  dfs(start[0], start[1], t);
  cout << "Output: " << endl;
  cout << t->reachableCount << endl << endl;
  return ;
}

tile * loadSampleInputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/red-and-black.txt");
  string s;
  regex patternNum("(\\d+)[\\s\\t]+(\\d+)");
  match_results<string::const_iterator> result;
  tile * tileTmp;
  int N = -1;
  tile *tiles = new tile[10000];
  while(getline(fin, s)) {
    if (N >= 0 && N < ( *tileTmp ).N) {
      char buf[tileTmp->M];
      strcpy(buf, s.c_str());
      /* tileTmp.tiles[N] = buf; */
      for(int k =0; k < tileTmp->M; k++) {
        ( *tileTmp ).tiles[N][k] = buf[k];
      }
      if(N++ == (tileTmp->N - 1)) {
        tiles[tileCount++] = *tileTmp;
        delete tileTmp;
      }
    }
    if(regex_match(s, result, patternNum)) {
      tileTmp = new tile;
      tileTmp->N = stringToInt(result[2]);
      tileTmp->M = stringToInt(result[1]);
      tileTmp->reachableCount  = 0;
      N = 0;
    }
  }
  fin.close();
  return tiles;
}

int stringToInt(string s) {
  stringstream sm;
  sm << s;
  int m;
  sm >> m;
  return m;
}

int * findStart(tile t) {
  int * start = new int[2];

  for(int i =0; i< t.N; i++) {
    for(int j =0; j< t.M; j++) {
      if(t.tiles[i][j] == START) {
        start[0] = i;
        start[1] = j;
      }
    }
  }
  return start;
}

void printTile(tile t) {
  cout << "Input: " << endl;
  cout << t.N << "," << t.M << endl;
  for(int i =0; i< t.N; i++) {
    for(int j =0; j< t.M; j++) {
      cout << t.tiles[i][j];
    }
    cout << endl;
  }
  return ;
}
