# pointer

## memory deploy 

1. data member is a stack-var, mem_func is a code-block which is not a part of the object in the memory.
so, call a mem_func depend on the object type, while call a data member depend on offset based on the object address.
Totally, mem_func and `T *const this` are determined by the type of caller, data member is determined by the runtime value in the memory.

2. `malloc/free` is a function, compiler can't attatch constructor/destructor task to it, so we need an operator that can be controled by compiler, that is `new/delete`.

## function pointer

## array/pointer
