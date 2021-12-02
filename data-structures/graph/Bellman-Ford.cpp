/* 
 * @Author: fangqi
 * @Date: 2021-11-30 11:53:25
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-30 11:53:31
 * @Description: 单源最短路问题1
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

struct edge {
  int to; // 终点
  int weight; // 权值
};

struct sample{
  int V;
  vector<edge> G[STRUCT_MAX_N];
  int d[STRUCT_MAX_N]; // 固定点到所有点的最短距离
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
  for(int v = 0; v < samp->V; v++) {
    samp->d[v] = INF;
  }
  samp->d[0] = 0;

  while(true) {
    bool need_update = false;
    for(int v = 0; v < samp->V; v++) {
      vector<edge>::iterator pd;
      vector<edge> g = samp->G[v];
      for(pd = g.begin(); pd != g.end(); pd++) {
        edge e = *pd;
        if (samp->d[v] != INF && samp->d[e.to] > (samp->d[v] + e.weight)) {
          samp->d[e.to] = samp->d[v] + e.weight;
          need_update = true;
        }
      }
    }
    if (!need_update) {
      break;
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/Bellman-Ford.txt");

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
        edge * e;
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          if (j == 0) {
            v = num;
          }else if (j > 1) {
            if (!( j % 2 )) {
              e = new edge;
              e->to = num;
            } else {
              e->weight = num;
              sampleTmp->G[v].push_back(*e);
              delete e;
            }
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
    vector<edge> g = samp->G[i];
    cout << i << " " << g.size() << " ";
      vector<edge>::iterator pd;
      for(pd = g.begin(); pd != g.end(); pd++) {
        cout << (*pd).to << " " << (*pd).weight;
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
  for(int v = 0; v < samp->V; v++) {
    cout << v << " " << samp->d[v] << endl;
  }
  cout << endl;
}

