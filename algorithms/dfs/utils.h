/* 
 * @Author: fangqi
 * @Date: 2021-11-18 23:20:15
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-18 23:20:15
 *  @Description: 工具类函数
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */
#ifndef UTILS_H_
#define UTILS_H_

#include <sstream>
#include <string>

int stringToInt(std::string);
int charToInt(char);

#define MAX_N 100000000

#define STRUCT_MAX_N 1000
#define STRUCT_MAX_M 1000

#define MAX_SAMPLE 100

int stringToInt(std::string s) {
  std::stringstream sm;
  sm << s;
  int m;
  sm >> m;
  return m;
}

int charToInt(char ch) {
  std::string s;
  s += ch;
  std::stringstream sm;
  sm << s;
  int m;
  sm >> m;
  return m;
}

int comb[MAX_N];
bool used[MAX_N];

void combination1(int pos, int n, int m, void (*process_comb)(int *, int)) {
  if (pos == m) {
    process_comb(comb, m);
    return;
  }
  for(int i = 0; i < n; i++) {
    if(!used[i]) {
      comb[pos] = i;
      used[i] = true;
      combination1(pos + 1, n, m, process_comb);
      used[i] = false;
    }
  }
}

#endif
