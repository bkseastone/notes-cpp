# [link library](https://blog.csdn.net/ztf312/article/details/77258048)

1. [creat static link library](https://www.cnblogs.com/alan666/p/8311984.html)

``` bash
g++ -c test.cpp
ar -r libtest.a test.o
g++ -I./lib -L./lib -o main main.cpp -ltest
./main
```

2. creat dynamic link library

```bash
g++ -fPIC -shared -o libtest.so test.cpp
g++ -I./lib -L./lib -o main main.cpp -ltest
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
./main
```
