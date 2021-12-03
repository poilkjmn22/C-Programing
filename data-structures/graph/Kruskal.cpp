/* 
 * @Author: fangqi
 * @Date: 2021-12-03 18:35:16
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-03 18:35:16
 * @Description: 最小生成树问题（Kruskal算法）
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

bool comparison (edge e1, edge e2) {
  return e1.weight < e2.weight;
}
bool is_edge_same (edge e1, edge e2) {
  return e1.from == e2.to && e1.to == e2.from;
}

class DisjointSet {
  public:
    vector<int> rank, p;

    DisjointSet() {}
    DisjointSet(int size) {
      rank.resize(size, 0);
      p.resize(size, 0);
      for(int i = 0; i < size; i++) {
        make_set(i); 
      }
    }

    void make_set(int x) {
      p[x] = x;
      rank[x] = 0;
    }

    bool same(int x, int y) {
      return find_set(x) == find_set(y);
    }

    void unite(int x, int y) {
      link(find_set(x), find_set(y));
    }

    void link(int x, int y) {
      if (rank[x] > rank[y]) {
        p[y] = x;
      } else {
        p[x] = y;
        if (rank[x] == rank[y]) {
          rank[y]++;
        }
      }
    }

    int find_set(int x) {
      if (x != p[x]) {
        p[x] = find_set(p[x]);
      }
      return p[x];
    }
};

struct sample{
  int V;
  vector<edge> edges;
  int min_cost;
};

vector<sample> load_sample_inputs();
void sort_edges(sample *);
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
  DisjointSet dset = DisjointSet(samp->V);

  for(int i = 0; i < samp->edges.size(); i++) {
    edge e = samp->edges[i];
    if(!dset.same(e.from, e.to)) {
      samp->min_cost += e.weight;
      dset.unite(e.from, e.to);
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/Prim.txt");

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
              e->from = v;
              e->to = num;
            } else {
              e->weight = num;
              sampleTmp->edges.push_back(*e);
              delete e;
            }
          }
        }
      }

      if (N++ == (sampleTmp->V - 1)) {
        N = -1;
        sort_edges(sampleTmp);
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

void sort_edges(sample * samp) {
  sort(samp->edges.begin(), samp->edges.end(), comparison);
  vector<edge>::iterator it = unique(samp->edges.begin(), samp->edges.end(), is_edge_same);
  samp->edges.resize(distance(samp->edges.begin(), it));
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->V << endl;
  vector<edge> g = samp->edges;
  vector<edge>::iterator pd;
  for(pd = g.begin(); pd != g.end(); pd++) {
    edge e = *pd;
    cout << e.from << " " << e.to << " " << e.weight << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: ";
  cout << endl;
  cout << samp->min_cost << endl;
  cout << endl;
}

