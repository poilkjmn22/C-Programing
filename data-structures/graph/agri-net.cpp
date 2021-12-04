/* 
 * @Author: fangqi
 * @Date: 2021-12-04 16:49:47
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-04 16:49:47
 * @Description: POJ-1258
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

struct edge {
  int from;
  int to; // 终点
  int weight; // 权值
};

struct sample{
  int V;
  int G[STRUCT_MAX_N][STRUCT_MAX_M];
  int min_cost;
  bool in_tree[STRUCT_MAX_N]; // 该顶点是否已经在树中
};

struct comparison {
  bool operator () (edge e1, edge e2) {
    return e1.weight > e2.weight;
  }
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
  priority_queue<edge, vector<edge>, comparison> pque;

  int s = 0;// 最开始选择一个顶点。
  int count = samp->V;
  samp->in_tree[s] = true;
  while(count-- > 1){
    for(int i = 0; i < samp->V; i++) {
      if (!samp->in_tree[i]) {
        edge e = {s, i, samp->G[s][i]};
        pque.push(e);
      }
    }

    edge min_edge;
    while(!pque.empty()) {
      min_edge = pque.top();
      pque.pop();
      if (!samp->in_tree[min_edge.to]) {
        break;
      }
    }
    samp->min_cost += min_edge.weight;
    s = min_edge.to;
    samp->in_tree[s] = true;
  }

}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/agri-net.txt");

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
        for(int j = 0; j < c_size; ++j) {
          sampleTmp->G[N][j] = stringToInt(result.captures(i)[j]);
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
    for(int j = 0; j < samp->V; j++) {
      cout << samp->G[i][j];
      if (j < samp->V - 1) {
        cout << " ";
      }
    }
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: ";
  cout << endl;
  cout << samp->min_cost << endl;
  cout << endl;
}

