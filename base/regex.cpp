/* 
 * @Author: fangqi
 * @Date: 2021-11-15 14:34:35
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-15 14:34:35
 * @Description: regex
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */

#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(void) {
  regex patternCheese("^[1-9]$");
  match_results<string::const_iterator> result;
  char ch = '9';
  string s(1, ch );
  regex_match(s, result, patternCheese);
  cout << result[0] << endl;

  regex patternRC("(\\d+)\\s(\\d+)");
  match_results<string::const_iterator> result1;
  string s1 = "2 5";
  regex_match(s1, result1, patternRC);
  cout << result1[1] << endl;

  return 0;
}
