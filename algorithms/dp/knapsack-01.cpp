/* 
 * @Author: fangqi
 * @Date: 2021-11-20 17:12:36
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-20 17:12:36
 * @Description: 01背包问题（《挑战程序设计竞赛一》例题）
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "utils.h"

using namespace std;
struct knapsack {
  int weight;
  int value;
};

struct sample{
  int knapsack_count;
  int max_weight;
  knapsack knapsacks[STRUCT_MAX_N];
  int max_value;
  int dp_res[STRUCT_MAX_N][STRUCT_MAX_M];
};
int sampleCount = 0;

int dp(sample *);
int dfs(int, int, sample *);
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

int dp(sample * samp) {
  for(int i = (samp->knapsack_count - 1); i >= 0; i--) {
    for(int j = 0; j <= samp->max_weight; j++) {
      if (j < samp->knapsacks[i].weight) {
        samp->dp_res[i][j] = samp->dp_res[i + 1][j];
      }else {
        samp->dp_res[i][j] = max(samp->dp_res[i + 1][j], samp->dp_res[i + 1][j - samp->knapsacks[i].weight] + samp->knapsacks[i].value);
      }
    }
  }
  return samp->dp_res[0][samp->max_weight];
}

int dfs(int idx, int sum, sample * samp) {
  knapsack ks = samp->knapsacks[idx];
  if (idx == samp->knapsack_count) {
    return 0;
  }
  if (sum < ks.weight) {// 重量会超过最大允许值，只能不选；
    return dfs(idx + 1, sum, samp);
  }
  return max(dfs(idx + 1, sum, samp), dfs(idx + 1, sum - ks.weight, samp) + ks.value);// 选或者不选都试一下。
}

void process_sample(sample * samp) {
  /* samp->max_value = dfs(0, samp->max_weight, samp); */
  samp->max_value = dp(samp);
}

sample * load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/knapsack-01.txt");

  sample * sampleTmp; 
  regex patternRC("(\\d+),(\\d+)");
  match_results<string::const_iterator> result;
  int N = -1;
  sample * samples = new sample[MAX_SAMPLE];

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    if (( sampleTmp ) && N >= 0 && N < ( *sampleTmp ).knapsack_count) {
      regex patternM("(\\d+)\\s(\\d+)");
      if(regex_match(s, result, patternM)) {
        knapsack m = {stringToInt(result[1]), stringToInt(result[2])};
        ( *sampleTmp ).knapsacks[N] = m;
      }
      if(N++ == (sampleTmp->knapsack_count - 1)) {
        samples[sampleCount++] = *sampleTmp;
        delete sampleTmp;
        N = -1;
      }
    }
    if(regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->knapsack_count = stringToInt(result[1]);
      sampleTmp->max_weight = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * s) {
  cout << "Input: " << endl;
  cout << s->knapsack_count << ", " << s->max_weight << endl;
  for(int i = 0; i< s->knapsack_count; i ++) {
    knapsack k = s->knapsacks[i];
    cout << "(" << k.weight << ", " << k.value << ")" << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: "
    << samp->max_value << endl;
}

