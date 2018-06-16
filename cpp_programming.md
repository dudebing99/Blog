[TOC]

------

> **说明：**C++ 编程时用到的一些小技巧。
>
> **参考资料：**
>
> - [More_C++_Idioms](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms)

## 赋值运算符方法优先处理自赋值

在实现赋值运算时，需要先判断是否是自赋值。

```cpp
T& operator= (const T& that)
{
    if (this == &that)
        return *this;

    // handle assignment here

    return *this;
}
```

