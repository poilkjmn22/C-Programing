#include <queue>
#include <cstdio>

using namespace std;

int main() {
  queue<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  
  printf("%d\n", s.front());
  s.pop();

  printf("%d\n", s.front());
  s.pop();

  printf("%d\n", s.front());
  s.pop();

  return 0;
}
