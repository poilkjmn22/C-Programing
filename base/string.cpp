/* 
 * @Author: fangqi
 * @Date: 2021-11-17 15:05:33
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-17 15:05:33
 * @Description: string
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_N = 100000000;

void printPerm(int *, int, char *);
int stringToInt(string);
int partialPerm(int, int);
void eachString(string);

char sample[6] = {'0', '1', '2', '4', '6', '7'};
int perm[6] = {4, 3, 1, 0, 2, 5};

int main() {
  /* printPerm(perm, 6, sample); */
  /* partialPerm(6, 5); */
  eachString("sdfshgsgsh");

  string s = "a bc";
  s += 'd';
  cout << (' ' == s[1]) << endl;
  s.erase(s.length() - 1);
  s += "ef";
  s = "";
  cout << s << endl;

  cout << stringToInt("000201") << endl;
  cout << atoi("000201") << endl;
  return 0;
}

void eachString(string str) {
  for(int i = 0; i < str.length(); i++) {
    char ch = str[i];
    cout << ch;
  }
  cout << endl;
}

void printPerm(int * perm, int n, char * sample) {
 string s;
  for(int i =0; i < n; i++) {
    s += *(sample + *(perm + i));
  }
  cout << s << endl;
}

int stringToInt(string s) {
  stringstream sm;
  sm << s;
  int m;
  sm >> m;
  return m;
}

int partialPerm(int n, int p) {
  string part1;
  string part2;
  for(int i = 0; i < p; i++) {
    part1 += sample[perm[i]];
  }
  for(int j = p;j < n; j++) {
    part2 += sample[perm[j]];
  }

  if((p > 1 && part1[0] == '0') || (n - p > 1 && part2[0] == '0')) {
    return MAX_N;
  }

  cout << part1 << ", " << part2 << endl;
  int part1Int = stringToInt(part1);
  int part2Int = stringToInt(part2);
  cout << part1Int << ", " << part2Int << endl;
  return abs(part1Int - part2Int);
}
