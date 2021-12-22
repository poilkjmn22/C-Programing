/* 
 * @Author: fangqi
 * @Date: 2021-12-22 14:06:13
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-22 14:06:13
 * @Description: POJ-2236
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
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

struct op {
  char type;
  int v1;
  int v2;
};

struct computer {
  int id;
  int x; // 
  int y; // 
};

struct sample {
  int n; // computers number 1, 2, ..., n
  int d; // maximum distance that computers can communicate
  vector<op> ops; // 操作指令
  vector<computer> rs; // 已经修好的电脑
  computer s[STRUCT_MAX_N + 1]; // 所有电脑
  vector<string> answers;
};

const string yes = "SUCCESS";
const string no = "FAIL";

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void conn_coms(op, sample *, DisjointSet &);
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
  DisjointSet dset_success = DisjointSet(samp->n + 1);

  for(vector<op>::iterator it = samp->ops.begin(); it != samp->ops.end(); it++) {
    op o = *it;
    if (o.type == 'O') {
      conn_coms(o, samp, dset_success);

      samp->rs.push_back(samp->s[o.v1]);
    } else if (o.type == 'S') {
      samp->answers.push_back(dset_success.same(o.v1, o.v2) ? yes : no);
    }
  }
}

void conn_coms(op o, sample * samp, DisjointSet &dset) {
  computer c = samp->s[o.v1];
  for(vector<computer>::iterator it = samp->rs.begin(); it != samp->rs.end(); it++) {
    computer ci = *it;
    if (sqrt(pow(c.x - ci.x, 2) + pow(c.y - ci.y, 2)) <= samp->d) {
      dset.unite(c.id, ci.id);
    }
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/disjoint-set/sample/wireless-network.txt");

  sample * samp; 
  boost::regex patternRC("(\\d+)\\s(\\d+)");
  boost::regex pattern_com("(\\d+)\\s(\\d+)");
  boost::regex pattern_op("(O|S)\\s(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  int N = 0;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    if (s == "0 0") {
      samples.push_back(*samp);
      delete samp;
      continue;
    }
    boost::smatch result;
    if (samp && N >= 1 && boost::regex_match(s, result, pattern_com)) {
      computer c = {N, stringToInt(result[1]), stringToInt(result[2])};
      samp->s[N] = c;
      if (N++ == samp->n) {
        N = 0;
      }
      continue;
    }
    if (samp && boost::regex_match(s, result, pattern_op, boost::match_extra)) {
      op o = {s[0], 0, 0};
      for(int i = 2; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          if (j == 0) {
            o.v1 = num;
          } else {
            o.v2 = num;
          }
        }
      }
      samp->ops.push_back(o);
      continue;
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->n = stringToInt(result[1]);
      samp->d = stringToInt(result[2]);
      N = 1;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl << samp->n << " " << samp->d << endl;
  for(int i = 1; i <= samp->n; i++) {
    computer c = samp->s[i];
    cout << c.x << " " << c.y << endl;
  }
  for(vector<op>::iterator it = samp->ops.begin(); it != samp->ops.end(); it++) {
    op o = *it;
    cout << o.type << " " << o.v1;
    if (o.type == 'S') {
      cout << " " << o.v2;
    }
    cout << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  for(vector<string>::iterator it = samp->answers.begin(); it != samp->answers.end(); it++) {
    cout << *it << endl;
  }
  cout << endl;
}

