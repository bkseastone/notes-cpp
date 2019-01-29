# basics

## basic1

### assignment

`int i = i;` same to `int i;`

### operator prior

prior: `++a` > compare(`>=<!`) > logic(`&&||`) > `a++`.

NOTICE: `a++` means execute add until the whole statement executed, even if `()` used.

`&&` can be used for if logic.

the order of `,` is from right to left.

### type convertion

bool convert to int is 0/1.

float(4 * 8 bits) 1.0 representation in memory:
`0`(1-bit sign) `01111111`(8-bits exponential offset) `0...0`(23-bits mantissa), expressed in hex is `0x3f800000`, in dec is `1065353216`.

`(int)` operation make explicit convertion, `(int&)` operation just `(int)` operation make explicit convertion, `(int&)` operation just re-explate the raw data.

little-endian(LSB->MSB lies in 0x00->0xFF) VS big-endian.

when calculate, as long as the width < sizeof(int), it will be lifted to int type.

when increase the data width, unsigned pad 0, signed pad symbolic bit.

## basic2

### decalration

When declare, usually it can be a inner link(means must init meanwhile declare) or a outer link(means can init in other places/time), if use `extern` to decorate, it will be a explicit outer link. Such as `class A;` is an implicit outer link.
Forward declaration(an outer link impletation) can only be used for the defination of pointer or reference, can not used to define an object(inherit is invalid too)(because need memory-layout when define an object).

### `sizeof`

the result of `sizeof` shall be calculated during compilation, so:

1. it can be used to define the array dimension;

2. it can't calculate the size of dynamically allocated array or the size of extern array;

3. usually, used for memory allocation;

4. the operand of sizeof won't be compiled, it just be substituted for a type key.

### data alignment

WHY: On hardware, one address accords to 4/8 bytes data(depending on data bus and OS). If data(4 bytes) is not aligned, CPU has to read twice to get the data. Thereby, alignment can improve efficient.

1. default: the struct start address is aligned by GCC automaticaly, and its each element is aligned according to the longest-type variable's size.
Thereby, CPU can get some a element by just reading once.

2. custom: `#pragma pack(n)`, set a limit on the default align method.

The size of empty class or empty class inheriting empty class is all 1 byte. 
But, when involved virtual inheriting, the size is 8 bytes(64bits OS), because of virtual table(pointer).

### `const`/`define` AND `inline`/`define`

1. `const` var will be execut type check, is more safe than `define`, which just makes substitution.

2. `inline` is more safe too, due to type check. 
NOTITION: `inline` must be used in the defination of function, not declaration.
Because declaration is used to provide link interface and type check, while defination is used to deploy.
