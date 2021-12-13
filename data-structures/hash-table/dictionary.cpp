/*
 * @Author: fangqi
 * @Date: 2021-12-12 16:24:20
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-12 16:24:20
 * @Description: 散列法- O（1）的时间内搜索出目标值
 * @Limitations: 1. 输入的字符串仅由A,C,G,T组成；2. 1 <= 字符串长度 <= 12; 3. 命令数 <= 1000000
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

const int M = 1046527;

struct command {
  string type;
  string str;
};

struct sample {
  int cmd_count; // 命令数
  command cmds[STRUCT_MAX_N];
  string H[M];
  vector<string> answers;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
int get_char(char);
int get_key(string);
int hash1(int);
int hash2(int);
int get_hash(int, int);
int find(string, sample * samp);
int insert(string, sample * samp);
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
  for(int i = 0; i < samp->cmd_count; i++) {
    command cmd = samp->cmds[i];
    if (cmd.type == "insert") {
      insert(cmd.str, samp);
    }else if (cmd.type == "find") {
      int f = find(cmd.str, samp);
      string ans = f ? "yes" : "no";
      samp->answers.push_back(ans);
    }
  }
}

// 字符转换为对应的数值
int get_char(char ch) {
  if (ch == 'A') {
    return 1;
  } else if (ch == 'C') {
    return 2;
  } else if (ch == 'G') {
    return 3;
  } else if (ch == 'T') {
    return 4;
  } else {
    return 0;
  }
}

// 将字符串生成为key
int get_key(string str) {
  long long sum = 0;
  long long p = 1;
  for(int i = 0; i < str.length(); i++) {
    sum += p * get_char(str[i]);
    p *= 5;
  }
  return sum;
}

int hash1(int key) {
  return key % M;
}

int hash2(int key) {
  return 1 + (key % (M - 1));
}

int get_hash(int key, int i) {
  return (hash1(key) + i * hash2(key)) % M;
}

int find(string str, sample * samp) {
  long long key, i, h;

  key = get_key(str);
  for(i = 0; ; i++) {
    h = get_hash(key, i);
    if (samp->H[h] == str) {
      return 1;
    } else if (samp->H[h].length() == 0) {
      return 0;
    }
  }
  return 0;
}

int insert(string str, sample * samp) {
  long long key, i, h;
  key = get_key(str);
  for(i = 0; ; i++) {
    h = get_hash(key, i); 
    if (samp->H[h] == str) { // 已有相同字符串的，忽略
      return 1;
    } else if (samp->H[h].size() == 0) {
      samp->H[h] = str;
      return 0;
    }
  }
  return 0;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/hash-table/sample/dictionary.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)");
  boost::regex pattern_line("(\\w+)\\s(\\w+)");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0 && boost::regex_match(s, result, pattern_line)) {
      samp->cmds[N] = {result[1], result[2]};
      if (N++ == (samp->cmd_count - 1)) {
        samples.push_back(*samp);
        delete samp;
      }
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->cmd_count = stringToInt(result[1]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  for(int i = 0; i < samp->cmd_count; i++) {
    command cmd = samp->cmds[i];
    cout << cmd.type << " " << cmd.str << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  for(vector<string>::iterator it = samp->answers.begin(); it != samp->answers.end(); it++) {
    cout << *it << endl; 
  }
}

