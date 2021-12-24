/* 
 * @Author: fangqi
 * @Date: 2021-12-23 22:04:40
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-23 22:04:40
 * @Description: POJ-3009
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

#define vacant '0'
#define block '1'
#define start '2'
#define goal '3'

const int MAX_MOVEMENT = 10;

typedef pair<int, int> P;

struct sample {
  int N;
  int M;
  P ps;
  P pg;
  char board[STRUCT_MAX_N][STRUCT_MAX_M];
  int d[STRUCT_MAX_N][STRUCT_MAX_M];
  int movement;
  bool success;
  int min_movement;
  P path[MAX_MOVEMENT + 1];
  P min_path[MAX_MOVEMENT + 1];
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void dfs(int, int, sample *);
void update_min_path(sample *);
void print_sample_output(sample *);

int main() {
  vector<sample> samples = load_sample_inputs();
  vector<sample>::iterator pd;
  for(pd = samples.begin(); pd != samples.end(); pd++) {
    sample * samp = &(*pd);
    print_sample_input(samp);
    process_sample(samp);
    print_sample_output(samp);
  }
  return 0;
}

void process_sample(sample * samp) {
  dfs(samp->ps.first, samp->ps.second, samp);
  if (!samp->success || samp->min_movement > MAX_MOVEMENT) {
    samp->min_movement = -1;
  }
}

void dfs(int x, int y, sample * samp) {
  samp->path[samp->movement] = P(x, y);
  if (samp->movement >= MAX_MOVEMENT) {
    return;
  }
  for(int i = 1; i <= x; i++) { // 四个方向寻找(上)
    int dx = x - i;
    int dy = y;
    if (samp->board[dx][dy] == block) {
      if (i == 1) { // 此处无法移动
        break;
      }
      samp->board[dx][dy] = vacant;
      samp->movement++;
      dfs(dx + 1, dy, samp);
      samp->movement--;
      samp->board[dx][dy] = block;
      break;
    }
    if (samp->board[dx][dy] == goal) {
      samp->success = true;
      if (samp->min_movement > (samp->movement + 1)) {
        samp->min_movement = samp->movement + 1;
        update_min_path(samp);
      }
      return;
    }
  }

  for(int i = 1; i <= (samp->M - y - 1); i++) { // 四个方向寻找(右)
    int dx = x;
    int dy = y + i;
    if (samp->board[dx][dy] == block) {
      if (i == 1) { // 此处无法移动
        break;
      }
      samp->board[dx][dy] = vacant;
      samp->movement++;
      dfs(dx, dy - 1, samp);
      samp->movement--;
      samp->board[dx][dy] = block;
      break;
    }
    if (samp->board[dx][dy] == goal) {
      samp->success = true;
      if (samp->min_movement > (samp->movement + 1)) {
        samp->min_movement = samp->movement + 1;
        update_min_path(samp);
      }
      return;
    }
  }

  for(int i = 1; i <= (samp->N - x - 1); i++) { // 四个方向寻找(下)
    int dx = x + i;
    int dy = y;
    if (samp->board[dx][dy] == block) {
      if (i == 1) { // 此处无法移动
        break;
      }
      samp->board[dx][dy] = vacant;
      samp->movement++;
      dfs(dx - 1, dy, samp);
      samp->movement--;
      samp->board[dx][dy] = block;
      break;
    }
    if (samp->board[dx][dy] == goal) {
      samp->success = true;
      if (samp->min_movement > (samp->movement + 1)) {
        samp->min_movement = samp->movement + 1;
        update_min_path(samp);
      }
      return;
    }
  }

  for(int i = 1; i <= y; i++) { // 四个方向寻找(左)
    int dx = x;
    int dy = y - i;
    if (samp->board[dx][dy] == block) {
      if (i == 1) { // 此处无法移动
        break;
      }
      samp->board[dx][dy] = vacant;
      samp->movement++;
      dfs(dx, dy + 1, samp);
      samp->movement--;
      samp->board[dx][dy] = block;
      break;
    }
    if (samp->board[dx][dy] == goal) {
      samp->success = true;
      if (samp->min_movement > (samp->movement + 1)) {
        samp->min_movement = samp->movement + 1;
        update_min_path(samp);
      }
      return;
    }
  }
}

void update_min_path(sample * samp) {
  for(int i = 0; i < samp->min_movement; i++) {
    samp->min_path[i] = samp->path[i]; 
  }
  samp->min_path[samp->min_movement] = samp->pg; 
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/curling-2.0.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0) {
      for(int i = 0; i < s.length(); i+=2) {
        samp->board[N][i / 2] = s[i];
        if (s[i] == start) {
          samp->ps = P(N, i / 2);
        }
        if (s[i] == goal) {
          samp->pg = P(N, i / 2);
        }
      }
      if (N++ == (samp->N - 1)) {
        samples.push_back(*samp);
        delete samp;
        N = -1;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->N = stringToInt(result[2]);
      samp->M = stringToInt(result[1]);
      samp->min_movement = MAX_MOVEMENT + 1;
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->M << " " << samp->N << endl;
  for(int i = 0; i < samp->N; i++) {
    for(int j = 0; j < samp->M; j++) {
      cout << samp->board[i][j] << " ";
    }
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->min_movement << endl;
  cout << "min_path: ";
  if (samp->success && samp->min_movement <= MAX_MOVEMENT) {
    for(int i = 0; i <= samp->min_movement; i++) {
      cout << samp->min_path[i].first << "," << samp->min_path[i].second << "  "; 
    }
  } else {
    cout << "fail";
  }
  cout << endl;
  cout << endl;
}

