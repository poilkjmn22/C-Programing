/* 
 * @Author: fangqi
 * @Date: 2021-11-18 16:57:50
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-18 16:57:50
 * @Description: AOJ-0525
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include "utils.h"

using namespace std;

struct sample{
  int N;
  int M;
  int jianbing[STRUCT_MAX_N][STRUCT_MAX_M + 1];
  int maxCountGood;
};
int sampleCount = 0;

sample * loadSampleInputs();
void printSampleInput(sample *);
void printSampleOutput(sample *);
void process_sample(sample *);
void dfs(int, int, sample *, bool);
void reverseRow(int, sample *);
void reverseColumn(int, sample *);
int calcGoodCount(sample *);

int main() {
  sample * samples = loadSampleInputs();
  for(int i =0; i < sampleCount; i++) {
    printSampleInput(samples + i);
    process_sample(samples + i);
    printSampleOutput(samples + i);
  }

  return 0;
}

sample * loadSampleInputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/jianbing.txt");

  sample * sampleTmp; 
  regex patternRC("(\\d+)\\s(\\d+)");
  match_results<string::const_iterator> result;
  int N = -1;
  sample * samples = new sample[MAX_SAMPLE];

  string s;
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    if (( sampleTmp ) && N >= 0 && N < ( *sampleTmp ).N) {
      int k = 0;
      for(int i = 0;i < s.length(); i++) {
        if(' ' != s[i]) {
            ( *sampleTmp ).jianbing[N][k++] = charToInt(s[i]);
        }
      }
      if(N++ == (sampleTmp->N - 1)) {
        samples[sampleCount++] = *sampleTmp;
        delete sampleTmp;
        N = -1;
      }
    }
    if(regex_match(s, result, patternRC)) {
      sampleTmp = new sample;
      int nN = stringToInt(result[1]);
      int nM = stringToInt(result[2]);
      sampleTmp->N = nN;
      sampleTmp->M = nM;
      sampleTmp->maxCountGood = 0;
      if(sampleTmp->N == 0) {
        delete sampleTmp;
      }
      N = 0;
    }
  }
  fin.close();

  return samples;
}

void printSampleInput(sample * s) {
  cout << "Input: " << endl;
  cout << s->N << " " << s->M << endl;
  for(int i = 0; i< s->N; i ++) {
    for(int j = 0; j< s->M; j ++) {
      cout << s->jianbing[i][j] << " ";
    }
    cout << endl;
  }
}

void printSampleOutput(sample * samp) {
  cout << "Output: "
    << samp->maxCountGood << endl
    << endl;
}

void process_sample(sample * samp) {
  samp->maxCountGood = calcGoodCount(samp);
  dfs(0, 0, samp, 0);
}

void dfs(int i, int j, sample * samp, bool isColumn) {
  if(i >= samp->N || j >= samp->M) {
    return ;
  }
  dfs(i + 1, j, samp, 0);
  dfs(i, j + 1, samp, 1);

  bool isFirst = (i == 0 && j == 0);

  if (isFirst) {
    reverseRow(i, samp);
    samp->maxCountGood = max(samp->maxCountGood, calcGoodCount(samp));
    dfs(i + 1, j, samp, 0);
    dfs(i, j + 1, samp, 1);
    reverseRow(i, samp);

    reverseColumn(j, samp);
    samp->maxCountGood = max(samp->maxCountGood, calcGoodCount(samp));
    dfs(i + 1, j, samp, 0);
    dfs(i, j + 1, samp, 1);
    reverseColumn(j, samp);

    reverseRow(i, samp);
    reverseColumn(j, samp);
    samp->maxCountGood = max(samp->maxCountGood, calcGoodCount(samp));
    dfs(i + 1, j, samp, 0);
    dfs(i, j + 1, samp, 1);
    reverseRow(i, samp);
    reverseColumn(j, samp);
  }else {
    if (isColumn) {
      reverseRow(i, samp);
      samp->maxCountGood = max(samp->maxCountGood, calcGoodCount(samp));
      dfs(i + 1, j, samp, 0);
      dfs(i, j + 1, samp, 1);
      reverseRow(i, samp);
    }else {
      reverseColumn(j, samp);
      samp->maxCountGood = max(samp->maxCountGood, calcGoodCount(samp));
      dfs(i + 1, j, samp, 0);
      dfs(i, j + 1, samp, 1);
      reverseColumn(j, samp);
    }
  }
}

void reverseRow(int r, sample * samp) {
  for(int i =0; i< samp->M; i++) {
    samp->jianbing[r][i] = 1 - samp->jianbing[r][i];
  }
}

void reverseColumn(int c, sample * samp) {
  for(int i =0; i< samp->N; i++) {
    samp->jianbing[i][c] = 1 - samp->jianbing[i][c];
  }
}

int calcGoodCount(sample * samp) {
  int count = 0;
  for(int i =0; i < samp->N; i++) {
    for(int j =0; j < samp->M; j++) {
      if (!samp->jianbing[i][j]) {
        count += 1;
      }
    }
  }
  return count;
}

