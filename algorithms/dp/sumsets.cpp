/* 
 * @Author: fangqi
 * @Date: 2021-11-24 09:26:34
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-24 09:26:34
 * @Description: POJ-2229
 * @O(N): 1 <= N <= 1,000,000 穷竭搜索法：pow(N, logN / 2)
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
  int sum;
  int sumsets;
  int dp[STRUCT_MAX_N];
  int dp_merge[STRUCT_MAX_N + 1];
};
int sampleCount = 0;

void dp(sample *);
void dp_merge(sample *);
/* void merge(int, int, int, sample *); */
void dfs(int, int, sample *);
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
  dp_merge(samp);
  samp->dp[0] = 1;
  for(int i = 2; i <= samp->sum; i+=2) {
    /* merge(i / 4, 2, i, samp); */
    /* samp->dp[i] = samp->dp[i - 2] + samp->merge; */
    /* samp->merge = 0; */
    samp->dp[i] = samp->dp[i - 2] + samp->dp_merge[i / 2];
  }
  samp->sumsets = samp->dp[samp->sum % 2 == 1 ? (samp->sum - 1) : samp->sum];
}

// merge函数可以再更进一步进行动态规划的
void dp_merge(sample * samp) {
  int n_half = samp->sum / 2;
  for(int i = 0; i <= n_half; i++) {
    if (i < 2) {
      samp->dp_merge[i] = 1;
      continue;
    }
    if (i % 2 == 1) {
      samp->dp_merge[i] = samp->dp_merge[i - 1];
      continue;
    }
    samp->dp_merge[i] = samp->dp_merge[i - 2] + samp->dp_merge[i / 2]; 
  }
}

/* void merge(int repeat_count, int log2, int sum, sample * samp){ */
/*   if (log2 == 2) { */
/*     samp->merge++; */
/*   } */
/*   if (pow(2, log2) > sum) { */
/*     return; */
/*   } */
/*   for(int i = 1; i <= repeat_count; i++) { */
/*     samp->merge ++; */
/*     if (i >= 2) {//能向2的(log2 + 1)次幂合成 */
/*       merge(i / 2, log2 + 1, sum, samp); */
/*     } */
/*   } */
/* } */

// repeat_count: 能合成的x的个数
// log2: 上面的log2_x, 即x = pow(2, log2)
void dfs(int repeat_count, int log2, sample * samp) {
  if (pow(2, log2) > samp->sum) {
    return;
  }
  for(int i = 1; i <= repeat_count; i++) {
    samp->sumsets ++;
    if (i >= 2) {//能向2的(log2 + 1)次幂合成
      dfs(i / 2, log2 + 1, samp);
    }
  }
}

void process_sample(sample * samp) {
  dp(samp);
  /* dfs(samp->sum / 2, 1, samp); */
}

sample * load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/sumsets.txt");

  sample * sampleTmp; 
  boost::regex patternRC("\\d+");
  sample * samples = new sample[MAX_SAMPLE];

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->sum = stringToInt(result[0]);
      sampleTmp->sumsets = 1;
      samples[sampleCount++] = *sampleTmp;
      delete sampleTmp;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: ";
  cout << samp->sum;
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: "
    << samp->sumsets << endl;
  cout << endl;
}

