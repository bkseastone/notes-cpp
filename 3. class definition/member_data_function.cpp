#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class A {
 private:
  int mem_data1 = 23;
  const char *mem_data2 = "weisong";
  const int id;
  static int CNT;
 public:
  /*
      Static mem_fun hasn't access to communicate with members of objects.
      When call static mem_fun, don't pass object pointer.
      Bcz static mem_fun and static data member have the same namespace, we can directly use static
      members(here is CNT).
  */
  static void fun1(void) { cout << "static mem_fun" << endl;}
  // Const mem_fun can read but can't modify members of objects.
  // When call const mem_fun, pass a read-only object pointer(here is const A *this).
  void fun2(void) const { cout << mem_data2 << mem_data1 << endl;}
  // Normal mem_fun has all access.
  void fun3(int new_val) { mem_data1 = new_val; fun2();}
  A() : id(CNT++) { cout << "id" << id << ": I" << endl;}
  ~A() { cout << "id" << id << ": D" << endl;}

};
// this is initialization, above is decalaration, 
// all compilation will do is making a link after making memory-layout.
// And, initialization naturally need a type.
// And, permission control won't effect until initialization.
int A::CNT = 0;

int main(void)
{
  // when only want to use a func, we can make it like this.
  A::fun1(); 
  A a;
  a.fun1(); // just have a logical relationship.
  a.fun2();
  a.fun3(24);
  // cout << A::CNT << endl; // permission deny.
  return 0;
}
