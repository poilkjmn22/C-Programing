/* 
 * @Author: fangqi
 * @Date: 2021-11-16 15:34:06
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-16 15:34:06
 * @Description: 数组
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <array>

using namespace std;

int * removeItem(int *, int, int);
void printArray(int *, int);

int main() {
  array<int, 3> arr = {1,2,3};
  printArray(arr.data(), arr.size());

  int * arr2 = removeItem(arr.data(), arr.size(), 2);
  printArray(arr2, arr.size() - 1);

  return 0;
}

void printArray(int * arr, int arrSize) {
  for(int i =0; i < arrSize; i++) {
    cout << *(arr+i) << ", ";
  }
  cout << endl;
}

int * removeItem(int * arr,int arrSize, int idx) {
  int * res = new int[arrSize - 1];
  for(int i =0; i < arrSize; i++) {
    if (i < idx) {
      *(res + i) = *(arr+i);
    }else if (i > idx) {
      *(res+i - 1) = *(arr+i);
    }
  }
  return res;
}
