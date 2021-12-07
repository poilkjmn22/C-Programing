/* 
 * @Author: fangqi
 * @Date: 2021-12-07 18:35:59
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-07 18:35:59
 * @Description: POJ-1703
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

struct message {
  string type;
  int c1; // 
  int c2; // 
};

struct sample {
  int n;
  int M;
  vector<message> messages;
  int d[STRUCT_MAX_N + 1];
  vector<string> res;
};

const string SAME_GANG = "In the same gang.";
const string DIFF_GANG = "In different gangs.";
const string NOT_SURE = "Not sure yet.";

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
  DisjointSet dset_same = DisjointSet(samp->n + 1);
  DisjointSet dset_diff = DisjointSet(samp->n + 1);

  for(int i = 0; i < samp->M; i++) {
    message m = samp->messages[i];
    if (m.type == "D") {
      if (samp->d[m.c1] != 0) {
        dset_same.unite(m.c2, samp->d[m.c1]);
      }
      if (samp->d[m.c2] != 0) {
        dset_same.unite(m.c1, samp->d[m.c2]);
      }
      samp->d[m.c1] = m.c2;
      samp->d[m.c2] = m.c1;
      dset_diff.unite(m.c1, m.c2);
    } else {
      if (dset_same.same(m.c1, m.c2)) {
        samp->res.push_back(SAME_GANG);
      } else if (dset_diff.same(m.c1, m.c2)) {
        samp->res.push_back(DIFF_GANG);
      } else {
        samp->res.push_back(NOT_SURE);
      }
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/disjoint-set/sample/find-catch.txt");

  sample * sampleTmp; 
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_msg("(A|D)\\s(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (sampleTmp && N >= 0 && boost::regex_match(s, result, pattern_msg)) {
      message m = {result[1], stringToInt(result[2]), stringToInt(result[3])};
      sampleTmp->messages.push_back(m);
      if (N++ == (sampleTmp->M - 1)) {
        N = -1;
        samples.push_back(*sampleTmp);
        delete sampleTmp;
      }
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      sampleTmp->n = stringToInt(result[1]);
      sampleTmp->M = stringToInt(result[2]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->n << " " << samp->M << endl;
  for(int i = 0; i < samp->M; i++) {
    message m = samp->messages[i];
    cout << m.type << " " << m.c1 << " " << m.c2 << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  vector<string> res = samp->res;
  for(vector<string>::iterator it = res.begin(); it != res.end(); it++) {
    cout << *it << endl;
  }
  cout << endl;
}

