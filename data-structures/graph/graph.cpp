/* 
 * @Author: fangqi
 * @Date: 2021-11-29 10:55:00
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-29 10:55:00
 * @Description: 邻接矩阵表示法
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

struct sample{
  int V;
  vector<int> G[STRUCT_MAX_N];
  int ** matrix;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample);
void process_sample(sample);
void print_sample_output(sample);

int main() {
  vector<sample> samples = load_sample_inputs();
  vector<sample>::iterator pd;
  for(pd = samples.begin(); pd != samples.end(); pd++) {
    print_sample_input(*pd);
    process_sample(*pd);
    print_sample_output(*pd);
  }
  return 0;
}

void process_sample(sample samp) {
  for(int i = 0; i < samp.V; i++) {
    vector<int> g = samp.G[i + 1];
    vector<int>::iterator pd;
    samp.matrix[i] = new int[STRUCT_MAX_M];
    for(int j = 0; j < STRUCT_MAX_M; j++) {
      samp.matrix[i][j] = 0;
    }
    for(pd = g.begin(); pd != g.end(); pd++) {
      samp.matrix[i][(*pd) - 1] = 1;
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/graph.txt");

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
      sampleTmp->matrix = new int *[STRUCT_MAX_N];
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample samp) {
  cout << "Input: " << endl << samp.V << endl;
  for(int i = 0; i < samp.V; i++) {
    vector<int> g = samp.G[i + 1];
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

void print_sample_output(sample samp) {
  cout << "Output: ";
  cout << endl;
  for(int i = 0; i < samp.V; i++) {
    for(int j = 0; j < samp.V; j++) {
      cout << samp.matrix[i][j];
      if (j < samp.V - 1) {
        cout << " ";
      }
    }
    cout << endl;
  }
}

