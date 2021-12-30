/* 
 * @Author: fangqi
 * @Date: 2021-12-30 18:10:53
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-30 18:10:53
 * @Description: POJ-3104
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

const int MAX_N_C = 100000; // number of cloth
const int MAX_W_C = 1000000000; // water contained in cloth
const int MAX_K = 1000000000; // radiator speed

struct sample {
  int n; // number of cloths
  int k; // radiator speed
  int cloths[MAX_N_C];
  int min_cost_time;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
bool compare_cloth(int, int);
bool condition(int, sample *);
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
  sort(samp->cloths, samp->cloths + samp->n, compare_cloth);

  int lb = 0;
  int ub = MAX_W_C;
  while((ub - lb) > 1) {
    int mid = (ub + lb) / 2;
    if (condition(mid, samp)) { // 能晾干则缩小范围
      ub = mid;
    } else { // 不能晾干则扩大范围
      lb = mid;
    }
  }

  samp->min_cost_time = ub;
}

bool compare_cloth(int a, int b) {
  return a > b;
}

// 所有衣物在<= t的时间内能够晾干
bool condition(int t, sample * samp) {
  int dry_time = 0;
  for(int i = 0; i < samp->n; i++) {
    int c = samp->cloths[i] - dry_time;
    int nd = 0; // radiator上烘烤的时间
    while (c > (t - dry_time) && dry_time <= t) {// 需要放到radiator上
      c -= (++nd) * samp->k;
      dry_time++;
      if (c < 0) {
        c = 0;
        break;
      }
    }
    if (dry_time > t) {
      return false;
    }
  }
  return dry_time <= t;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/binary-search/sample/drying.txt");

  boost::regex patternRC("\\d+");
  boost::regex pattern_cloths("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  sample * samp;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N == 0 && boost::regex_match(s, result, pattern_cloths, boost::match_extra)) {
      N++;
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          samp->cloths[j] = num;
        }
      }
      continue;
    }
    if (samp && N >= 1) {
      samp->k = stringToInt(s);
      samples.push_back(*samp);
      delete samp;
      N = -1;
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->n = stringToInt(result[0]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->n << endl;
  for(int i = 0; i < samp->n; i++) {
    cout << samp->cloths[i] << " ";
  }
  cout << endl << samp->k << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->min_cost_time << endl;
  cout << endl;
}

