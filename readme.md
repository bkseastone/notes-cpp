# [link library](https://blog.csdn.net/ztf312/article/details/77258048)

1. [create static link library](https://www.cnblogs.com/alan666/p/8311984.html)

2. create dynamic link library

# basic

## declaration

normally, declaration is initialization in statically-typed, exclude:

* explicit outer link : use `extern` to decorate
* implicit outer link : such as Forward declaration `class A;` 
  * Forward declaration can only be used for the definition of pointer or reference
  * Forward declaration can not be used to define an object(inherit is invalid too), because need memory-layout when define an object

## sizeof

the result of `sizeof` shall be calculated during compilation, so:

1. can be used to define the array dimension
2. can't calculate the size of dynamically allocated array or the size of extern array

usually, used for memory allocation. Note that the operand of sizeof won't be compiled, it just be substituted for a type key.

## data alignment

WHY: On hardware, one address accords to 4/8 bytes data(depending on data bus and OS). If data(such as 4 bytes) is not aligned, CPU has to read twice to get the data. Thereby, alignment can improve efficiency.

1. default: each element is aligned according to the **longest**-type variable's size

2. custom: `#pragma pack(n)`, set a up-limit on the default

The size of empty class or empty class inheriting empty class is all 1 byte. 
But, when involved virtual inheriting, the size is 8 bytes(64-bits OS), because of virtual table(pointer).

## operator prior

`++a`  **>**  COMPARE(`>=<!`)  **>**  LOGIC(`&&||`)  **>**  `a++`

*NOTICE: `a++` means execute add until the whole statement(exclude `=`) executed, even if `()` used.*

## type conversion

1. bool convert to int is 0/1

2. `(int)` operation make explicit conversion, `(int&)` operation just re-explain the raw data
3. when calculate, as long as the width < sizeof(int), it will be lifted to int type
4. when increase the data width, `unsigned` pad 0, `signed` pad symbolic bit

## const / define AND inline / define

1. `const` var will execute type check, is more safe than `define`, which is just substitution
2. `inline` is more safe too, due to type check

*NOTE: `inline` must be used in the definition of function, not declaration.*
*Because declaration is used to provide **link interface and type check**, while definition is used to **deploy**.*

## misc

1. `&&` can be used for if logic.

2. the order of `,` is from right to left.

3. little-endian(LSB->MSB lies in 0x00->0xFF) VS big-endian

# pointer

## function pointer

implement callback function.

featured code:

```c++
void (*pfunc)(void) = &func; // explicitly suggest this is a function pointer
pfunc(); // uniform function invoke form
```

In order to solve the problem of adjusting the address of class instances caused by multi-inheritance and virtual inheritance of C++, class member function pointer must be passed in class instance object when calling.

```c++
void (A::*pfunc)(void) = &A::func;
A a0 = new A();
(a0->*pfunc)();  //调用时必须要加类的对象名和*符号
```

## array pointer

implement 2-dim matrix to vector by row

# class definition

## data / function member

> use struct to save params, use class to make objects and communicate, use inbuild-type variable to associate in local.

1. static mem_fun

	* static *mem_fun* and static  *mem_data* have the same namespace
	* use `A::fun1();` to avoid creating a new object

2. const mem_fun

	* decorate some a *mem_data* with `mutable` can modify it

3. normal mem_fun

	* normal *mem_fun* has all access.

4. static mem_data

	* initialization need a type
	* permission control won't effect until initialization

5. others

	* `B *b = new B();`, explicit invoke which constructor, rather than using `B b;`. 

## initial list

initial list should **just** be used for const variables, constructor used for things of construction.

## memory deploy 

1. *mem_fun* is a code-block, determined by the class-type of caller, no matter what the object really is. (`T * const this` is same)
2. *mem_data* is a stack-var, determined by the runtime value in the memory, implemented by *mem_data* offset based on the object address

`malloc/free` is a function, compiler can't attach constructor/destructor task to it, so we need an operator that can be controlled by compiler, that is `new/delete`.

# oop

## [virtual table](https://www.zhangjiee.com/blog/cpp-vtable)

### single inheritance

In order to ensure the highest performance of virtual function tables, such as multi-layer inheritance or multi-inheritance, compilers usually store the pointers of virtual function tables in the front of object instances.

* when no virtual function override, derived class' v-table stores virtual function address in declaration order.
* when virtual function override, the base class in the virtual function table of the derived class is override with the virtual function is overwritten in the original position, while the virtual function of the derived class is no longer retained, the other remains. The virtual function name called by the base class pointer to statically determine the offset in the virtual function table, the virtual function tables of each derived class are also statically generated at **compile time**, and as to which virtual function table is used, the **runtime** determined by the specific content pointing to the base class pointer. Because the overloaded virtual function is overwritten at the original position of the base class, this implements polymorphism. Therefore, early binding refers to the function address to call is embedded in the constant store (code area) at compile time, and late binding refers to the function address to call is placed in the stack, only in the runtime can be taken, can also be said to be indirect addressing.

Note that if you still want a virtual function that is overloaded in a derived class call base class, you can call `Child->base::v_func () ` with the domain name parser, so that the compiler no longer goes through the virtual function table, but inserts the function address directly.

### runtime polymorphism

Runtime polymorphism can be seen as an attribute of **dynamically-typed, which allows an object that does not know the specific type (but knows its base class type) to call a function that knows only the interface **, which is different from the true dynamically-typed language, It implements type security checks at compile time through the technique of virtual function tables.

If the purpose of inheritance is code reuse, then the purpose of polymorphism is interface reuse.

## run time type information

1. when operand is statically-typed, `typeid` can deduce type information in compile time.
	* type name
	* build-in type variable name
	* object instance
	* dereference of pointer to non-virtual-member object, which has no polymorphism, and just truncates memory blocks statically.

2. when operand is dynamically-typed, `typeid` will deduce type information in run time by V-Table.
	* dereference of pointer to virtual-member object, which has polymorphism.
	* `dynamic_cast<T>(p)` provide safety downcast depending `type_info` information. To be detailed, it will get `T`'s `type_info` statically, and `p`'s `type_info` dynamically, and then compare&use them.

# string

1. conversion between number and string
2. string split 
3. string append

# reference

[1. Object Oriented Software Design and Construction  **CS2704**](http://people.cs.vt.edu/kafura/cs2704/basic.concepts.html)

