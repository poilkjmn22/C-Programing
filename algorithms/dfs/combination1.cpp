/* 
 * @Author: fangqi
 * @Date: 2021-11-17 10:54:55
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-17 10:55:06
 * @Description: 生成组合(使用数组，不使用vector的实现)
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>

using namespace std;

void combination1(int, int, int);
void print_comb(int *, int, int *);

const int MAX_N = 100000000;

bool used[MAX_N];
int comb[MAX_N];

int sample[7] = {1, 2,3, 4,5, 6, 7};

int count = 0;

int main() {
  combination1(0, 7, 3);

  cout << count << endl;
  return 0;
}

/* 生成0,1,2,...,n-1|m 的组合 */
void combination1(int pos, int n, int m) {
  if (pos == m) {
    print_comb(comb, m, sample);
    count++;
    return;
  }
  for(int i = 0; i < n; i++) {
    if(!used[i]) {
      comb[pos] = i;
      used[i] = true;
      combination1(pos + 1, n, m);
      used[i] = false;
    }
  }
}

void print_comb(int * comb, int m, int * sample) {
  for(int i = 0; i < m; i++) {
    cout << *(sample + *(comb + i)) << ",";
  }
  cout << endl;
}
