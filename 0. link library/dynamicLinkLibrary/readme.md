# [动态链接](http://man.linuxde.net/ldconfig)

1. 拷贝动态链接库到系统共享目录下,或在系统共享目录下为该动态链接库建立连接(硬连接或符号连接均可,常用符号连接).这里说的系统共享目录,指的是LINUX动态链接库存放的目录,包括/lib,/usr/lib以及/etc/ld.so.conf文件内所列的一系列目录。实例：执行 

```bash
cp libmyalib.so /lib 
ldconfig 
```

或

```bash
ln -s `pwd`/libmyalib.so /lib 
ldconfig 
```

注意pwd前后有两个反引号`，其目的是取得pwd命令的输出，即当前目录。此时再执行main，即可成功。

2. 将动态链接库所在目录名追加到动态链接库配置文件/etc/ld.so.conf中.。

```bash
pwd >> /etc/ld.so.conf 
ldconfig 
```bash

此时再执行main，即可成功。

3. 利用动态链接库管理命令ldconfig,强制其搜索指定目录,并更新缓存文件,便于动态装入。

```bash
ldconfig `pwd` 
```

此时再执行main，即可成功。要注意,第三种方法虽然有效,但效果是暂时的,供程序测试还可以,一旦再度运行ldconfig,则缓存文件内容可能改变,所需的动态链接库可能不被系统共享了。无论哪种办法，其实质都是用ldconfig命令把动态库文件，所在路径加入到系统库列表中。

4. LD_LIBRARY_PATH

如果想在这两个目录以外放lib，但是又不想在/etc/ld.so.conf中加东西（或者是没有权限加东西）。那也可以，就是export一个全局变量LD_LIBRARY_PATH，然后运行程序的时候就会去这个目录中找library。一般来讲这只是一种临时的解决方案，在没有权限或临时需要的时候使用。
