/* 
 * @Author: fangqi
 * @Date: 2021-11-17 09:08:27
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-17 09:08:34
 * @Description: 生成全排列
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <vector>

using namespace std;

int permutationCount(int);
vector<int> removeAt(vector<int>, int);
vector<vector<int>> permutations(vector<int>);
void printPermutations(vector<vector<int>>);

vector<int> sample = {1, 2, 3, 4, 5, 6, 7};

int main() {

  int permCount = permutationCount(sample.size());
  cout << permCount << endl;

  vector<vector<int>> perms = permutations(sample);
  printPermutations(perms);

  return 0;
}

int permutationCount(int n) {
  if (n <= 1) {
    return 1;
  }
  return n * permutationCount(n - 1);
}

vector<vector<int>> permutations(vector<int> arr) {
  vector<vector<int>> res;
  int n = arr.size();
  if (n <= 1) {
    vector<int> v_i;
    v_i.push_back(arr[0]);
    res.push_back(v_i);
    return res;
  }
  for(int i =0; i < n; i++) {
    vector<vector<int>> lastRes = permutations(removeAt(arr, i));

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

void printPermutations(vector<vector<int>> perms) {
    int count = 0;
    vector<vector<int>>::iterator pd;
    for(pd = perms.begin(); pd != perms.end(); pd++) {
      vector<int>::iterator pd1;
      for(pd1 = (*pd).begin(); pd1 != (*pd).end(); pd1++) {
        cout << (*pd1) << ",";
      }
      cout << endl;
      count ++;
    }
    cout << count << endl;
}

