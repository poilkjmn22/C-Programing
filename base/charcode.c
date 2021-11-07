#include <stdio.h>

int main(void) {
  char ch;
  
  printf("请输入一个字符：");
  scanf("%c", &ch);
  printf("the code for %c is %d\n", ch, ch);
  return 0;
}
