/* 
 * @Author: fangqi
 * @Date: 2021-11-17 11:33:30
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-17 11:33:30
 * @Description: POJ-2718
 * @O(n): n! * n
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

const int MAX_N = 100000000;

typedef pair<int, int> P;

struct tile {
  string digits;
  int perm[MAX_N];
  int count;
  bool used[MAX_N];
  int diff = MAX_N;
  P parts;
};

void processPerm(int, tile *);
P partialPerm(int, int, int *, char *);
void permutation1(int, int, tile *);
int stringToInt(string);
void printPerm(int *, int, char *);
void print_tile(tile *);
tile * loadSampleInputs();

int sampleCount;

int main() {
  tile * tiles = loadSampleInputs();
  for(int i =0; i< sampleCount; i++) {
    print_tile(tiles + i);

    permutation1(0, (*(tiles + i)).digits.length(), tiles + i);
    cout << "Output: " << (*(tiles + i)).diff 
      << "(" << tiles[i].parts.first << ", " << tiles[i].parts.second << ")" << endl
      << endl;
  }

  return 0;
}

P partialPerm(int n, int p, int * perm, string digits) {
  string part1;
  string part2;
  for(int i = 0; i < p; i++) {
    part1 += digits[perm[i]];
  }
  for(int j = p;j < n; j++) {
    part2 += digits[perm[j]];
  }

  if((p > 1 && part1[0] == '0') || (n - p > 1 && part2[0] == '0')) {
    return P(0,MAX_N);
  }
  return P(stringToInt(part1), stringToInt(part2));
}

void processPerm(int n, tile * t) {
  /* printPerm(perm, n, digits); */
  int mid = n / 2;
  for(int i = 1; i <= mid; i ++) { //只需要到中点就可以了，减少重复的配对
    P parts = partialPerm(n, i, t->perm, t->digits);
    int ndiff = abs(parts.first - parts.second);
    if (ndiff < t->diff) {
      t->diff = ndiff;
      t->parts = parts;
    }
  }
}

int stringToInt(string s) {
  stringstream sm;
  sm << s;
  int m;
  sm >> m;
  return m;
}

/* 生成0,1,2,...,n-1的全排列 */
void permutation1(int pos, int n, tile * t) {
  if (pos == n) {
    processPerm(n, t);
    return;
  }
  for(int i = 0; i < n; i++) {
    if(!t->used[i]) {
      t->perm[pos] = i;
      t->used[i] = true;
      permutation1(pos + 1, n, t);
      t->used[i] = false;
    }
  }
}

void printPerm(int * perm, int n, string digits) {
  string s;
  for(int i =0; i < n; i++) {
    s += digits[*(perm + i)];
  }
  cout << s << endl;
}

tile * loadSampleInputs() {
  ifstream fin;
  fin.open("./algorithms/dfs/sample/smallest-difference.txt");
  string s;
  regex patternDigits("(\\d\\s)+\\d");
  tile * tileTmp;
  tile *tiles = new tile[10000];
  while(getline(fin, s)) {
    if(s.empty()) {
      continue;
    }
    if(regex_match(s, patternDigits)) {
      tileTmp = new tile;
      for(int i = 0;i < s.length(); i++) {
        if(' ' != s[i]) {
          tileTmp->digits += s[i];
        }
      }
      tiles[sampleCount++] = *tileTmp;
    }
  }
  fin.close();
  return tiles;
}

void print_tile(tile * t) {
  cout << "Input: " ;
  cout << t->digits;
  cout << endl;
}

