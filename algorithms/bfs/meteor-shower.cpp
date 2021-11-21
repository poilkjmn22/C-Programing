/* 
 * @Author: fangqi
 * @Date: 2021-11-20 10:01:44
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-20 10:01:44
 * @Description: POJ-3669
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <queue>
#include "utils.h"

using namespace std;

#define MAX_X 300
#define MAX_Y 300
#define MAX_METEOR 50

struct meteor {
  int x;
  int y;
  int time;
};

struct sample{
  int meteor_size;
  meteor meteors[MAX_METEOR];
  int t[MAX_X + 1][MAX_Y + 1];//走到某一个位置的时间
  meteor safePos;
};
int sampleCount = 0;

void bfs(sample *);
bool is_safe(meteor, sample *);
bool can_pass(meteor,int, int, sample *);
sample * load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void print_sample_output(sample *);

int direction[4][2] = {
  {0, -1},
  {1, 0},
  {0, 1},
  {-1, 0}
};

int main() {
  sample * samples = load_sample_inputs();
  for(int i =0; i < sampleCount; i++) {
    print_sample_input(samples + i);
    process_sample(samples + i);
    print_sample_output(samples + i);
  }

  return 0;
}

void process_sample(sample * samp) {
  bfs(samp);
}

void print_sample_output(sample * samp) {
  meteor p = samp->safePos;
  cout << "Output: "
    << p.time << "(" << p.x << ", " << p.y << ")" << endl
    << endl;
}

void bfs(sample * samp) {
  queue<meteor> que;
  meteor origin = {0, 0, 0};
  que.push(origin);

  while(que.size()) {
    meteor p = que.front();
    que.pop();

    if(is_safe(p, samp)) {
      //找到了安全的位置
      samp->safePos = p;
      break;
    }

    for(int k = 0; k < 4; k++) {// 逆时针四个方向移动
      int nx = p.x + direction[k][0];
      int ny = p.y + direction[k][1];

      if(0 <= nx && nx <= MAX_X && 0 <= ny && ny <= MAX_Y && samp->t[nx][ny] == 0 && can_pass(p, nx, ny, samp)) {
        samp->t[nx][ny] = samp->t[p.x][p.y] + 1;
        meteor np = {nx, ny, samp->t[nx][ny]};
        que.push(np);
      }
    }
  }
}

bool can_pass(meteor p, int nx, int ny, sample * samp) {//新的移动位置（nx, ny）是否是安全能通过的
  bool res = true;
  meteor np = {nx, ny, samp->t[nx][ny]};
  int size = samp->meteor_size;
  for(int i =0; i< size; i++) {
    meteor m = samp->meteors[i];
    if((p.time + 1) >= m.time) {//时间早于陨石到达则能通过，否则， 被炸的区域无法通过
      for(int k =0; k < 4; k++) {
        if((m.x + direction[k][0]) == np.x && (m.y + direction[k][1]) == np.y) {
          res = false;
          break;
        }
      }
      if(m.x == np.x && m.y == np.y) {
        res = false;
      }
      if(!res) {
        break;
      }
    }
  }
  return res;
}

bool is_safe(meteor pos, sample * samp) {//陨石雨永远砸不到的地方是安全的
  bool res = true;
  int size = samp->meteor_size;
  for(int i =0; i< size; i++) {
    meteor m = samp->meteors[i];
    for(int k =0; k < 4; k++) {
      if((m.x + direction[k][0]) == pos.x && (m.y + direction[k][1]) == pos.y) {
        res = false;
        break;
      }
    }
    if(m.x == pos.x && m.y == pos.y) {
      res = false;
    }
    if(!res) {
      break;
    }
  }
  return res;
}

sample * load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/bfs/sample/meteor-shower.txt");

  sample * sampleTmp; 
  regex patternRC("\\d+");
  match_results<string::const_iterator> result;
  int N = -1;
  sample * samples = new sample[MAX_SAMPLE];

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    if (( sampleTmp ) && N >= 0 && N < ( *sampleTmp ).meteor_size) {
      regex patternM("(\\d+)\\s(\\d+)\\s(\\d+)");
      if(regex_match(s, result, patternM)) {
        meteor m = {stringToInt(result[1]), stringToInt(result[2]), stringToInt(result[3])};
        ( *sampleTmp ).meteors[N] = m;
      }
      if(N++ == (sampleTmp->meteor_size - 1)) {
        samples[sampleCount++] = *sampleTmp;
        delete sampleTmp;
        N = -1;
      }
    }
    if(regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->meteor_size = stringToInt(result[0]);
      meteor m0 = {0, 0, -1};
      sampleTmp->safePos = m0;
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * s) {
  cout << "Input: " << endl;
  cout << s->meteor_size << endl;
  for(int i = 0; i< s->meteor_size; i ++) {
    meteor m = s->meteors[i];
    cout << m.x << " " << m.y << " " << m.time
    << endl;
  }
}

