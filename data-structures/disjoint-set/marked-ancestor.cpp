/* 
 * @Author: fangqi
 * @Date: 2021-12-05 12:20:00
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-05 12:20:00
 * @Description: AOJ-2170
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

    /* bool same(int x, int y) { */
    /*   return find_set(x) == find_set(y); */
    /* } */

    void unite(int x, int y) {
      p[x] = y;
    }

    /* void link(int x, int y) { */
    /*   if (rank[x] > rank[y]) { */
    /*     p[y] = x; */
    /*   } else { */
    /*     p[x] = y; */
    /*     if (rank[x] == rank[y]) { */
    /*       rank[y]++; */
    /*     } */
    /*   } */
    /* } */

    int find_set(int x) {
      return p[x];
    }
};

typedef pair<int, vector<int>> p_tree;

struct query {
  string type; // 操作种类（'Q': query, 'M': mark）
  int node;
};

struct sample{
  int n; // 1, 2, 3, ..., n的集合
  int qc; // 查询总数
  vector<int> tree; // 树，1为根
  vector<query> query_list; // 查询列表
  map<int, vector<int>> * forest;
  bool marked[STRUCT_MAX_N];
  int sum_q; // 查询的marked祖先节点的总和
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void build_forest(sample *);
/* void print_forest(sample *); */
void mark_node(int ,int, DisjointSet * , sample * );
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
  build_forest(samp);

  DisjointSet dset = DisjointSet(samp->n + 1);
  // mark node 1
  samp->marked[1] = true;
  for(int i = 2; i <= samp->n; i++) {
    dset.unite(i, 1);
  }
  vector<query>::iterator vq;
  for(vq = samp->query_list.begin(); vq != samp->query_list.end(); vq++) {
     query q = *vq;
     if (q.type == "Q") {
       samp->sum_q += dset.find_set(q.node);
     } else {
       samp->marked[q.node] = true;
       mark_node(q.node, q.node, &dset, samp);
     }
  }
}

void build_forest(sample * samp) {
  samp->forest = new map<int, vector<int>>;
  for(int i = 2; i <= samp->n; i++) {
    int p = samp->tree[i];
    map<int, vector<int>>::iterator it = (*samp->forest).find(p);
    if (it != (*samp->forest).end()) {
      it->second.push_back(i);
    }else {
      vector<int> child = {i};
      (*samp->forest).insert(p_tree(p, child));
    }
  }
  
}

/* void print_forest(sample * samp) { */
/*   map<int, vector<int>>::iterator root = (*samp->forest).find(1); */
/*   if (root != (*samp->forest).end()) { */
/*     vector<int> child = root->second; */
/*     for(int i = 0; i < child.size(); i++) { */
/*       cout << child[i] << " "; */ 
/*     } */
/*     cout << endl; */
/*   } */
/* } */

void mark_node(int qnode,int marked, DisjointSet * dset, sample * samp) {
  (*dset).unite(qnode, marked);
  map<int, vector<int>>::iterator mroot = (*samp->forest).find(qnode);
  if (mroot != (*samp->forest).end()) {
    vector<int> child = mroot->second;
    for(int i = 0; i < child.size(); i++) {
      if (!samp->marked[child[i]]) {
        mark_node(child[i], marked, dset, samp);
      }
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/disjoint-set/sample/marked-ancestor.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_node("\\d+");
  boost::regex pattern_query("(Q|M)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;
  int M = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 2 && boost::regex_match(s, result, pattern_node)) {
      int parent = stringToInt(result[0]);
      sampleTmp->tree.push_back(parent);

      if (N++ == (sampleTmp->n)) {
        N = -1;
        M = 0;
      }
      continue;
    }
    if (sampleTmp && M >= 0 && boost::regex_match(s, result, pattern_query)) {
      string type = result[1];
      int node = stringToInt(result[2]);
      query q = {type, node};
      sampleTmp->query_list.push_back(q);

      if (M++ == (sampleTmp->qc - 1)) {
        M = -1;
        samples.push_back(*sampleTmp);
        delete sampleTmp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->n = stringToInt(result[1]);
      sampleTmp->qc = stringToInt(result[2]);
      sampleTmp->tree.push_back(0);
      sampleTmp->tree.push_back(1);
      N = 2;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->n << " " << samp->qc  << endl;
  
  for(int i = 2; i <= samp->n; i++) {
    cout << samp->tree[i] << endl; 
  }

  vector<query> g = samp->query_list;
  vector<query>::iterator pd;
  for(pd = g.begin(); pd != g.end(); pd++) {
    query q = *pd;
    cout << q.type << " " << q.node;
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: ";
  cout << samp->sum_q << endl;
  cout << endl;
}

