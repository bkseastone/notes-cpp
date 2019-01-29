#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/* 1. use struct to save params, use class to make objects and communicate, use
 *  inbuild-type variable to associate in local.
 * */
struct C_struct {
  int a[10];
};
namespace main_func_needed_data {
const struct C_struct c1 = {
  .a={0,1,2,3,4,5,6,7,8,9},
};
}
namespace mfnd = main_func_needed_data;

class A {
 private:
  const int id;
  static int CNT;
  int mem_i;
 public:
  A() : id(CNT++), mem_i(0) { cout << "A-id" << id << ": " << mem_i << endl;}
  A(int i) : id(CNT++), mem_i(i) { cout << "A-id" << id << ": " << mem_i << endl;}
  A& operator=(const A& a) { mem_i = a.mem_i;}
  ~A() {cout << "A-id" << id << ": free" << mem_i << endl;}
};
int A::CNT = 0;

class B {
 private:
  /* 
     if need a class-type member, there are 2 methods to solve twice
     construction process:
     1. use initial list, rather than re-assign it a value in construct function
       block.
     2(feature). use a pointer not a object, thereby it is same to a
       inbuild-type member, and there is no difference between initial and
       re-assign.
     totally, initial list should just be used for const variables, things
     of construction should be constructor's responsibility.
  */
  A mem_a;
  //A *mem_a;
 public:
  B() {}
  B(int size) { mem_a = A(size); }
  //B(int size) { mem_a = new A(size); }
  ~B() {}
  //~B() {delete mem_a;}
};

int main(void)
{
  // explicit invoke which constructor, rather than using B b; 
  B *b = new B();
  delete b;
  B *b2 = new B(mfnd::c1.a[9]);
  delete b2;
  return 0;
}
