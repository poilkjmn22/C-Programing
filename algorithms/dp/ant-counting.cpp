/* 
 * @Author: fangqi
 * @Date: 2021-12-23 09:53:20
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-23 09:53:20
 * @Description: POJ-3046
 * @O(n) = T * B, 不优化递推关系式的话则会是T * B * N[t](N[t] 为种类t的个数)
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

struct sample {
  int T; // 种类1, 2, 3, ..., T
  int A; // 蚂蚁总数
  int S; // size range start
  int B; // size range end
  int nT[STRUCT_MAX_N + 1];
  int dp[STRUCT_MAX_N + 1][STRUCT_MAX_N + 1];
  int set_count;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void dp(sample *);
void init_type_1(sample *);
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

  for(int s = samp->S; s <= samp->B; s++) {
    samp->set_count += samp->dp[samp->T][s]; 
  }
}

// type=1时，特殊处理
void init_type_1(sample * samp) {
  const int nT_1 = samp->nT[1];
  for(int j = 1; j <= samp->B; j++) { // set group size
    if (j <= nT_1) {
      samp->dp[1][j] = 1;
    }
  }
  for(int t = 1; t <= samp->T; t++) { // family type
    samp->dp[t][1] = t;
  }
}

void dp(sample * samp){
  init_type_1(samp);

  for(int i = 2; i <= samp->T; i++) { // ant family-type
    for(int j = 2; j <= samp->B; j++) { // set group size
      int k = samp->nT[i];
      int tail = 0;
      if((j-k) > 1) {
        tail = samp->dp[i - 1][j - k - 1]; 
      } else if ((j-k) == 1) { // 全部选了i,这种情况不要漏掉。
        tail = 1;
      }
      samp->dp[i][j] = samp->dp[i][j - 1] + samp->dp[i - 1][j] - tail;
      /* 优化递推关系式 || */
      /* for(int k = 0; k <= samp->nT[i]; k++) { */
      /*   if((j-k) > 0) { */
      /*     samp->dp[i][j] += samp->dp[i - 1][j - k]; */ 
      /*   } else if (k == j) { // 全部选了i,这种情况不要漏掉。 */
      /*     samp->dp[i][j] += 1; */
      /*   } */
      /* } */
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/ant-counting.txt");

  boost::regex patternRC("(\\d+)\\s(\\d+)\\s(\\d+)\\s(\\d+)");
  vector<sample> samples;
  sample * samp;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0) {
      samp->nT[stringToInt(s)]++;
      if (N++ == (samp->A - 1)) {
        N = -1;
        samples.push_back(*samp);
        delete samp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->T = stringToInt(result[1]);
      samp->A = stringToInt(result[2]);
      samp->S = stringToInt(result[3]);
      samp->B = stringToInt(result[4]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->T << " " << samp->A << " " << samp->S << " " << samp->B << endl;
  for(int i = 1; i <= samp->T; i++) {
    cout << i << ": " << samp->nT[i] << endl;
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->set_count << endl;
  cout << endl;
}

