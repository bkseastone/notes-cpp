# oop

## [多态的实现细节——虚函数表](https://www.zhangjiee.com/blog/cpp-vtable)

### 函数指针

函数指针需显示地声明输入输出参数类型来给编译器提供中断/恢复现场所需的信息 （否则即使解引用某个函数地址并后接括号，也无法正确调用该函数），且考虑到安全问题，不允许隐式的类型转换。函数指针存储的就是代码块的地址（该地址由编译器自动分配）。

与数组类似，函数名在作为一个值使用时会隐式地转换为指针，函数类型在作为形参使用时同样也会隐式地转换为指针。在使用函数指针调用函数时也会隐式地解引用（不要纠结函数地址解引用后是什么，记住解引用后的东西只用于后接括号这一种情况就好了）。为保证较好的阅读性，推荐如下的使用方法：

```c++
void (*pfunc)(void) = &func; // 显式地表明这是函数地址
pfunc(); // 统一规范函数调用形式，隐去编译器内部的繁琐操作
```

另外，函数名代表的是那一段代码块，在编译时起符号链接作用，类似于变量名代表的便是那一个对象。

而类成员函数指针为能解决因为C++的多重继承、虚继承而带来的类实例地址的调整问题，在调用的时候一定要传入类实例对象，示例如下：

```c++
void (A::*pfunc)(void) = &A::func;
A a0 = new A();
(a0->*pfunc)();  //调用时必须要加类的对象名和*符号
```

### 单一继承

为了保证取到虚函数表的有最高的性能——如果有多层继承或是多重继承的情况下，编译器一般将虚函数表的指针存放于对象实例中最前面的位置。

* 当没有虚函数重载时，派生类的虚函数表为：虚函数按声明顺序放于表中，基类的虚函数在派生类的虚函数前面。

* 当有虚函数重载时，派生类的虚函数表中基类被重载的虚函数在原位置被覆盖，同时派生类的虚函数不再保留，其他的依旧。由基类指针所调用的虚函数名来静态确定在虚函数表中的偏移量，各派生类的虚函数表也在**编译时**静态生成；至于具体使用哪一个虚函数表，在**运行时**由基类指针的指向的具体内容决定。因为重载的虚函数是在基类的原位置覆盖，这就实现了多态。所以，早绑定是指要 call 的函数地址在编译期便被嵌入在了常量存储区（代码区），而晚绑定是指要 call 的函数地址是被放在栈中的，只有在运行时才能取到，也可以说是间接寻址。

注意，若仍然想在派生类调用基类中被重载的虚函数，可用域名解析符来调用`child->Base::v_func()`，如此编译器便不再走虚函数表，而是直接将函数地址插进来。

### 运行时多态

运行时多态可以看做为 **dynamically-typed 的一种特性，它允许一个不知道具体类型的对象（但知道其基类类型）去调用一个只知道接口的函数**，它与真正的 dynamically-typed language 不同，它通过虚函数表的技术在编译时实现类型安全检查。

若说继承的目的是代码重用，那么多态的目的便是接口重用。

## run time type information

1. when operand is statically-typed, `typeid` can deduce type information in compile time.

* type name

* build-in type variable name

* object instance

* dereference of pointer to non-virtual-member object, which has no polymorphism, and just truncats memory blocks statically.

2. when operand is dynamically-typed, `typeid` will deduce type information in run time by V-Table.

* dereference of pointer to virtual-member object, which has polymorphism.

* `dynamic_cast<T>(p)` provide safety downcast depending `type_info` information. To be detailed, it will get `T`'s `type_info` statically, and `p`'s `type_info` dynamically, and then campare&use them.

