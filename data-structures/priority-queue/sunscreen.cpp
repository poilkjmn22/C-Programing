/* 
 * @Author: fangqi
 * @Date: 2021-11-26 14:33:29
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-26 14:33:29
 * @Description: POJ-3614
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

typedef pair<int, int> P_SPFc;
typedef pair<int, int> P_SPFl;

struct sample{
  int C;
  int L;
  P_SPFc SPFcs[STRUCT_MAX_N];
  P_SPFl SPFls[STRUCT_MAX_N];
  int max_cows_protected;
};
int sampleCount = 0;

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

void process_sample(sample * samp) {
  priority_queue<P_SPFc> pque_cows;
  priority_queue<P_SPFl> pque_lotions;

  for(int i = 0; i < samp->C; i++) {
    pque_cows.push(samp->SPFcs[i]); 
  }
  for(int i = 0; i < samp->L; i++) {
    pque_lotions.push(samp->SPFls[i]); 
  }
  P_SPFl lotion;
  while(!pque_cows.empty()) {
    P_SPFc cow = pque_cows.top();
    pque_cows.pop();

    if (lotion.second == 0) {
      if (pque_lotions.empty()) {
        break;
      }
      lotion = pque_lotions.top();
      pque_lotions.pop();
    }
    if (lotion.second > 0 && lotion.first >= cow.first) {
      lotion.second--;
      samp->max_cows_protected++;
    }
  }
}

sample * load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/priority-queue/sample/sunscreen.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_P_SPF("(\\d+)\\s(\\d+)");
  sample * samples = new sample[MAX_SAMPLE];
  int N = -1;
  int M = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_P_SPF)) {
      sampleTmp->SPFcs[N] = P_SPFc(stringToInt(result[2]), stringToInt(result[1]));
      if (N++ == (sampleTmp->C - 1)) {
        N = -1;
        M = 0;
      }
      continue;
    }
    if (sampleTmp && M >= 0 && boost::regex_match(s, result, pattern_P_SPF)) {
      sampleTmp->SPFls[M] = P_SPFl(stringToInt(result[1]), stringToInt(result[2]));
      if (M++ == (sampleTmp->L - 1)) {
        samples[sampleCount++] = *sampleTmp;
        delete sampleTmp;
        M = -1;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->C = stringToInt(result[1]);
      sampleTmp->L = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->C << ", " << samp->L << endl;
  for(int i = 0; i < samp->C; i++) {
    cout << samp->SPFcs[i].first << " " << samp->SPFcs[i].second;
    cout << endl;
  }
  for(int i = 0; i < samp->L; i++) {
    cout << samp->SPFls[i].first << " " << samp->SPFls[i].second;
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: "
    << samp->max_cows_protected << endl;
  cout << endl;
}

