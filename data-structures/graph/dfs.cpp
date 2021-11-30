/* 
 * @Author: fangqi
 * @Date: 2021-11-29 16:47:28
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-29 16:47:28
 * @Description: 图的深度优先遍历
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

struct discover {
  int start; // 发现时刻
  int end; // 结束时刻
};

struct sample{
  int V;
  vector<int> G[STRUCT_MAX_N];
  discover res[STRUCT_MAX_N];
  bool processed[STRUCT_MAX_N];
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
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
  stack<int> processing;
  processing.push(1);
  int step = 1;
  discover dis;
  dis.start = step;
  dis.end = 0;
  samp->res[1] = dis;

  while(!processing.empty()) {
    int p = processing.top();
    if (samp->processed[p]) {
      processing.pop();
      continue;
    }

    vector<int> g = samp->G[p];
    vector<int>::iterator pd;
    bool should_process = true;
    for(pd = g.begin(); pd != g.end(); pd++) {
      if (!samp->processed[*pd]) {
        should_process = false;
        processing.push(*pd);
        discover dis;
        dis.start = ++step;
        dis.end = 0;
        samp->res[*pd] = dis;
      }
    }
    if (should_process) {
      processing.pop();
      samp->processed[p] = true;
      samp->res[p].end = ++step;
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/dfs.txt");

  sample * sampleTmp; 
  boost::regex patternRC("\\d");
  boost::regex pattern_edges("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_edges, boost::match_extra)) {
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        int v;
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          if (j == 0) {
            v = num;
          }else if (j > 1) {
            sampleTmp->G[v].push_back(num);
          }
        }
      }

      if (N++ == (sampleTmp->V - 1)) {
        N = -1;
        samples.push_back(*sampleTmp);
        delete sampleTmp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->V = stringToInt(result[0]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->V << endl;
  for(int i = 0; i < samp->V; i++) {
    vector<int> g = samp->G[i + 1];
    cout << i + 1 << " " << g.size() << " ";
      vector<int>::iterator pd;
      for(pd = g.begin(); pd != g.end(); pd++) {
        cout << (*pd);
        if (pd != g.end()) {
          cout << " ";
        }
      }
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: ";
  cout << endl;
  for(int i = 0; i < samp->V; i++) {
    cout << i + 1 << " "
      << samp->res[i + 1].start << " " << samp->res[i + 1].end
      << endl;
  }
}

