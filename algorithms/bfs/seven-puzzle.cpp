/* 
 * @Author: fangqi
 * @Date: 2021-12-21 11:43:21
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-21 11:43:21
 * @Description: AOJ-0121
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

const int CARD_NUM = 8;

const int direction[4][2] = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1},
};

struct status {
  int step;
  int last_swap_card;
  int cards[2][4];
};

struct sample {
  int cards[CARD_NUM];
  int min_step_count;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void bfs(sample *);
bool is_init_status(status, sample *);
status init_final_status();
status change_status(status, int);
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
  bfs(samp);
}

void bfs(sample * samp) {
  queue<status> que;
  que.push(init_final_status());

  while(true) {
    status st = que.front();
    que.pop();

    if (is_init_status(st, samp)) {
      samp->min_step_count = st.step;
      break;
    }

    for(int i = 0; i < 4; i++) {
      status dst = change_status(st, i);
      if (dst.step >= 0) {
        que.push(dst);
      }
    }
  }
}

status init_final_status() {
  status st_f;
  st_f.step = 0;
  st_f.last_swap_card = 0;
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 4; j++) {
      st_f.cards[i][j] = i * 4 + j;
    }
  }
  
  return st_f;
}

status change_status(status st, int d) {
  int x;
  int y;
  // 0的位置
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 4; j++) {
      if (st.cards[i][j] == 0) {
        x = i;
        y = j;
        break;
      }
    }
  }
  int dx = x + direction[d][0];
  int dy = y + direction[d][1];
  status dst;
  dst.step = -1; // 特殊值，表示该status为无效的/非法的。
  if (0 <= dx && dx < 2 && 0 <= dy && dy < 4 && st.cards[dx][dy] != st.last_swap_card) {
    dst.step = st.step + 1;
    dst.last_swap_card = st.cards[dx][dy];
    // 0 跟新的值交换
    for(int j = 0; j < 2; j++) {
      for(int k = 0; k < 4; k++) {
        if (j == dx && k == dy) {
          dst.cards[j][k] = 0;
        } else if (st.cards[j][k] == 0) {
          dst.cards[j][k] = st.cards[dx][dy];
        } else {
          dst.cards[j][k] = st.cards[j][k];
        }
      }
    }
  }
  return dst;
}

bool is_init_status(status st, sample * samp) {
  bool res = true;
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 4; j++) {
      if(samp->cards[i * 4 + j] != st.cards[i][j]) {
        res = false;
        break;
      }
    }
  }
  return res;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/bfs/sample/seven-puzzle.txt");

  boost::regex pattern_AC("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (boost::regex_match(s, result, pattern_AC, boost::match_extra)) {
      sample samp;

      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          samp.cards[j] = stringToInt(result.captures(i)[j]);
        }
      }
      samples.push_back(samp);
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  for(int i = 0; i < CARD_NUM; i++) {
    cout << samp->cards[i] << " ";
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->min_step_count << endl;
}

