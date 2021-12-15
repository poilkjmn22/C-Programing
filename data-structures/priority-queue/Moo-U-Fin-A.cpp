/* 
 * @Author: fangqi
 * @Date: 2021-12-13 16:30:34
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-13 16:30:34
 * @Description: POJ-2010
 * @Limitations: 1 <= N <= 19,999, N <= C <= 100,000, 0 <= F <= 20,000,000,000
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <regex>
#include "utils.h"
#include <boost/regex.hpp>

using namespace std;

struct calve {
  int score; // 学分
  int fin_aid; // 所需的补助金
};

struct comparison_calve_fin {
  bool operator () (calve c1, calve c2) {
    return c1.fin_aid > c2.fin_aid;
  }
};

struct sample {
  int N; // classrooms 的数量
  int C; // claves 的数量
  int F; // 总金额
  calve calves[STRUCT_MAX_N];
  calve admit_calves[STRUCT_MAX_N];
  int used_fin;
  int max_mid_score;
};

vector<sample> load_sample_inputs();
void print_sample_input(sample *);
void process_sample(sample *);
bool compare_calve_score(calve, calve);
void update_mid_score(calve, sample *);
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
  priority_queue<calve, vector<calve>, comparison_calve_fin> pque;
  for(int i = 0; i < samp->C; i++) {
    pque.push(samp->calves[i]);
  }

  int admit_count = 0;
  // 最少金额
  while(!pque.empty()) {
    calve c = pque.top();
    pque.pop();

    samp->admit_calves[admit_count++] = c;
    samp->used_fin += c.fin_aid;
    if (admit_count == samp->N) {
      break;
    }
  }

  // 分数排序
  sort(samp->admit_calves, samp->admit_calves + samp->N, compare_calve_score);

  // 扫描剩下的可选的项，使分数中位数最大
  while(!pque.empty()) {
    calve c = pque.top();
    pque.pop();
    
    calve mc = samp->admit_calves[samp->N / 2];
    if ((samp->used_fin - mc.fin_aid + c.fin_aid) > samp->F) {
      break;
    }
    if (c.score > mc.score) {
      samp->used_fin = samp->used_fin - mc.fin_aid + c.fin_aid;
      update_mid_score(c, samp);
    }
  }

  samp->max_mid_score = samp->admit_calves[samp->N / 2].score;
}

void update_mid_score(calve c, sample * samp) {
  samp->admit_calves[samp->N / 2] = c;
  for(int i = ((samp->N / 2) - 1); i >= 0; i--) {
    if (c.score > samp->admit_calves[i].score) {
      samp->admit_calves[i] = c;
      samp->admit_calves[i + 1] = samp->admit_calves[i];
    } else {
      break;
    }
  }
}

bool compare_calve_score(calve c1, calve c2) {
  return c1.score > c2.score;
}

vector<sample> load_sample_inputs() {
  ifstream fin;
  fin.open("./data-structures/priority-queue/sample/Moo-U-Fin-A.txt");

  sample * samp;
  boost::regex patternRC("(\\d+)\\s(\\d+)\\s(\\d+)");
  boost::regex pattern_calve("(\\d+)\\s(\\d+)");
  vector<sample> samples;
  int N = -1;

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    boost::smatch result;
    if (samp && N >= 0 && boost::regex_match(s, result, pattern_calve)) {
      calve c = {stringToInt(result[1]), stringToInt(result[2])};
      samp->calves[N] = c;
      if (N++ == (samp->C - 1)) {
        N = -1;
        samples.push_back(*samp);
        delete samp;
      }
    }
    if (boost::regex_match(s, result, patternRC)) {
      samp = new sample;
      samp->N = stringToInt(result[1]);
      samp->C = stringToInt(result[2]);
      samp->F = stringToInt(result[3]);
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void print_sample_input(sample * samp) {
  cout << "Input: " << endl;
  cout << samp->N << " " << samp->C << " " << samp->F << endl;
  for(int i = 0; i < samp->C; i++) {
    calve c = samp->calves[i];
    cout << c.score << " " << c.fin_aid << endl;
  }
}

void print_sample_output(sample * samp) {
  cout << "Output: " << endl;
  cout << samp->max_mid_score << endl;
  cout << "details: ";
  for(int i = 0; i < samp->N; i++) {
    cout << samp->admit_calves[i].score << " " << samp->admit_calves[i].fin_aid << ", "; 
  }
  cout << "used_fin: " << samp->used_fin << endl;
  cout << endl;
}

