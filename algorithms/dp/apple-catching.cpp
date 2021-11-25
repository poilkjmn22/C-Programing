
/* 
 * @Author: fangqi
 * @Date: 2021-11-25 10:27:26
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-25 10:27:26
 * @Description: POJ-2385
 * @O(N): N * M
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
  int T;
  int W;
  int dp[STRUCT_MAX_N][STRUCT_MAX_M];
  int tree_drops[STRUCT_MAX_N];
  int max_catching_cout;
};
int sampleCount = 0;

void dp(sample *);
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
  for(int i = 0; i < samp->T; i++) {
     for(int j = 0; j <= samp->W; j++) {
      if (i == 0) {
        samp->dp[i][j] = 1;
        continue;
      }
      if (samp->tree_drops[i] == samp->tree_drops[i - 1]) {
        samp->dp[i][j] = samp->dp[i - 1][j] + 1;
      }else {
        if (j == 0) {
          samp->dp[i][j] = samp->dp[i - 1][j];
        } else {
          samp->dp[i][j] = max(samp->dp[i - 1][j], samp->dp[i - 1][j - 1] + 1);
        }
      }
    }
  }
  samp->max_catching_cout = samp->dp[samp->T - 1][samp->W];
}

void dfs(int repeat_count, int log2, sample * samp) {

}

void process_sample(sample * samp) {
  dp(samp);
  /* dfs(samp->sum / 2, 1, samp); */
}

sample * load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/apple-catching.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex patternTD("\\d");
  sample * samples = new sample[MAX_SAMPLE];
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, patternTD)) {
      sampleTmp->tree_drops[N] = stringToInt(result[0]);
      if (N++ == (sampleTmp->T - 1)) {
        samples[sampleCount++] = *sampleTmp;
        delete sampleTmp;
        N = -1;
      }
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->T = stringToInt(result[1]);
      sampleTmp->W = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << samp->T << ", " << samp->W << endl;
  for(int i = 0; i < samp->T; i++) {
    cout << samp->tree_drops[i];
    if (i != samp->T - 1) {
      cout << " ";
    }
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: "
    << samp->max_catching_cout << endl;
  cout << endl;
}

