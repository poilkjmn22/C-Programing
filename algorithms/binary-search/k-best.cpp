/* 
 * @Author: fangqi
 * @Date: 2021-12-31 10:20:29
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-31 10:20:29
 * @Description: POJ-3111
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

const int MAX_N_J = 100000; // number of jewels
const double MAX_SUM_V = 10000000; //

struct jewel {
  int v;
  int w;
};

struct sample {
  int n; // number of jewels
  int k; // numbers keeped
  jewel jewels[MAX_N_J];
  double max_avg;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
bool compare_item(int, int);
bool condition(double, sample *);
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
  double lb = 0;
  double ub = MAX_SUM_V;
  for(int i = 0; i < 100; i++) {
    double mid = (lb + ub) / 2; 

    if (condition(mid, samp)) {
      lb = mid;
    } else {
      ub = mid;
    }
  }
  samp->max_avg = ub;
}

bool compare_item(int a, int b) {
  return a > b;
}

bool condition(double avg, sample * samp) {
  double * items = new double[samp->n];
  for(int i = 0; i < samp->n; i++) {
    jewel je = samp->jewels[i];
    items[i] = je.v - avg * je.w; 
  }
  sort(items, items + samp->n, compare_item);

  double sum = 0;
  for(int i = 0; i < samp->k; i++) {
    sum += items[i]; 
  }

  return sum >= 0;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/binary-search/sample/k-best.txt");

  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_jewel("(\\d+)\\s(\\d+)");
  vector<sample> samples;
  sample * samp;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N != -1 && boost::regex_match(s, result, pattern_jewel)) {
      jewel je = {stringToInt(result[1]), stringToInt(result[2])};
      samp->jewels[N] = je;
      if (N++ == (samp->n - 1)) {
        samples.push_back(*samp);
        delete samp;
        N = -1;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->n = stringToInt(result[1]);
      samp->k = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->n << " " << samp->k << endl;
  for(int i = 0; i < samp->n; i++) {
    cout << samp->jewels[i].v << " " << samp->jewels[i].w << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->max_avg << endl;
  cout << endl;
}

