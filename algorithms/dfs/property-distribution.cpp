/* 
 * @Author: fangqi
 * @Date: 2021-12-19 09:27:43
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-19 09:27:43
 * @Description: AOJ-0118
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

#define apple '@'
#define oyster '#'
#define orange '*'


const int direction[4][2] = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1},
};

struct sample {
  int N;
  int M;
  char garden[STRUCT_MAX_N][STRUCT_MAX_M];
  bool visited[STRUCT_MAX_N][STRUCT_MAX_M];
  int distribution_count; // 接受分配的人数
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void dfs(int, int, sample *);
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
  for(int i = 0; i < samp->N; i++) {
    for(int j = 0; j < samp->M; j++) {
      if (!samp->visited[i][j]) {
        dfs(i, j, samp);
        samp->distribution_count++;
      }
    }
  }
}

void dfs(int x, int y, sample * samp) {
  samp->visited[x][y] = true;
  for(int i = 0; i < 4; i++) {
    int dx = x + direction[i][0];
    int dy = y + direction[i][1];
    if (0 <= dx && dx < samp->N && 0 <= dy && dy < samp->M && !samp->visited[dx][dy] && samp->garden[dx][dy] == samp->garden[x][y]) { // 把同种类果树连接起来
      dfs(dx, dy, samp);
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/property-distribution.txt");

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
      for(int i = 0; i < s.length(); i++) {
        samp->garden[N][i] = s[i];
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
      samp->N = stringToInt(result[1]);
      samp->M = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->N << " " << samp->M << endl;
  for(int i = 0; i < samp->N; i++) {
    for(int j = 0; j < samp->M; j++) {
      cout << samp->garden[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->distribution_count << endl;
}

