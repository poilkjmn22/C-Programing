/* 
 * @Author: fangqi
 * @Date: 2021-12-10 14:29:47
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-10 14:29:47
 * @Description: POJ-3187
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
const int max_n = 10;

struct compare_sum_order {
  bool operator () (const vector<int> &sum_order1, const vector<int> &sum_order2) {
    for(int i = 0; i < sum_order1.size(); i++) {
      if(sum_order1[i] > sum_order2[i]) {
        return false;
      } else if (sum_order1[i] < sum_order2[i]) {
        return true;
      }
    }
    return true;
  }
};
struct sample {
  int n; // 1,2,3,...n
  int sum;
  bool used[max_n + 1];
  int perm[max_n];
  set<vector<int>, compare_sum_order> sum_orders;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void permutation(int, sample *);
void calc_sum(sample *);
void backward_digits(int *, int, sample *);
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
  permutation(0, samp);
}

void permutation(int pos, sample * samp) {
  if (pos == samp->n) {
    calc_sum(samp);
    return;
  }
  for(int i = 1; i <= samp->n; i++) {
    if(!samp->used[i]){
      samp->used[i] = true;
      samp->perm[pos] = i;
      permutation(pos + 1, samp);
      samp->used[i] = false;
    }
  }
}

void calc_sum(sample * samp) {
  backward_digits(samp->perm, samp->n, samp);
}

void backward_digits(int * digits, int size, sample * samp) {
  if (size == 1) {
    if (samp->sum == digits[0]) {
      vector<int> sum_order;
      for(int i = 0; i < samp->n; i++) {
        sum_order.push_back(samp->perm[i]);
      }
      samp->sum_orders.insert(sum_order);
    }
    return;
  }
  int * res = new int[size - 1];
  for(int i = 0; i < size - 1; i++) {
    res[i] = digits[i] + digits[i + 1];
  }
  backward_digits(res, size - 1, samp);
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/backward-digit-sums.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  vector<sample> samples;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->n = stringToInt(result[1]);
      samp->sum = stringToInt(result[2]);
      samples.push_back(*samp);
      delete samp;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->n << " " << samp->sum << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  /* for(set<vector<int>, compare_sum_order>::iterator it = samp->sum_orders.begin(); it != samp->sum_orders.end(); it++) { */
    vector<int> sum_order = *samp->sum_orders.begin();
    for(vector<int>::iterator its = sum_order.begin(); its != sum_order.end(); its++) {
      cout << *its << " ";
    }
    cout << endl;
  /* } */
  cout << endl;
}

