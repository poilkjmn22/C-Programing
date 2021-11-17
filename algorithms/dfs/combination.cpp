/* 
 * @Author: fangqi
 * @Date: 2021-11-16 15:15:48
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-16 15:15:48
 * @Description: 组合
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <vector>

using namespace std;

int combinationCount(int, int);
vector<int> removeAt(vector<int>, int);
vector<vector<int>> combinations(vector<int>, int);
void printCombinations(vector<vector<int>>);

vector<int> sample = {1, 2, 3, 4, 5, 6, 7};

int main() {

  const int m  = 3;
  int comb = combinationCount(sample.size(), m);
  cout << comb << endl;

  vector<vector<int>> combs = combinations(sample, m);
  printCombinations(combs);

  return 0;
}

int combinationCount(int n, int m) {
  if (m == 1) {
    return n;
  }else if (m < 1) {
    return 1;
  }
  return n * combinationCount(n - 1, m - 1);
}

vector<vector<int>> combinations(vector<int> arr, int m) {
  vector<vector<int>> res;
  int n = arr.size();
  for(int i =0; i < n; i++) {
    if (m == 1) {
      vector<int> v_i;
      v_i.push_back(arr[i]);
      res.push_back(v_i);
      continue;
    }
    vector<vector<int>> lastRes = combinations(removeAt(arr, i), m - 1);

    vector<vector<int>>::iterator pd;
    for(pd = lastRes.begin(); pd != lastRes.end(); pd++) {
      vector<int> n_vi = {arr[i]};
      n_vi.insert(n_vi.begin() + 1, (*pd).begin(), (*pd).end());
      res.push_back(n_vi);
    }
  }

  return res;
}

vector<int> removeAt(vector<int> arr, int idx) {
  vector<int> new_vec;
  new_vec.insert(new_vec.begin(), arr.begin(), arr.begin() + idx);
  new_vec.insert(new_vec.end(), arr.begin()+ idx + 1, arr.end());
  return new_vec;
}

void printCombinations(vector<vector<int>> combs) {
    vector<vector<int>>::iterator pd;
    for(pd = combs.begin(); pd != combs.end(); pd++) {
      vector<int>::iterator pd1;
      for(pd1 = (*pd).begin(); pd1 != (*pd).end(); pd1++) {
        cout << (*pd1) << ",";
      }
      cout << endl;
    }
}

