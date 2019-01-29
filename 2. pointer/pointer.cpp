#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

int max(int a, int b) { return a>b?a:b; }
int min(int a, int b) { return a<b?a:b; }
int add(int a, int b) { return a+b; }
void test(int (*p)(int, int), int a, int b)
{ 
  int c = (*p)(a, b);
  printf("a=%d, b=%d, result=%d\n", a, b, c);
}

int main(void)
{
  // function pointer
  // 1. the most commonly used use is to pass a function as a parameter.
  // 2. 异步操作的回调和其他需要匿名回调的结构
  test(&max, 3, 5);
  test(add, 3, 5);
  // an array/pointer case.
  int a1[2][2] = {{1,2},
                  {3,4}};
  int *a1_vector = a1[0];
  cout << "matrix to vector: " << a1_vector[2] << endl; // 3
  return 0;
}
