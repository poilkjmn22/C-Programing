/* 
 * @Author: fangqi
 * @Date: 2021-11-15 11:17:27
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-15 11:17:37
 * @Description: AOJ-0558
 * O(n) = N * M[ * 4 * 9]
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
#include <queue>
#include "utils.h"

using namespace std;

#define BARRIER 'X'
#define PASS '.'
#define START 'S'

typedef pair<int, int> P;

struct tile {
  int N;
  int M;
  int CheeseMax;
  char tiles[STRUCT_MAX_N][STRUCT_MAX_M + 1];
  int d[STRUCT_MAX_N][STRUCT_MAX_M];
  int power;
  int leastCostTime;
};

void solve(tile *);
P findStart(tile);
void bfs(P, tile *);
void normalizeTile(P, tile *);
tile * loadSampleInputs();
void printTile(tile);
string charToString(char);

int direction[4][2] = {
  {0, -1},
  {1, 0},
  {0, 1},
  {-1, 0}
};

int tileCount = 0;
const int INF = 100000000;

int main() {
  tile *tileArr;
  tileArr = loadSampleInputs();
  for(int i = 0; i < tileCount; i++) {
    printTile(tileArr[i]);
    solve(&tileArr[i]);
  }

  return 0;
}

void bfs(P start, tile * t) {
  if((*t).CheeseMax == stringToInt(charToString(t->tiles[start.first][start.second]))) {// 最后一块奶酪了
    return ;
  }
  t->tiles[start.first][start.second] = PASS;
  normalizeTile(start, t);

  queue<P> que;
  que.push(start);
  
  regex patternCheese("^[1-9]$");
  match_results<string::const_iterator> result;

  bool foundCheese = false;
  while(que.size() && !foundCheese) {
    P p = que.front();
    que.pop();

    for(int k = 0; k < 4; k++) {// 逆时针四个方向移动
      int nx = p.first + direction[k][0];
      int ny = p.second + direction[k][1];

      if(0 <= nx && nx < t->N && 0 <= ny && ny < t->M && t->d[nx][ny] == INF) {
        string s = charToString(t->tiles[nx][ny]);
        if(t->tiles[nx][ny] == PASS || regex_match(s, patternCheese)) {
          que.push(P(nx, ny));
          (*t).d[nx][ny] = (*t).d[p.first][p.second] + 1;
        }
        if(regex_match(s, result, patternCheese)) {

          if((*t).power >= stringToInt( result[0] )) {// 吃掉离自己最近且能吃下的奶酪
            foundCheese = true;
            (*t).power++;
            t->leastCostTime += ((*t).d[nx][ny] = ((*t).d[p.first][p.second] + 1));
            bfs(P(nx, ny), t);
            break;
          }
        }
      }
    }

  }
  return ;
}

void normalizeTile(P start, tile * t) {
  for(int i =0; i< t->N; i++) {
    for(int j =0; j< t->M; j++) {
      t->d[i][j] = INF;
    }
  }
  
  t->d[start.first][start.second] = 0;
  return ;
}

void solve(tile * t) {
  bfs(findStart(*t), t);
  cout << "Output: " << endl;
  cout << t->leastCostTime << endl << endl;
  return ;
}

tile * loadSampleInputs() {
  ifstream fin;
  fin.open("./algorithms/bfs/sample-cheese.txt");
  string s;
  regex patternNum("(\\d+)[\\s\\t]+(\\d+)[\\s\\t]+(\\d+)");
  match_results<string::const_iterator> result;
  tile * tileTmp;
  int N = -1;
  tile *tiles = new tile[10000];
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    if (( tileTmp ) && N >= 0 && N < ( *tileTmp ).N) {
      char buf[tileTmp->M];
      strcpy(buf, s.c_str());
      for(int k =0; k < tileTmp->M; k++) {
        ( *tileTmp ).tiles[N][k] = buf[k];
      }
      if(N++ == (tileTmp->N - 1)) {
        tiles[tileCount++] = *tileTmp;
        delete tileTmp;
        N = -1;
      }
    }
    if(regex_match(s, result, patternNum)) {
      tileTmp = new tile;
      tileTmp->N = stringToInt(result[1]);
      tileTmp->M = stringToInt(result[2]);
      tileTmp->CheeseMax = stringToInt(result[3]);
      tileTmp->power = 1;
      tileTmp->leastCostTime = 0;
      N = 0;
    }
  }
  fin.close();
  return tiles;
}

P findStart(tile t) {
  P start;

  for(int i =0; i< t.N; i++) {
    for(int j =0; j< t.M; j++) {
      if(t.tiles[i][j] == START) {
        start.first = i;
        start.second = j;
      }
    }
  }
  return start;
}

void printTile(tile t) {
  cout << "Input: " << endl;
  cout << t.N << "," << t.M << "," << t.CheeseMax << endl;
  for(int i =0; i< t.N; i++) {
    for(int j =0; j< t.M; j++) {
      cout << t.tiles[i][j];
    }
    cout << endl;
  }
  return ;
}


