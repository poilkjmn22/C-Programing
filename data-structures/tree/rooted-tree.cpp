/* 
 * @Author: fangqi
 * @Date: 2021-12-11 16:41:02
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-11 16:41:02
 * @Description: 有根树的表达。<使用左子右兄弟表达法>
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

struct line {
  int id;
  int k;
  vector<int> children;
};

struct tree {
  int p; // 父节点
  int l; // 最左侧的子节点
  int r; // 右侧紧邻的兄弟节点
};

struct sample {
  int node_count;
  line lines[STRUCT_MAX_N];
  tree T[STRUCT_MAX_N];
  int D[STRUCT_MAX_N]; // 树的深度
  int root;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
void get_root(sample *);
void set_depth(int, int, sample *);
void print_sample_output(sample *);
string get_node_type(int, sample *);
void print_children(int, sample *);

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
  for(int i = 0; i < samp->node_count; i++) {
    samp->T[i].p = NIL_NODE; 
    samp->T[i].l = NIL_NODE; 
    samp->T[i].r = NIL_NODE; 
  }

  for(int i = 0; i < samp->node_count; i++) {
    line l = samp->lines[i];
    int left = -1;

    for(int j = 0; j < l.children.size(); j++) {
      int node = l.children[j];
      if (j == 0) {
        samp->T[l.id].l = node;
      } else {
        samp->T[left].r = node;
      }
      left = node;
      samp->T[node].p = l.id;
    }
  }

  get_root(samp);

  set_depth(samp->root, 0, samp);
}

void get_root(sample * samp) {
  for(int i = 0; i < samp->node_count; i++) {
    if (samp->T[i].p == NIL_NODE) {
      samp->root = i;
      break;
    }
  }
}

void set_depth(int node,int depth, sample * samp) {
  samp->D[node] = depth;
  if (samp->T[node].l != NIL_NODE) {
    set_depth(samp->T[node].l, depth + 1, samp);
  }
  if (samp->T[node].r != NIL_NODE) {
    set_depth(samp->T[node].r, depth, samp);
  }
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/tree/sample/rooted-tree.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)");
  boost::regex pattern_line("(?:(\\d+)(?:\\s|$))+");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0 && boost::regex_match(s, result, pattern_line, boost::match_extra)) {
      line l;
      for(int i = 1; i < result.size(); i++) {
        int c_size = result.captures(i).size();
        for(int j = 0; j < c_size; ++j) {
          int num = stringToInt(result.captures(i)[j]);
          if (j == 0) {
            l.id = num;
          } else if (j == 1) {
            l.k = num;
          } else {
            l.children.push_back(num);
          }
        }
      }
      samp->lines[N] = l;
      if (N++ == (samp->node_count - 1)) {
        samples.push_back(*samp);
        delete samp;
      }
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->node_count = stringToInt(result[1]);
      samp->root = NIL_NODE;
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  for(int i = 0; i < samp->node_count; i++) {
    line l = samp->lines[i];
    cout << l.id << " " << l.k << " ";
    for(vector<int>::iterator it = l.children.begin(); it != l.children.end(); it++) {
      cout << *it << " ";
    }
    cout << endl;
  }
  cout << endl;
}

string get_node_type(int node, sample * samp) {
  tree t = samp->T[node];
  if (t.p == NIL_NODE) {
    return "root";
  }
  if (t.l == NIL_NODE) {
    return "leaf";
  }
  return "internal";
}

void print_children(int node, sample * samp) {
  cout << "[" ;
  int l = samp->T[node].l;
  if (l != NIL_NODE) {
    cout << l << ", ";
  } else {
    cout << "]";
    return;
  }
  int r = samp->T[l].r;
  while(r != NIL_NODE) {
    cout << r << ", ";
    r = samp->T[r].r;
  }
  cout << "]";
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  for(int i = 0; i < samp->node_count; i++) {
    tree t = samp->T[i];
    cout << "node " << i << ": ";
    cout << "parent = " << t.p << ", ";
    cout << "depth = " << samp->D[i] << ", ";
    cout << get_node_type(i, samp) << ", ";
    print_children(i, samp);
    cout << endl;
  }
}

