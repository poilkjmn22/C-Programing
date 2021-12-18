/* 
 * @Author: fangqi
 * @Date: 2021-12-18 11:47:22
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-18 11:47:22
 * @Description: POJ-1742
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

typedef pair<int, int> coin;

struct sample {
  int n;
  int m;
  set<int> prices;
  /* int values[STRUCT_MAX_N]; // A1,A2, ..., An */
  /* int numbers[STRUCT_MAX_N]; // C1, C2, ..., Cn */
  coin coins[STRUCT_MAX_N]; // C1, C2, ..., Cn
  int price_count;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
bool compare_coin(coin, coin);
void print_prices(sample *);
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
  sort(samp->coins, samp->coins + samp->n, compare_coin);

  bool overm = false; // 超过了m, 则后续不用迭代
  for(int i = 0; i < samp->n; i++) {
    coin cc = samp->coins[i];
    int v = cc.first;
    int c = cc.second;
    int k = 1;

    set<int> nprices = samp->prices;
    for(int k = 1; k <= c; k++) {
      for(set<int>::iterator it = samp->prices.begin(); it != samp->prices.end(); it++) {
        int nv = *it + (v * k);
        if (nv > samp->m) {
          overm = true;
          break;
        } else {
          nprices.insert(nv);
        }
      }
    }

    for(int k = 1; k <= c; k++) {
      int nv = v * k;
      if (nv > samp->m) {
        overm = true;
        break;
      } else {
        nprices.insert(nv);
      }
    }

    samp->prices = nprices;

    if (overm) {
      break;
    }
  }
  
  samp->price_count = samp->prices.size();
}

bool compare_coin(coin c1, coin c2) {
  return c1.first < c2.first;
}

void print_prices(sample * samp) {
  for(set<int>::iterator it = samp->prices.begin(); it != samp->prices.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dp/sample/coins.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_AC("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0 && boost::regex_match(s, result, pattern_AC, boost::match_extra)) {
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          if (j < samp->n) {
            samp->coins[j].first = num;
          } else {
            samp->coins[j - samp->n].second = num;
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
      samp->m = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->n << " " << samp->m << endl;
  for(int i = 0; i < samp->n; i++) {
    cout << samp->coins[i].first << " ";
  }
  for(int i = 0; i < samp->n; i++) {
    cout << samp->coins[i].second << " ";
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->price_count << endl;
  cout << "all prices: ";
  print_prices(samp);
}

