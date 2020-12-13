## Mark Sweep GC

A simple mark sweep gc inspired by: 

-   [munificent/mark-sweep](https://github.com/munificent/mark-sweep)

编译环境：

-   C++11 or later

### 使用

本项目使用CMake构建，使用时：

首先在项目根目录使用：

```bash
cmake.exe -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ./
```

编译Makefile文件；

然后使用make命令编译：

```bash
make
```

编译完成后，运行文件即可：

```bash
# WIN
.\mark_sweep_gc.exe
# LINUX
./mark_sweep_gc
```

### 更多说明

见博文：

-   国外Github Pages：[使用C++实现一个Mark-Sweep的GC](https://jasonkayzk.github.io/2020/12/12/使用C++实现一个Mark-Sweep的GC/)
-   国内镜像Gitee Pages：[使用C++实现一个Mark-Sweep的GC](https://jasonkay.gitee.io/2020/12/12/使用C++实现一个Mark-Sweep的GC/)


