/* 
 * @Author: fangqi
 * @Date: 2021-11-17 09:49:23
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-17 09:49:23
 * @Description: 生成全排列(使用数组，不使用vector的实现)
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>

using namespace std;

void permutation1(int, int);
void printPerm(int *, int, int *);

const int MAX_N = 100000000;

bool used[MAX_N];
int perm[MAX_N];

int sample[7] = {1, 2,3, 4,5, 6, 7};

int exec_count = 0;

int main() {
  permutation1(0, 7);

  cout << exec_count << endl;
  return 0;
}

/* 生成0,1,2,...,n-1的全排列 */
void permutation1(int pos, int n) {
  if (pos == n) {
    printPerm(perm, n, sample);
    exec_count++;
    return;
  }
  for(int i = 0; i < n; i++) {
    if(!used[i]) {
      perm[pos] = i;
      used[i] = true;
      permutation1(pos + 1, n);
      used[i] = false;
    }
  }
}

void printPerm(int * perm, int n, int * sample) {
  for(int i = 0; i < n; i++) {
    cout << *(sample + *(perm + i)) << ",";
  }
  cout << endl;
}
