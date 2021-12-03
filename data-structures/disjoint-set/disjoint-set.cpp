/* 
 * @Author: fangqi
 * @Date: 2021-12-03 16:32:44
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-03 16:32:44
 * @Description: 并查集（互质的集合）
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

struct query {
  int type; // 操作种类（0: unite, 1: same）
  int x;
  int y;
};

struct sample{
  int n; // 0, 1, 2, 3, ..., n - 1 的集合
  int qc; // 查询总数
  vector<query> query_list; // 查询列表
  vector<bool> is_same; // x,y是否属于同一集合。
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
  DisjointSet dset = DisjointSet(samp->n);
  vector<query>::iterator vq;
  for(vq = samp->query_list.begin(); vq != samp->query_list.end(); vq++) {
     query q = *vq;
     if (q.type == 0) {
       dset.unite(q.x, q.y);
     } else {
      samp->is_same.push_back(dset.same(q.x, q.y));
     }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/disjoint-set/sample/disjoint-set.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_query("(\\d+)\\s(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_query)) {
      query q;
      q.type = stringToInt(result[1]);
      q.x = stringToInt(result[2]);
      q.y = stringToInt(result[3]);
      sampleTmp->query_list.push_back(q);

      if (N++ == (sampleTmp->qc - 1)) {
        N = -1;
        samples.push_back(*sampleTmp);
        delete sampleTmp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->n = stringToInt(result[1]);
      sampleTmp->qc = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->n << " " << samp->qc  << endl;
  vector<query> g = samp->query_list;
  vector<query>::iterator pd;
  for(pd = g.begin(); pd != g.end(); pd++) {
    query q = *pd;
    cout << q.type << " " << q.x << " " << q.y;
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: ";
  cout << endl;
  vector<bool>::iterator vi;
  for(vi = samp->is_same.begin(); vi != samp->is_same.end(); vi++) {
    cout << *vi << endl;
  }
}

