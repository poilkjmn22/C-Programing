/* 
 * @Author: fangqi
 * @Date: 2021-12-06 15:38:18
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-06 15:38:18
 * @Description: AOJ-2224
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

typedef pair<int, int> pile;

struct edge {
  int from; // 起点
  int to; // 终点
  double weight; // 权值

};

bool comparison (edge e1, edge e2) {
  return e1.weight > e2.weight;
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
  int E;
  vector<pile> vertex;
  vector<edge> edges;
  double min_holy_water;
};

vector<sample> load_sample_inputs();
void sort_edges(sample *);
void print_sample_input(sample *);
double calc_fence_length(pile, pile);
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
      dset.unite(e.from, e.to);
    } else {
      // 拆掉该条fence
      samp->min_holy_water += e.weight;
    }
  }
  samp->min_holy_water = setfixed(samp->min_holy_water, 3);
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/graph/sample/save-your-cats.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_pile("(-?\\d+)\\s(\\d+)");
  boost::regex pattern_fence("(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;
  int M = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;

    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_pile)) {
      sampleTmp->vertex.push_back(pile(stringToInt(result[1]), stringToInt(result[2])));

      if (N++ == (sampleTmp->V - 1)) {
        N = -1;
        M = 0;
      }
      continue;
    }
    if (sampleTmp && M >= 0 && boost::regex_match(s, result, pattern_fence)) {
      edge e = {stringToInt(result[1]) - 1, stringToInt(result[2]) - 1, 0};
      e.weight = calc_fence_length(sampleTmp->vertex[e.from], sampleTmp->vertex[e.to]);
      sampleTmp->edges.push_back(e);

      if (M++ == (sampleTmp->E - 1)) {
        M = -1;
        sort_edges(sampleTmp);
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

double calc_fence_length(pile p1, pile p2) {
  return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

void sort_edges(sample * samp) {
  sort(samp->edges.begin(), samp->edges.end(), comparison);
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->V << " " << samp->E << endl;
  vector<edge> g = samp->edges;
  vector<edge>::iterator pd;
  for(pd = g.begin(); pd != g.end(); pd++) {
    edge e = *pd;
    pile from = samp->vertex[e.from];
    pile to = samp->vertex[e.to];
    cout << "(" << from.first << "," << from.second << ")" << " (" << to.first << "," << to.second << ")" << " " << e.weight << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: ";
  cout << endl;
  cout << samp->min_holy_water << endl;
  cout << endl;
}

