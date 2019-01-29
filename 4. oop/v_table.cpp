#include <iostream>

using std::cout;
using std::cin;
using std::endl;

typedef void (*func_pointer)(void);
typedef long size_pointer;

class Base {
 public:
  virtual void func1(void) { cout << "Base::func1" << endl; }
  virtual void func2(void) { cout << "Base::func2" << endl; }
  virtual ~Base() { cout << "Base::D" << endl; }
};

class Derive1 : public Base {
 public:
  void func2(void) override { cout << "Derive1::func2" << endl; }
  ~Derive1() { cout << "Derive1::D" << endl; }
};

class Derive2 : public Base {
 public:
  void func2(void) override { cout << "Derive2::func2" << endl; }
  virtual void func3(void) { cout << "Derive2::func3" << endl; }
  ~Derive2() { cout << "Derive2::D" << endl; }
};

/*  [reference-blog](https://bkseastone.github.io/2018/09/06/cpp%E2%80%94%E2%80%94%E5%9F%BA%E7%A1%80/#%E5%A4%9A%E6%80%81%E7%9A%84%E5%AE%9E%E7%8E%B0%E7%BB%86%E8%8A%82%E8%99%9A%E5%87%BD%E6%95%B0%E8%A1%A8)
 *  [reference-doc](https://itanium-cxx-abi.github.io/cxx-abi/abi.html#vtable)
 *
 *  |V-Table(Base)|V-Table(Derive1)|V-Table(Derive2)|
 *  |:----:       |:----:          |:----:          |
 *  |func1        |func1           |func1           |
 *  |func2        |func2(override) |func2(override) |
 *  |~Base        |~Derive1(override)|~Derive2(override)|
 *  |~Base        |~Derive1(override)|~Derive2(override)|
 *  |             |                |func3           |
 *
 *  [note]: the entries for virtual destructors is a pair of entries, the
 *  1th-destructor(complete object destructor) performs the destruction 
 *  without delete(), so object still exists on the stack; the
 *  2th-destructor(deleting destructor) calls delete() after performing
 *  the destruction, so object not exists on the stack any longer.
 */
int main(void)
{
  Base *a0 = new Base();
  size_pointer **v_table =(size_pointer **)a0;
  func_pointer p = NULL;
  cout << "1. detail of V-Table" << endl;
  cout << "sizeof(Base) = " << sizeof(*a0) << endl; // all of a0 has is only a pointer to V-Table
  cout << "Base's address: " << a0 << endl;
  cout << "Base's V-Table address: " << v_table[0] << endl;
  cout << "V-Table 1th-el: " << (long *)v_table[0][0] << endl;
  delete a0;
  cout << "2. detail of virtual func invoke" << endl;
  a0 = new Derive1();
  a0->func2(); 
  v_table = (size_pointer **)a0;
  p = (func_pointer)v_table[0][1];
  p();
  delete a0;
  cout << "3. magic operation(Base pointer invoke Derive function)" << endl;
  a0 = new Derive2();
  //a0->func3(); // error: class Base has no member named 'func3', BUT, you can do this:
  v_table = (size_pointer **)a0;
  p = (func_pointer)v_table[0][4];
  p();
  cout << "--" << endl;
  delete a0;
  return 0;
}
