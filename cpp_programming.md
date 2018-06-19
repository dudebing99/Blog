[TOC]

------

> **说明：**C++ 编程时用到的一些小技巧。
>
> **参考资料：**
>
> - [More C++ Idioms](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms)
> - [More C++ Idioms 中文翻译](https://github.com/HorkyChen/MoreCPlusPlusIdioms)

## 运行时间测量

### C++ 实现方式

> **源码路径：**[calculate_runtime.cpp](https://dudebing99.github.io/blog/archives/cpp_programming/calculate_runtime.cpp)

```cpp
#include <iostream>
#include <chrono>
#include <functional>

using MilliSeconds = std::chrono::milliseconds;
using MicroSeconds = std::chrono::nanoseconds;
using NanoSeconds = std::chrono::nanoseconds;

template<typename TimeT = MilliSeconds>
struct Measure
{
    template<typename F, typename ...Args>
    typename TimeT::rep Execution(F func, Args&&... args)
    {
        auto start = std::chrono::system_clock::now();

        // Now call the function with all the parameters you need.
        func(std::forward<Args>(args)...);

        auto duration = std::chrono::duration_cast< TimeT>
            (std::chrono::system_clock::now() - start);

        return duration.count();
    }
};

class Dummy
{
public:
    Dummy() = default;
    ~Dummy() = default;

public:
    void Add()
    {
        double sum = 0.0;
        for (int i = 0; i < 8000000; ++ i)
        {
            sum += 1.01;
        }
    }
};

void Add()
{
    double sum = 0.0;
    for (int i = 0; i < 8000000; ++i)
    {
        sum += 1.01;
    }
}

int main()
{
    Measure<MilliSeconds> measure;

    std::cout << "1. call directly" << std::endl;
    std::cout << measure.Execution([&]() {
        double sum = 0.0;
        for (int i = 0; i < 8000000; ++i)
        {
            sum += 1.01;
        }
    }) << " ms" << std::endl;

    std::cout << "2. call member function" << std::endl;
    Dummy dummy;
    std::cout << measure.Execution(std::bind(&Dummy::Add, &dummy)) << " ms " << std::endl;

    std::cout << "3. call common function" << std::endl;
    std::cout << measure.Execution(Add) << " ms" << std::endl;

    return 0;
}
```

**输出**

```bash
1. call directly
32 ms
2. call member function
34 ms 
3. call common function
47 ms
```

### C 实现方式

```c
#include <ctime>
#include <stdio.h>

int main()
{
    clock_t begin = clock();

    // your codes
    double sum = 0.0;
    for (int i = 0; i < 100000000; ++ i)
    {
        sum += 1.1;
    }

    clock_t end = clock();

    double elapsed_sec = double(end - begin) / CLOCKS_PER_SEC;
    double elapsed_ms = double(end - begin) / (CLOCKS_PER_SEC / 1000);

    printf("elapsed %.3f second, %.0f ms\n", elapsed_sec, elapsed_ms);

    return 0;
}
```

**输出**

```bash
elapsed 0.360 second, 360 ms
```

## 赋值运算符方法优先处理自赋值

​	在实现赋值运算时，需要先判断是否是自赋值。如果赋值运算符操作的两个对象实际是同一个对象，直接返回即可。

```cpp
T& operator= (const T& that)
{
    if (this == &that)
        return *this;

    // handle assignment here

    return *this;
}
```

## PIMPL 指向实现的指针

​	PIMPL（pointer to implementation），即，指向实现的指针，是一种常用的，用来对“类的接口与实现”进行解耦的方法。这个技巧可以避免在头文件中暴露私有细节，因此是促进 API 接口与实现保持完全分离的重要机制。由于PIMPL 解除了接口与实现之间的耦合关系，从而降低文件间的编译依赖关系，PIMPL 也因此常被称为“编译期防火墙“ 。

### 主要优点

- 降低耦合
- 信息隐藏：真正实现依赖于私有指针完成
- 降低编译依赖，提高编译速度：可减少编译冲突
- 接口与实现分离

### 使用场景

​	一般来说，研发部基础平台组负责基础组件的开发，然后提供给业务组使用。因此，基础组件的接口不需要暴露过多的实现细节，同时，实现发生变化时，最好能够做到业务组不需要重新编译所有使用到基础组件的代码，否则将极大地增加学习、使用成本。例如，基础平台组提供跨平台的线程库，最开始只提供 支持 Windows，后续需要支持 Linux；或者需要在类中添加一个私有成员变量，如果直接在接口层实现，将导致 Windows 平台相关的所有代码需要重新编译。此时，利用 PIMPL 即可解决如上问题。

### 示例

​	定义一个 Book 类，包含一个成员变量。

```cpp
class Book
{
public:
    void Print();
private:
    std::string m_contents;
};
```

​	对于使用者而言，只需要关注 Print()，但是如果我们给 Book 类添加一个成员变量

```cpp
class Book
{
public:
    void Print();
private:
    std::string m_contents;
    std::string m_title;
};
```

​	虽然 Print() 接口本身不变，但是使用者需要重新编译所有使用到 Book 类的源码。此时，通过 PIMPL 可以得到解决。

- 提供接口的头文件 public.h

```cpp
// public.h
class Book
{
public:
    void Print();
private:
    class BookImpl;
    BookImpl *m_impl;
};
```

- 私有实现相关的头文件 private.h

```cpp
// private.h
#include "public.h"

class Book::BookImpl
{
public:
    void Print();
private:
    std::string m_contents;
    std::string m_title;
};
```

- 实现源文件

```cpp
Book::Book() : m_impl(new BookImpl())
{
}

Book::~Book()
{
    delete m_impl;
}

void Book::Print()
{
    m_impl->Print();
}

void Book::BookImpl::Print()
{
    std::cout << "print from BookImpl" << std::endl;
}
```

- 对于使用者而言

```cpp
int main()
{
    Book book;
    book.Print();
    
    return 0;
}
```



