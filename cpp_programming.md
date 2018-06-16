[TOC]

------

> **说明：**C++ 编程时用到的一些小技巧。
>
> **参考资料：**
>
> - [More_C++_Idioms](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms)

## 赋值运算符方法优先处理自赋值

在实现赋值运算时，需要先判断是否是自赋值。如果赋值运算符操作的两个对象实际是同一个对象，直接返回即可。

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

**Pimpl：** pointer to implementation，即，指向实现的指针，是一种常用的，用来对“类的接口与实现”进行解耦的方法。这个技巧可以避免在头文件中暴露私有细节，因此是促进 API 接口与实现保持完全分离的重要机制。

### 主要优点

- 降低耦合
- 信息隐藏：真正实现依赖于私有指针完成
- 降低编译依赖，提高编译速度：可减少编译冲突
- 接口与实现分离

