/* 
 * @Author: fangqi
 * @Date: 2021-12-27 09:36:14
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-27 09:36:14
 * @Description: POJ-1065
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

struct wooden_stick {
  int l; // length
  int w; // weight
};

struct P {
  int G;
  int g;
  int i;
};

struct sample {
  int n; // number of wooden sticks
  wooden_stick ws[STRUCT_MAX_N];
  vector<vector<vector<int>>> mis_sets_group;
  int min_setup_time;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void dp(sample *);
void init_dp(sample *);
void calc_min_setup_time(sample *);
bool compare_ws(wooden_stick, wooden_stick);
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
  calc_min_setup_time(samp);
}

void init_dp(sample * samp) {
  vector<int> mis = {0};
  vector<vector<int>> mis_sets;
  mis_sets.push_back(mis);
  samp->mis_sets_group.push_back(mis_sets);

  samp->min_setup_time = samp->n;
}

void dp(sample * samp){
  sort(samp->ws, samp->ws + samp->n, compare_ws);
  init_dp(samp);

  for(int i = 1; i < samp->n; i++) {
    vector<P> matches;
    for(int G = 0; G < samp->mis_sets_group.size(); G++) {
      vector<vector<int>> group = samp->mis_sets_group[G];
      for(int g = 0; g < group.size(); g++) {
        vector<int> mis = group[g];
        wooden_stick back_ws = samp->ws[(mis.back())];
        if (samp->ws[i].w >= back_ws.w) {
          P p = {G, g, i};
          matches.push_back(p);
        }
      }
    }
    
    if (matches.empty()) { // 没有找到该条ws加入进去而不用增加setup_time的组
      for(vector<vector<vector<int>>>::iterator G = samp->mis_sets_group.begin(); G != samp->mis_sets_group.end(); G++) {
        vector<int> mis = {i};
        (*G).push_back(mis);
      }
    } else {
      for(vector<P>::iterator ip = matches.begin(); ip != matches.end(); ip++) {
        P p = *ip;
        vector<vector<int>> sets;
        vector<vector<int>> mgroup = samp->mis_sets_group[p.G];
        for(int g = 0; g < mgroup.size(); g++) {
          vector<int> mis = mgroup[g];
          if (g == p.g) {
            mis.push_back(p.i);
          }
          sets.push_back(mis);
        }
        samp->mis_sets_group.push_back(sets);
      }
    }
  }
}

bool compare_ws(wooden_stick ws1, wooden_stick ws2) {
  return ws1.l < ws2.l;
}

void calc_min_setup_time(sample * samp) {
  for(vector<vector<vector<int>>>::iterator G = samp->mis_sets_group.begin(); G != samp->mis_sets_group.end(); G++) {
    if (samp->min_setup_time > (*G).size()) {
      samp->min_setup_time = (*G).size();
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/wooden-sticks.txt");

  boost::regex patternRC("(\\d+)\\s");
  boost::regex pattern_ws("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  sample * samp;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0 && boost::regex_match(s, result, pattern_ws, boost::match_extra)) {
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          int idx = j / 2;
          if ((j % 2) == 0) {
            samp->ws[idx].l = num;
          } else {
            samp->ws[idx].w = num;
          }
        }
      }
      samples.push_back(*samp);
      delete samp;
      N = -1;
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->n = stringToInt(result[1]);
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
    wooden_stick ws = samp->ws[i];
    cout << ws.l << " " << ws.w << " ";
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->min_setup_time << endl;
  cout << endl;
}

