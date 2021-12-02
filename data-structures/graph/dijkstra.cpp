/* 
 * @Author: fangqi
 * @Date: 2021-12-02 11:17:39
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-02 11:17:39
 * @Description: 单源最短路问题2（不存在负权值的情况下）
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
  int to; // 终点
  int weight; // 权值
};

struct sample{
  int V;
  vector<edge> G[STRUCT_MAX_N];
  int d[STRUCT_MAX_N]; // 固定点到所有点的最短距离
  /* int used[STRUCT_MAX_N]; // 已经确定了的最短距离的顶点 */
  int prev[STRUCT_MAX_N];
};

typedef pair<int, int> P;
struct comparison {
  bool operator () (P p1, P p2) {
    return p1.second > p2.second;
  }
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(int, sample *);
int * get_path(int, int, sample *);
void print_sample_output(sample *);

int main() {
  vector<sample> samples = load_sample_inputs();
  vector<sample>::iterator pd;
  for(pd = samples.begin(); pd != samples.end(); pd++) {
    sample * samp = &(*pd);
    print_sample_input(samp);
    process_sample(0, samp);
    get_path(0, 4, samp);
    print_sample_output(samp);
  }
  return 0;
}

void process_sample(int s, sample * samp) {
  for(int v = 0; v < samp->V; v++) {
    samp->d[v]  = INF;
  }
  samp->d[s] = 0;
  priority_queue<P, vector<P>, comparison> pque;
  pque.push(P(s, 0));
  
  while(!pque.empty()) {
    /* int v = -1; */
    /* for(int u = 0; u < samp->V; u++) { // 剩下的尚未使用过的顶点中，距离最小的点最短距离已经确定了：因为不存在负边，以后的更新不会再改变最短距离了 */
    /*   if (!samp->used[u] && (v == -1 || samp->d[v] > samp->d[u])) { */
    /*     v = u; */
    /*   } */
    /* } */
    /* if (v == -1) { */
    /*   break; */
    /* } */
    /* samp->used[v] = true; */

    P p = pque.top();
    pque.pop();
    int v = p.first;
    if (samp->d[v] < p.second) { // 优先队列中取出来的如果不是最小值，忽略掉
      continue;
    }
    vector<edge> g = samp->G[v];
    vector<edge>::iterator pd;
    for(pd = g.begin(); pd != g.end(); pd++) {
      edge e = *pd;
      if ((samp->d[v] + e.weight) < samp->d[e.to]) {
        samp->d[e.to] = samp->d[v] + e.weight; 
        samp->prev[e.to] = v; // 前驱顶点 记录下来。
        pque.push(P(e.to, samp->d[e.to]));
      }
    }
  }
}

int * get_path(int s, int v, sample * samp) {
  int * path = new int[samp->V];
  int p = v;
  int idx = 0;
  path[idx] = p;
  while(p != s) {
    p = samp->prev[p];
    path[++idx] = p;
  }
  
  cout << "the shortest path " << s << "->" << v << ": ";
  for(; idx >= 0; idx--) {
    cout << path[idx] << " "; 
  }
  cout << endl;
  return path;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/dijkstra.txt");

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

