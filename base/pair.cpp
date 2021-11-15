#include <iostream>
/* #include <string> */
using namespace std;

typedef pair<int, int> P;

P funcReturnP();

int main() {
  /* pair<string, string> p; */
  /* p.first = "abc"; */
  /* p.second = "one"; */

  P p2(2, 4);

  /* cout << p.first << ", " << p.second << endl; */
  cout << p2.first << ", " << p2.second << endl;

  P p3 = funcReturnP();
  cout << p3.first << ", " << p3.second << endl;
  return 0;
}

P funcReturnP() {
  P p(3, 4);
  return p;
}
