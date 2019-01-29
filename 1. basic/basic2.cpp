#include <iostream>
#include <stdio.h>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

// When declare, usually it can be a inner link(means must init meanwhile declare)
// or a outer link(means can init in other places/time), if use `extren` to decorate,
// it will be a explicit outer link. Such as `class A;` is an implicit outer
// link.
// forward declaration only can be used for the defination of pointer or
// reference, can not used to define an object(inherit is invalid too). 
//class A; // can not be used here.
class A{};
class B : public A {};
class C : public virtual A {};

template <class T> void swap(T, T);

int main(void)
{
  // the result of `sizeof` will be calculated during compilation, so:
  // 1. it can be used to define the array dimension;
  // 2. it can't calculate the size of dynamically allocated array or the size
  // of extern array;
  // 3. usually, used for memory allocation.

  // data alignment
  // 1. default: the struct start address is aligned by GCC automaticaly, and
  // its each element is aligned according to the longest-type variable's size.
  // Thereby, CPU can get some a element by just reading once.
  // 2. custom: `#pragma pack(n)`, set a limit on the default align method.
  struct MyStruct1 { char dda; int type; char dda2; }; 
  struct MyStruct2 { double dda1; int i; char dda; char dda2; }; 
  struct MyStruct3 { double dda1; int i; }; 
#pragma pack(2)
  struct MyStruct4 { char dda; int type; char dda2; }; 
#pragma pack(8)
  struct MyStruct5 { char dda; int type; char dda2; }; 
  cout << "sizeof(MyStruct1)" << sizeof(MyStruct1)          //12
       << "sizeof(MyStruct2)" << sizeof(MyStruct2)          //16
       << "sizefo(MyStruct3)" << sizeof(MyStruct3) << endl  //16
       << "sizefo(MyStruct4)" << sizeof(MyStruct4)          //8
       << "sizefo(MyStruct5)" << sizeof(MyStruct5) << endl; //12
  // the size of empty class or empty class inheriting empty class is all 1 byte.
  // but, when involved virtual inheriting, the size is 8 bytes(64bits OS),
  // because of virtual table(pointer).
  cout << sizeof(A) << "," << sizeof(B) << "," << sizeof(C) << endl;
  // the operand of sizeof won't be compiled, it just be substituted for a type
  // key.
  int a = 5;
  cout << sizeof(++a) << ", " << a <<  endl;

  int b = 10;
  swap<int&>(b, a);
  cout << b << a << endl;
  return 0;
}

// `inline` must be used in the defination of function, not declaration.
template <class T>
inline void swap(T a, T b) {
  char tempbuf[10];
  memcpy(tempbuf, &a, sizeof(a));
  memcpy(&a, &b, sizeof(b));
  memcpy(&b, &tempbuf, sizeof(a));
}
