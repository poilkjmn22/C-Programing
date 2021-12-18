/* 
 * @Author: fangqi
 * @Date: 2021-12-18 11:39:15
 * @LastEditors: fangqi
 * @LastEditTime: 2021-12-18 11:39:15
 * @Description: set
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <set>

using namespace std;

int main() {
  set<int> s;
  s.insert(3);
  s.insert(6);
  s.insert(1);
  s.insert(2);

  for(set<int>::iterator it = s.begin(); it != s.end(); it++) {
    cout << *it << " "; 
  }
  cout << endl;

  return 0;
}

