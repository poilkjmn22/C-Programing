/* 
 * @Author: fangqi
 * @Date: 2021-12-10 21:06:04
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-10 21:06:04
 * @Description: AOJ-0033
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
const int BALL_COUNT = 10;

struct sample {
  int balls[BALL_COUNT];
  vector<int> container_1;
  vector<int> container_2;
  string answer;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void dfs(int, sample *);
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
  dfs(BALL_COUNT - 1, samp);
}

void dfs(int nth, sample * samp) {
  if (nth < 0) {
    bool in_order_1 = true;
    for(int i = 1; i < samp->container_1.size(); i++) { // 要求球号是递减的
      if (samp->container_1[i - 1] < samp->container_1[i]) {
        in_order_1 = false;
        break;
      }
    }

    bool in_order_2 = true;
    for(int i = 1; i < samp->container_2.size(); i++) {
      if (samp->container_2[i - 1] < samp->container_2[i]) {
        in_order_2 = false;
        break;
      }
    }
    if (in_order_1 && in_order_2) {
      samp->answer = "YES";
    }
    return;
  }
  // 放入左边
  samp->container_1.push_back(samp->balls[nth]);
  dfs(nth - 1, samp);
  samp->container_1.pop_back();

  // 放入右边
  samp->container_2.push_back(samp->balls[nth]);
  dfs(nth - 1, samp);
  samp->container_2.pop_back();

}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/ball.txt");

  sample * samp;
  boost::regex pattern_balls("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (boost::regex_match(s, result, pattern_balls, boost::match_extra)) {
      samp = new sample;
      samp->answer = "NO";
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          samp->balls[j] = stringToInt(result.captures(i)[j]);
        }
      }
      samples.push_back(*samp);
      delete samp;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  for(int i = 0; i < BALL_COUNT; i++) {
    cout << samp->balls[i] << " ";
  }
  cout << endl;
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->answer << endl;
}

