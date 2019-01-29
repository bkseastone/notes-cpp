#include <iostream>
#include <stdio.h>

#include "util.h"

using std::cout;
using std::cin;
using std::endl;

int main(void)
{
  int i = i; // same to `int i;`
  i = (23==23); // bool is converted to int
  std::cout << i << std::endl; // 1
  // prior: `++a` > compare(`>=<!`) > logic(`&&||`) > `a++`.
  // NOTICE: `a++` means execute add until the whole statement executed, even
  // if `()` used.
  int a = i>=1 && (i++)>=2;
  std::cout << a << ", " << i << std::endl; // 0, 2
  // `&&` can be used for if logic.
  i = (a>=1 && !i++);
  std::cout << a << ", " << i << std::endl; // 0, 0
  // the order of `,` is from right to left.
  printf("%d, %d\n", i, ++i); // 1, 1
  // float(4*8 bits) 1.0 representation in memory:
  // 0(1-bit sign) 01111111(8-bits exponential offset) 0...0(23-bits mantissa),
  // expressed in hex is 0x3f800000, in dec is 1065353216.
  // `(int)` operation make explicit convertion, `(int&)` operation just
  // re-explate the raw data.
  float a1=1.0f;
  cout << (int)a1 << ", " << (int&)a1 << ", " << &a1 << endl;
  // little-endian(LSB->MSB lie in 0x00->0xFF) VS big-endian.
  unsigned short a2 = 0x2018;
  char a2_c = (char)a2;
  char *a2_c_p = (char *)&a2;
  printf("%04x, %04x, %04x\n", a2, a2_c, *(unsigned short *)a2_c_p); // 2018, 18, 2018
  // when calculate, as long as the width < sizeof(int), it will be lifted to int type.
  unsigned char a3 = 0xFF;
  unsigned char a3_m = ~a3>>2;
  printf("%02x, %02x\n", ~a3, a3_m); // ffffff00, c0
  // when increase the data width, unsigned pad 0, signed pad symbolic bit.
  unsigned char a4_u = -1;
  signed char a4_s = -1;
  printf("%08x, %08x\n", (unsigned)a4_u, (int)a4_u); // 000000ff, 000000ff
  printf("%08x, %08x\n", (unsigned)a4_s, (int)a4_s); // ffffffff, ffffffff

  return 0;
}
