#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

class A {
 public:
  A() { m_a = 1; m_b = 2;}
  ~A() {}
  void func(void) { cout << "A: " << m_a << ", " << m_b << ", " << endl;}
  void func2(void) { cout << "the size of this instance of class A is: " << sizeof(*this) << endl;}
 private:
  int m_a, m_b;
};

class B {
 public:
  B() { m_c = 3;}
  ~B() {}
  void func(void) { cout << "B: " << m_c << endl;}
  void func2(void) { cout << "the size of this instance of class B is: " << sizeof(*this) << endl;}
 private:
  int m_c;
};

int main(void)
{
  // memory deploy 
  // 1. data member is a stack-var, mem_func is a code-block which is not a part
  // of the object. so, call a mem_func depend on the object type, while call a
  // data member depend on offset based on the object address.
  // 2. `malloc/free` is a function, compiler can't attatch constructor/destructor
  // task to it, so we need an operator that can controled by compiler, that is
  // `new/delete`.
  A *a = new A();
  a->func2(); //sizeof(A()): 8
  B *b = new B();
  b->func2(); //sizeof(B()): 4
  delete b;
  b = (B *)a;
  b->func(); // B: 1
  // mem_func and * this determined by the type of caller, data member
  // determined by the runtime value in the memory.
  b->func2(); //sizeof(B()): 4
  delete a;
  b = new B();
  a = (A *)b;
  a->func(); // A: 3, 21899(a rand number),
  delete b;
  b = 0; a = 0;
  return 0;
}
