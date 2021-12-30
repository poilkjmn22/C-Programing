/* 
 * @Author: fangqi
 * @Date: 2021-12-30 10:31:27
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-30 10:31:27
 * @Description: POJ-3258
 * @O(n): N * log(L)
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

const int MAX_L = 1000000000;
const int MAX_R = 50000;

struct sample {
  int n; // number of rocks (exclude start, end rocks)
  int m; // remove m rocks
  int l; // river length
  int rocks[MAX_R];
  int max_min_distance;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
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
  sort(samp->rocks, samp->rocks + samp->n);

  int lb = 0;
  int ub = MAX_L;
  while((ub - lb) > 1) {
    int mid = (ub + lb) / 2;
    if (condition(mid, samp)) {
      lb = mid;
    } else {
      ub = mid;
    }
  }

  samp->max_min_distance = lb;
}

bool condition(int d, sample * samp) {
  int removed = 0;
  int prev = 0;
  for(int i = 0; i < samp->n; i++) {
    if ((samp->rocks[i] - prev) < d) {// remove rocks[i]
      removed++;
    } else {
      prev = samp->rocks[i];
    }
  }
  if ((samp->l - prev) < d) { // 最后一个石头是否要remove？
    removed++;
  }
  return removed <= samp->m;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/binary-search/sample/river-hopscotch.txt");

  boost::regex patternRC("(\\d+)\\s(\\d+)\\s(\\d+)");
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
      samp->rocks[N] = stringToInt(s);
      if (N++ == (samp->n - 1)) {
        samples.push_back(*samp);
        delete samp;
        N = -1;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->l = stringToInt(result[1]);
      samp->n = stringToInt(result[2]);
      samp->m = stringToInt(result[3]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->l << " " << samp->n << " " << samp->m << endl;
  for(int i = 0; i < samp->n; i++) {
    cout << samp->rocks[i];
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->max_min_distance << endl;
  cout << endl;
}

