/* 
 * @Author: fangqi
 * @Date: 2021-12-04 11:24:25
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-04 11:24:25
 * @Description: AOJ-0189
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
  int from; // 起点
  int to; // 终点
  int weight; // 权值
};

struct sample {
  int V;
  int E;
  vector<edge> edges;
  int d[STRUCT_MAX_N][STRUCT_MAX_N]; // 任意两点间的最短距离
  int min_sum_cost;
  int convenient_location;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void print_shortest_paths(sample *);
int calc_sum_cost(int, sample *);
void fill_INF(sample *);
void fill_edge(sample *);
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
  fill_INF(samp);
  fill_edge(samp);
  // Floyd-Warshall求所有点对最短路径
  for(int k = 0; k < samp->V; k++) {
    for(int i = 0; i < samp->V; i++) {
        if (samp->d[i][k] == INF) { // 加法溢出，则丢弃掉
          continue;
        }
      for(int j = 0; j < samp->V; j++) {
        if (samp->d[k][j] == INF) { // 加法溢出，则丢弃掉
          continue;
        }
        samp->d[i][j] = min(samp->d[i][j], samp->d[i][k] + samp->d[k][j]);
      }
    }
  }
  /* print_shortest_paths(samp); */

  for(int v = 0; v < samp->V; v++) {
    int sum_cost = calc_sum_cost(v, samp);
    if(samp->min_sum_cost > sum_cost) {
      samp->min_sum_cost = sum_cost;
      samp->convenient_location = v;
    } else if (samp->min_sum_cost == sum_cost) {
      samp->convenient_location = min(samp->convenient_location, v);
    }
  }
}

void print_shortest_paths(sample * samp) {
  cout << "Output: ";
  cout << endl;
  for(int v = 0; v < samp->V; v++) {
    if (v == 0) {
      cout << "  ";
    }
    cout << v << " ";
    if (v == samp->V - 1) {
      cout << endl;
    }
  }
  for(int v = 0; v < samp->V; v++) {
    cout << v << " ";
    for(int v1 = 0; v1 < samp->V; v1++) {
      cout << samp->d[v1][v] << " ";
    }
    cout << endl;
  }
}

int calc_sum_cost(int v, sample * samp) {
  int res = 0;
  for(int i = 0; i < samp->V; i++) {
    res += samp->d[v][i];
  }
  return res;
}

void fill_INF(sample * samp) {
  for(int i = 0; i < samp->V; i++) {
    for(int j = 0; j < samp->V; j++) {
      samp->d[i][j] = i == j ? 0 : INF;
    }
  }
}

void fill_edge(sample * samp) {
  vector<edge> g = samp->edges;
  vector<edge>::iterator pd;
  for(pd = g.begin(); pd != g.end(); pd++) {
    edge e = *pd;
    samp->d[e.from][e.to] = e.weight;
    samp->d[e.to][e.from] = e.weight;
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/convenient-location.txt");

  sample * sampleTmp; 
  boost::regex patternRC("\\d+");
  boost::regex pattern_edges("(\\d+)\\s(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_edges)) {
      edge e;
      e.from = stringToInt(result[1]);
      e.to = stringToInt(result[2]);
      e.weight = stringToInt(result[3]);
      sampleTmp->edges.push_back(e);

      sampleTmp->V = max(e.from, e.to);

      if (N++ == (sampleTmp->E - 1)) {
        N = -1;
        sampleTmp->V++;
        samples.push_back(*sampleTmp);
        delete sampleTmp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->E = stringToInt(result[0]);
      sampleTmp->min_sum_cost = INF;
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->V << ", " << samp->E << endl;
  for(int i = 0; i < samp->E; i++) {
     edge e = samp->edges[i];
     cout << e.from << " " << e.to << " " << e.weight << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->convenient_location << " " << samp->min_sum_cost << endl;
  cout << endl;
}

