/* 
 * @Author: fangqi
 * @Date: 2021-12-08 11:07:53
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-08 23:56:52
 * @Description: AOJ-2249
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

struct edge {
  int from;
  int to; // 
  int dist; // 距离
  int cost; // 花费
};

struct sample {
  int V;
  int E;
  vector<edge> edges;
  int d[STRUCT_MAX_N + 1];
  int cost[STRUCT_MAX_N + 1];
  vector<int> path[STRUCT_MAX_N + 1];
  int prev[STRUCT_MAX_N + 1];
  int min_cost;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void init_d(sample *);
void get_path(sample *);
void get_path_v(int, sample *);
int calc_min_cost(sample *);
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
  init_d(samp);

  set<int> same[STRUCT_MAX_N];
  while(true) {
    bool update = false;
    for(vector<edge>::iterator it = samp->edges.begin(); it != samp->edges.end(); it++) {
      edge e = *it;
      int ld = samp->d[e.to];
      if (samp->d[e.from] != INF && ld > (samp->d[e.from] + e.dist)) {
        samp->d[e.to] = samp->d[e.from] + e.dist;
        samp->cost[e.to] = e.cost;
        samp->prev[e.to] = e.from;
        update = true;
      }
      if (samp->d[e.from] != INF && ld == (samp->d[e.from] + e.dist)) {
        if (same[e.to].find(e.from) == same[e.to].end()) { // 首次加入相同最短距离下的不同前驱结点
          same[e.to].insert(e.from);
          if (samp->cost[e.to] > e.cost) {
            samp->cost[e.to] = e.cost;
            samp->prev[e.to] = e.from;
          }
          update = true;
        }
      }
    }

    if (!update) {
      break;
    }
  }
  
  get_path(samp);
  samp->min_cost = calc_min_cost(samp);
}

void init_d(sample * samp) {
  for(int i = 1; i <= samp->V; i++) {
    samp->d[i] = INF;
  }
  samp->d[1] = 0;
}

int calc_min_cost(sample * samp) {
  int res = 0;
  for(int i = 2; i <= samp->V; i++) {
    res += samp->cost[i];    
  }
  return res;
}

void get_path(sample * samp) {
  for(int i = 2; i <= samp->V; i++) {
    get_path_v(i, samp);
  }
}

void get_path_v(int v, sample * samp) {
  int p = v;
  while(p != 1) {
    samp->path[v].push_back(p);
    p = samp->prev[p];
  }
  samp->path[v].push_back(p);
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/road-construction.txt");

  sample * sampleTmp;
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_edge("(\\d+)\\s(\\d+)\\s(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_edge)) {
      edge e = {stringToInt(result[1]), stringToInt(result[2]), stringToInt(result[3]), stringToInt(result[4])};
      edge e2 = {stringToInt(result[2]), stringToInt(result[1]), stringToInt(result[3]), stringToInt(result[4])};
      sampleTmp->edges.push_back(e);
      sampleTmp->edges.push_back(e2);
      if (N++ == (sampleTmp->E - 1)) {
        N = -1;
        samples.push_back(*sampleTmp);
        delete sampleTmp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->V = stringToInt(result[1]);
      sampleTmp->E = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->V << " " << samp->E << endl;
  for(int i = 0; i < samp->E; i++) {
    edge e = samp->edges[i * 2];
    cout << e.from << " " << e.to << " " << e.dist << " " << e.cost << endl;
     
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  for(int i = 2; i <= samp->V; i++) {
    cout << samp->d[i] << ":";
    vector<int> path = samp->path[i];
    for(vector<int>::reverse_iterator it = path.rbegin(); it != path.rend(); it++) {
      cout << *it;
      if (it < path.rend() - 1) {
        cout << "->";
      }
    }
    cout << endl;
  }
  cout << "min_cost:" << samp->min_cost << endl;
  cout << endl;
}

