/* 
 * @Author: fangqi
 * @Date: 2021-12-24 23:56:32
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-24 23:56:32
 * @Description: POJ-3181
 * @O(n): N * K (没有优化递推关系式的情况下，为 N * K * x)(x为平均的N[i] / K[j])
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

const int MAX_N_D = 10000;
const int MAX_K = 100;

struct sample {
  int N;
  int K;
  int dp[MAX_N_D + 1][MAX_K + 1];
  int set_count;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void dp(sample *);
void init_dp(sample *);
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
  dp(samp);
  samp->set_count = samp->dp[samp->N][samp->K]; 
}

// 初始化
void init_dp(sample * samp) {
  for(int i = 1; i <= samp->N; i++) {
    samp->dp[i][1] = 1;
  }
}

void dp(sample * samp){
  /* init_dp(samp); */

  for(int k = 1; k <= samp->K; k++) {
    for(int n = 1; n <= samp->N; n++) {
      if (n < k) {
        samp->dp[n][k] = samp->dp[n][n];
      } else if (n == k) {
        samp->dp[n][k] = samp->dp[n][k - 1] + 1; // dn == 0时，需要特别处理一下
      } else {
        samp->dp[n][k] = samp->dp[n][k - 1] + samp->dp[n - k][k];
      }
    }
  }

  /* for(int i = 1; i <= samp->N; i++) { */
  /*   for(int j = 2; j <= samp->K; j++) { */
  /*     int k = 0; */
  /*     int r = 0; */
  /*     int sum = 0; */
  /*     while((r = (i - j * k)) >= 0) { */
  /*       sum += samp->dp[r][j - 1]; */
  /*       k++; */
  /*     } */
  /*     samp->dp[i][j] = sum; */
  /*   } */
  /* } */
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/dollar-dayz.txt");

  boost::regex patternRC("(\\d+)\\s(\\d+)");
  vector<sample> samples;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (boost::regex_match(s, result, patternRC)) {
      sample * samp = new sample;
      samp->N = stringToInt(result[1]);
      samp->K = stringToInt(result[2]);
      samples.push_back(*samp);
      delete samp;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->N << " " << samp->K;
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->set_count << endl;
  cout << endl;
}
