# class defination

## data OR function member

> use struct to save params, use class to make objects and communicate, use inbuild-type variable to associate in local.

### static mem_fun

Static mem_fun hasn't access to communicate with members of objects.When call static mem_fun, don't pass object pointer.Bcz static mem_fun and static member have the same namespace, we can directly use static members(here is CNT).

When only want to use a func, we can make it like this `A::fun1();`. Thereby avoid creating new object.

### const mem_fun

Const mem_fun can read but can't modify members of objects.When call const mem_fun, pass a read-only object pointer(here is `const A *this`).
If you really really want to modify some a member, you can decorate that member with `mutable`.

### normal mem_fun

Normal mem_fun has all access.

### static mem_data

this is initialization, above is declaration, all compilation will do is making a link after making memory-layout. And, initialization naturally need a type. And, permission control won't effect until initialization.

### others

`B *b = new B();`, explicit invoke which constructor, rather than using `B b;`. 

## initial list

if need a class-type member, there are 2 methods to solve twice construction process:

1. use initial list, rather than re-assign it a value in construct function block.

2. (**feature**)use a pointer not a object, thereby it is same to a inbuild-type member, and there is no difference between initial and re-assign.

totally, initial list should just be used for const variables, things of construction should be constructor's responsibility.
