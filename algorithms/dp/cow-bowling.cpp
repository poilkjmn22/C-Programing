/* 
 * @Author: fangqi
 * @Date: 2021-11-23 16:48:17
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-23 16:48:17
 * @Description: POJ-3176
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
  int size;
  int row_count;
  int highest_sum;
  int cows[STRUCT_MAX_N];
  int dp[STRUCT_MAX_N];
};
int sampleCount = 0;

void dp(sample *);
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
  for(int i = samp->row_count; i >= 1; i--) {
    for(int j = 0; j < i; j++) {
      int start = i * (i - 1) / 2;
      if (i == samp->row_count) {
        samp->dp[start + j] = samp->cows[start + j];
        continue;
      }
      samp->dp[start + j] = samp->cows[start + j] + max(samp->dp[start + j + i], samp->dp[start + j + i + 1]);
    }
  }
  samp->highest_sum = samp->dp[0];
}

void process_sample(sample * samp) {
  dp(samp);
}

sample * load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/cow-bowling.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(\\d+):");
  boost::regex patternCows("(?:(\\d+)(?:\\s|$))+");
  int N = -1;
  sample * samples = new sample[MAX_SAMPLE];

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if(sampleTmp && N >= 0 && boost::regex_match(s, result, patternCows, boost::match_extra)) {
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          sampleTmp->cows[sampleTmp->size++] = stringToInt(result.captures(i)[j]);
        }
      }
      if (N++ == (sampleTmp->row_count - 1)) {
        samples[sampleCount++] = *sampleTmp;
        delete sampleTmp;
        N = -1;
      }
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->row_count = stringToInt(result[1]);
      sampleTmp->size = 0;
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  for(int i = 0; i< samp->size; i ++) {
    cout << samp->cows[i] << " ";
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: "
    << samp->highest_sum << endl;
    /* << " ("; */

  /* for(int i = 0; i < samp->highest_sum; i++) { */
  /*   cout << samp->dist[i]; */
  /*   if (i < samp->highest_sum - 1) { */
  /*     cout << ", "; */
  /*   } */
  /* } */
  /* cout << ")" << endl; */
}

