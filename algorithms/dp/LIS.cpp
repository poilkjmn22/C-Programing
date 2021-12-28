/* 
 * @Author: fangqi
 * @Date: 2021-11-22 11:38:44
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-22 11:38:44
 * @Description: Longest Increasing Subsequence
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

struct sample{
  int count;
  int src[STRUCT_MAX_N];
  int sel[STRUCT_MAX_N];
  int L;
  int LIS[STRUCT_MAX_N];
  int dist[STRUCT_MAX_N];
  vector<int> path;
};
int sampleCount = 0;

void dp(sample *);
void dp2(sample *);
void fill(sample *, int);
void get_path(sample *);
void dfs(sample *);
sample * load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void print_sample_output(sample *);

int main() {
  sample * samples = load_sample_inputs();
  for(int i =0; i < sampleCount; i++) {
    print_sample_input(samples + i);
    process_sample(samples + i);
    print_sample_output(samples + i);
  }

  return 0;
}


void dp(sample * samp) {
  for(int i = 0; i < samp->count; i++) {
    samp->LIS[i] = 1;
    for(int j = 0; j < i; j++) {
      if (samp->src[j] < samp->src[i]) {
        samp->LIS[i] = max(samp->LIS[i], samp->LIS[j] + 1);
      }
    }
    samp->L = max(samp->L, samp->LIS[i]);
  }
}

// LIS[i - 1] 定义为长度为i的最长递增子序列的最后一个元素
void dp2(sample * samp) {
  fill(samp, MAX_N);
  for(int i = 0; i < samp->count; i++) {
    *lower_bound(samp->LIS, samp->LIS + i, samp->src[i]) = samp->src[i];
  }
  samp->L = lower_bound(samp->LIS, samp->LIS + samp->count - 1, MAX_N) - samp->LIS;

  get_path(samp);
}

void fill(sample * samp, int v) {
  for(int i = 0; i < samp->count; i++) {
    samp->LIS[i] = v;
  }
}

void get_path(sample * samp) {
  for(int i = 0; i < samp->L; i++) {
    samp->path.push_back(samp->LIS[i]); 
  }
}

void dfs(int pos, int n, sample * samp) {
  if (samp->L > 0) {
    return ;
  }
  if(n == pos) {
    samp->L = n;
    for(int i = 0; i < n; i++) {
      samp->dist[i] = samp->src[samp->sel[i]];
    }
    return ;
  }
  for(int i = 0; i < samp->count; i++) {
    if (i <= (samp->count - (n - pos))) {
      if (pos > 0 && (i <= samp->sel[pos - 1] || samp->src[i] <= samp->src[samp->sel[pos - 1]])) {
        continue;
      }
      samp->sel[pos] = i;
      dfs(pos + 1, n, samp);
    }
  }
}

void process_sample(sample * samp) {
  /* for(int i = samp->count; i > 0; i--) { */
  /*   dfs(0, i, samp); */
  /*   if (samp->L > 0) { */
  /*     break; */
  /*   } */
  /* } */
  /* dp(samp); */
  dp2(samp);
}

sample * load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/LIS.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(?:(\\d+)\\s)+(\\d+)$");
  sample * samples = new sample[MAX_SAMPLE];

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if(boost::regex_match(s, result, patternRC, boost::match_extra)) {
      sampleTmp = new sample;
      sampleTmp->count = 0;
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          sampleTmp->src[sampleTmp->count++] = stringToInt(result.captures(i)[j]);
        }
      }
      samples[sampleCount++] = *sampleTmp;
      delete sampleTmp;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  for(int i = 0; i< samp->count; i ++) {
    cout << samp->src[i] << " ";
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: "
    << samp->L << endl;
  /* cout << "path: "; */
  /* for(int i = 0; i < samp->path.size(); i++) { */
  /*   cout << samp->path[i] << " "; */
  /* } */
  /* cout << endl; */
}

