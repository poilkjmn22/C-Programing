/* 
 * @Author: fangqi
 * @Date: 2021-12-09 14:16:03
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-09 14:16:03
 * @Description: POJ-3050
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

const int grid_size = 5;
const int total_hops = 5;
const int hop_direction[4][2] = {
  {0, 1},
  {1, 0},
  {0, -1},
  {-1, 0},
};

struct sample {
  string G[grid_size][grid_size];
  set<int> res;
  string digits;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void hopscotch(int, int, int, sample *);
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
  for(int i = 0; i < grid_size; i++) {
    for(int j = 0; j < grid_size; j++) {
      hopscotch(i, j, 0, samp);
      samp->digits = "";
    }
  }
}

void hopscotch(int x, int y,int step, sample * samp) {
  samp->digits += samp->G[x][y];
  if (step == total_hops) {
    samp->res.insert(stringToInt(samp->digits));
    return;
  }
  for(int i = 0; i < 4; i++) {
    int dx = x + hop_direction[i][0];
    int dy = y + hop_direction[i][1];
    if (0 <= dx && dx < grid_size && 0 <= dy && dy < grid_size) {
      hopscotch(dx, dy, step + 1, samp);
      samp->digits.erase(step + 1);
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/hopscotch.txt");

  sample * sampleTmp;
  boost::regex patternRC("\\d+");
  boost::regex pattern_line("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_line, boost::match_extra)) {
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          sampleTmp->G[N][j] = result.captures(i)[j];
        }
      }
      if (N++ == (grid_size - 1)) {
        N = -1;
        samples.push_back(*sampleTmp);
        delete sampleTmp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  for(int i = 0; i < grid_size; i++) {
    for(int j = 0; j < grid_size; j++) {
      cout << samp->G[i][j] << " ";
    }
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->res.size() << endl;
  for(set<int>::iterator it = samp->res.begin(); it != samp->res.end(); it++) {
    cout << *it << " "; 
  }
  cout << endl;
}

