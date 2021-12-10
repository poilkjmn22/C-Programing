/* 
 * @Author: fangqi
 * @Date: 2021-12-09 21:22:37
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-09 21:22:37
 * @Description: POJ-3280
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

const string details[4] = {
  "Add",
  "Delete",
  "Add prev",
  "Delete prev"
};

struct cost {
  int A; // adding
  int D; // deleting
};

struct sample {
  int N; // costs 的长度
  int M; // source的长度
  string source;
  string cheapest_palindrome[STRUCT_MAX_N];
  map<char, cost> costs;
  int dp[STRUCT_MAX_N];
  int adding[STRUCT_MAX_N];
  int deleting[STRUCT_MAX_N];
  int min_cost;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void calc_add_str(sample *);
string build_cheapest_palindrome(int, int, sample *, int);
int handle_same_tail(int, string);
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
  calc_add_str(samp);

  samp->dp[0] = 0;
  samp->cheapest_palindrome[0] = samp->source.substr(0, 1);
  for(int i = 1; i < samp->M; i++) {
    map<char, cost>::iterator it = samp->costs.find(samp->source[i]);
    cost c = it->second;
    int mins[4] = {samp->dp[i - 1] + c.A, samp->dp[i - 1] + c.D, samp->adding[i - 1], samp->deleting[i - 1]};
    // 相同字符的情况需要特殊处理，如: abb->abbba,b;需要进一步减少花费
    int same_count = handle_same_tail(i, samp->source);
    if (same_count) {
      mins[2] -= same_count * c.A;
      mins[3] -= same_count * c.D;
    }
    int min = mins[0];
    int min_idx = 0;
    for(int j = 0; j < 4; j++) {
      if (min > mins[j]) {
        min = mins[j];
        min_idx = j;
      }
    }
    samp->cheapest_palindrome[i] = build_cheapest_palindrome(i, min_idx, samp, same_count);
    samp->dp[i] = min;
  }
  samp->min_cost = samp->dp[samp->M - 1];
}

int handle_same_tail(int idx, string str) {
  int count = 0;
  int i = idx - 1;
  while(i >= 0) {
    if (str[i--] == str[idx]) {
      count++;
    } else {
      break;
    }
  }
  return count;
}

string build_cheapest_palindrome(int j, int dx, sample * samp, int same_count) {
  string res;
  string rprev = samp->source.substr(0, j - same_count);
  switch(dx) {
    case 0:
      res = samp->source[j] + samp->cheapest_palindrome[j - 1] + samp->source[j];
      break;
    case 1:
      res = samp->cheapest_palindrome[j - 1];
      break;
    case 2:
      reverse(rprev.begin(), rprev.end());
      res = samp->source.substr(0, j + 1) + rprev;
      break;
    case 3:
      res = samp->source.substr(j - same_count, same_count + 1);
      break;
    default:
      break;
  }
  return res;
}

void calc_add_str(sample * samp) {
  for(int i = 0; i < samp->M; i++) {
    map<char, cost>::iterator it = samp->costs.find(samp->source[i]);
    samp->adding[i] = it->second.A;
    samp->deleting[i] = it->second.D;
    if (i > 0) {
      samp->adding[i] += samp->adding[i - 1];
      samp->deleting[i] += samp->deleting[i - 1];
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/cheapest-palindrome.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_cost("([a-z])\\s(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;
  int M = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0) {
      samp->source = s;

      N = -1;
      M = 0;
      continue;
    }
    if (samp && M >= 0 && boost::regex_match(s, result, pattern_cost)) {
      cost c = {stringToInt(result[2]), stringToInt(result[3])};
      string alp = result[1];
      samp->costs.insert(pair<char, cost>(alp[0], c));
      if (M++ == (samp->N - 1)) {
        M = -1;
        samples.push_back(*samp);
        delete samp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->N = stringToInt(result[1]);
      samp->M = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->N << " " << samp->M << endl;
  cout << samp->source << endl;
  for(map<char, cost>::iterator it = samp->costs.begin(); it != samp->costs.end(); it++) {
    cost c = (*it).second; 
    cout << (*it).first << " " << c.A << " " << c.D << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->min_cost << endl;
  cout << "how: ";
  for(int i = 0; i < samp->M; i++) {
    cout << samp->cheapest_palindrome[i];
    cout << " ";
  }
  cout << endl;
}

