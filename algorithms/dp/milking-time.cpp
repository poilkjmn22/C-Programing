/* 
 * @Author: fangqi
 * @Date: 2021-12-15 09:56:06
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-15 09:56:06
 * @Description: POJ-3616
 * @Limitations: 1 <= N <= 1000000, 1 <= M <= 1000, 1 <= R <= N
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

struct interval {
  int S; // start hour
  int E; // end hour
  int P; // efficiency
};

struct sample {
  int N; // next N hours
  int M; // interval count
  int R; // rest hour
  interval is[STRUCT_MAX_N];
  int dp[STRUCT_MAX_N];
  int max_p;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
bool compare_interval(interval, interval);
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
  sort(samp->is, samp->is + samp->M, compare_interval);

  samp->dp[0] = samp->is[0].P;
  for(int i = 1; i < samp->M; i++) {
    int j = i - 1;
    int k = -1; // 最大E的interval，能够连续上当前interval
    while(j >= 0){
      if ((samp->is[j].E + samp->R) <= samp->is[i].S) {
        k = j;
        break;
      }
      j--;
    }
    samp->dp[i] = k >= 0 ? max(samp->dp[k] + samp->is[i].P, samp->dp[i - 1]) : max(samp->dp[i - 1], samp->is[i].P);
  }

  samp->max_p = samp->dp[samp->M - 1];
}

bool compare_interval(interval itl1, interval itl2) {
  return itl1.E < itl2.E;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/milking-time.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)\\s(\\d+)\\s(\\d+)");
  boost::regex pattern_interval("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if(samp && N >= 0 && boost::regex_match(s, result, pattern_interval, boost::match_extra)) {
      interval itl;
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          if (j == 0) {
            itl.S = num;
          } else if (j == 1) {
            itl.E = num;
          } else if (j == 2) {
            itl.P = num;
          }
        }
      }
      samp->is[N++] = itl;
      if (N == samp->M) {
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
      samp->R = stringToInt(result[3]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->N << " " << samp->M << " " << samp->R << endl;
  for(int i = 0; i < samp->M; i++) {
    interval itl = samp->is[i];
    cout << itl.S << " " << itl.E << " " << itl.P << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->max_p << endl;
  cout << endl;
}

