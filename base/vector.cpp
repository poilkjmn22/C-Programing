/* 
 * @Author: fangqi
 * @Date: 2021-11-16 22:20:19
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-16 22:20:19
 * @Description: vector
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int>);
vector<int> removeAt(vector<int>, int);
void printVectorNest(vector<vector<int>>);

int main() {
  vector<int> vec;
  vec.push_back(9);
  vec.push_back(8);
  vec.push_back(7);

  printVector(vec);

  vector<int> vec1(3);
  vec1[0] = 1;
  vec1[1] = 2;
  vec1[2] = 3;
  printVector(vec1);

  vector<int> vec2 = removeAt(vec, 1);
  printVector(vec2);

  vector<int> vec3 = {4,5,6};
  printVector(vec3);

  vector<vector<int>> vecA;
  vecA.push_back(vec);
  vecA.push_back(vec1);
  vecA.push_back(vec3);
  printVectorNest(vecA);

  return 0;
}

void printVector(vector<int> vec) {
  /* vector<int>::iterator pd; */
  /* for(pd = vec.begin(); pd != vec.end(); pd++) { */
  /*   cout << *pd << ","; */
  /* } */
  /* cout << endl; */
}

void printVectorNest(vector<vector<int>> combs) {
    vector<vector<int>>::iterator pd;
    for(pd = combs.begin(); pd != combs.end(); pd++) {
      vector<int>::iterator pd1;
      for(pd1 = (*pd).begin(); pd1 != (*pd).end(); pd1++) {
        cout << (*pd1) << ",";
      }
      cout << endl;
    }
}

vector<int> removeAt(vector<int> arr, int idx) {
  vector<int> new_vec;
  new_vec.insert(new_vec.begin(), arr.begin(), arr.begin() + idx);
  new_vec.insert(new_vec.end(), arr.begin()+ idx + 1, arr.end());
  return new_vec;
}
