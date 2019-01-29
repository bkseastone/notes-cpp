#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::type_info;

class X { public: virtual void func1(void) {cout << "X::func1" << endl;} int m1[2];}; 
class XX : public X { public: void func1(void) override {cout << "XX::func1" << endl;} int m2;}; 
class Y {}; 
class YY : public Y {};

template<class T>
void printTypeInfo(const T *pT)
{
  cout << typeid(*pT).name() << endl;
}
 
int main()
{
  int n = 0;
  XX xx;
  YY yy;
  Y *py = &yy;
  // 1. when operand is statically-typed, `typeid` can deduce type information in compile time.
  // * type name
  cout << typeid(int).name() << endl; // i
  cout << typeid(XX).name() << endl; // 2XX
  // * build-in type variable name
  cout << typeid(n).name() << endl; // i
  cout << typeid(py).name() << endl; // P1Y
  // * object instance
  cout << typeid(xx).name() << endl; // 2XX
  cout << typeid(yy).name() << endl; // 2YY
  // * dereference of pointer to non-virtual-member object, which has no
  // polymorphism, and just truncats memory blocks statically.
  printTypeInfo<Y>(&yy); // 1Y
  // 2. when operand is dynamically-typed, `typeid` will deduce type information in run time by V-Table.
  // * dereference of pointer to virtual-member object, which has polymorphism.
  printTypeInfo<X>(&xx); // 2XX
  typedef long size_pointer;
  X *px = new X();
  size_pointer **v_table = (size_pointer **)px;
  cout << (*(type_info *)(v_table[0][-1])).name() << endl; // 1X
  delete px;
  px = new XX();
  v_table = (size_pointer **)px;
  cout << (*(type_info *)(v_table[0][-1])).name() << endl; // 2XX
  delete px;
  // * `dynamic_cast<T>(p)` provide safety downcast depending `type_info` information.
  // To be detailed, it will get `T`'s `type_info` statically, and `p`'s
  // `type_info` dynamically, and then campare&use them.
  class A { public: virtual void func(void) { cout << "A::func" << endl; } int m_a; };
  class B { int m_b; };
  class C : public A, public B { public: void func(void) override { cout << "C::func" << endl; } int m_c; };
  class D : public A, public B { public: void func(void) override { cout << "D::func" << endl; } int m_d; };
  C *pc = new C();
  A *p0 = dynamic_cast<A *>(pc);
  B *p1 = dynamic_cast<B *>(pc);
  D *pd = dynamic_cast<D *>(pc);
  cout << p0 << '\t' << p1 << '\t' << pc << '\t' << pd << endl;
  cout << ((long)p1 == (long)pc) << endl; // False, because of the memory-layout.
  cout << (p1 == pc) << endl; // True, `p1` is implicitly transformed to `C *` type
  delete pc;
  return 0;
}
