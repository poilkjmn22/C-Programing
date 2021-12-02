/* 
 * @Author: fangqi
 * @Date: 2021-12-02 17:31:38
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-02 17:31:38
 * @Description: 任意两点间的最短路问题（Floyd-Warshall 算法）
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

struct sample {
  int V;
  vector<edge> G[STRUCT_MAX_N];
  int d[STRUCT_MAX_N][STRUCT_MAX_N]; // 任意两点间的最短距离
  int prev[STRUCT_MAX_N];
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void fill_INF(sample *);
void fill_edge(sample *);
void get_path(int, int, sample *);
void print_sample_output(sample *);

int main() {
  vector<sample> samples = load_sample_inputs();
  vector<sample>::iterator pd;
  for(pd = samples.begin(); pd != samples.end(); pd++) {
    sample * samp = &(*pd);
    print_sample_input(samp);
    process_sample(samp);
    get_path(0, 4, samp);
    print_sample_output(samp);
  }
  return 0;
}

void process_sample(sample * samp) {
  fill_INF(samp);
  fill_edge(samp);
  for(int k = 0; k < samp->V; k++) {
    for(int i = 0; i < samp->V; i++) {
      for(int j = 0; j < samp->V; j++) {
        if (samp->d[i][k] == INF || samp->d[k][j] == INF) {
          continue;
        }
        samp->d[i][j] = min(samp->d[i][j], samp->d[i][k] + samp->d[k][j]);
      }
    }
  }
}

void fill_INF(sample * samp) {
  for(int i = 0; i < samp->V; i++) {
    for(int j = 0; j < samp->V; j++) {
      samp->d[i][j] = INF;
    }
  }
}

void fill_edge(sample * samp) {
  for(int i = 0; i < samp->V; i++) {
    samp->d[i][i] = 0;

    vector<edge> g = samp->G[i];
    vector<edge>::iterator pd;
    for(pd = g.begin(); pd != g.end(); pd++) {
      edge e = *pd;
      samp->d[i][e.to] = e.weight;
    }
  }
}

void get_path(int s, int v, sample * samp) {
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
    for(int v1 = 0; v1 < samp->V; v1++) {
      cout << v << "->" << v1 << ": " << samp->d[v][v1] << endl;
    }
    cout << endl;
  }
}

