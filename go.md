[TOC]

------

## 参考资料

- [gobyexample](https://gobyexample.com/)
- [50 Shades of Go: Traps, Gotchas, and Common Mistakes for New Golang Devs](http://devs.cloudimmunity.com/gotchas-and-common-mistakes-in-go-golang/)
- [Golang tutorial series](https://golangbot.com/learn-golang-series/)
- [topgoer.com](http://www.topgoer.com/)

## Hello World

**功能：**向控制台打印 Hello World

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/hello_world/hello_world.go)

```go
package main

import "fmt"

func main() {
	fmt.Printf("%s\n", "Hello World")
}
```

**输出**

```bash
Hello World
```

## for 循环

**功能：**输出九九乘法口诀表

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/recycle/for.go)

```go
package main

import "fmt"

func main() {
	for i := 1; i <= 9; i++ {
		for j := 1; j <= i; j++ {
			fmt.Printf("%d*%d=%d ", j, i, j*i)
		}
		fmt.Println("")
	}
}
```

**输出**

```bash
1*1=1 
1*2=2 2*2=4 
1*3=3 2*3=6 3*3=9 
1*4=4 2*4=8 3*4=12 4*4=16 
1*5=5 2*5=10 3*5=15 4*5=20 5*5=25 
1*6=6 2*6=12 3*6=18 4*6=24 5*6=30 6*6=36 
1*7=7 2*7=14 3*7=21 4*7=28 5*7=35 6*7=42 7*7=49 
1*8=8 2*8=16 3*8=24 4*8=32 5*8=40 6*8=48 7*8=56 8*8=64 
1*9=9 2*9=18 3*9=27 4*9=36 5*9=45 6*9=54 7*9=63 8*9=72 9*9=81 
```

**功能：**实现 while 逻辑（Golang 中无 while 循环，可借助 for 实现）

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/recycle/while.go)

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	var count uint32 = 0
	for true {
		count++
		if count == 3 {
			goto loop
		}
		fmt.Println("count: ", count, " in infinite loop")
		time.Sleep(time.Second * 3)
	}
loop:
	fmt.Println("Go to loop")
}
```

**输出**

```bash
count:  1  in infinite loop
count:  2  in infinite loop
Go to loop
```

## switch 多分支

> Golang 的 switch 非常灵活：
>
> - 如果 switch 有表达式，表达式不必是常量或整数，执行的过程从上至下，直到找到匹配项
> - 如果 switch 没有表达式，从上到下直到匹配 case 的表达式为真
> - switch 默认每个 case 最后带有 break，即，匹配成功后不会自动向下执行其他 case，而是跳出整个switch，可使用 fallthrough 强制执行后面的 case 代码，fallthrough 不会判断下一个 case 的表达式是否为真

**功能：**switch 多分支的使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/switch.go)

```go
package main

import "fmt"
import "time"

func f0(i int) {
	// 包含条件表达式
	switch i {
	case 1:
		fmt.Println("one")
	case 2:
		fmt.Println("two")
	case 3:
		fmt.Println("three")
	default:
		fmt.Println("unexpected")
	}
}

func f1(i int) {
	// 包含条件表达式
	switch i {
	case 1:
		fmt.Println("one")
	case 2:
		fmt.Println("two")
		fallthrough
	case 3:
		fmt.Println("three")
	default:
		fmt.Println("unexpected")
	}
}

func f2(weekday time.Weekday) {
	// 包含条件表达式，多重条件
	switch weekday {
	case time.Saturday, time.Sunday:
		fmt.Println("It's the weekend")
	default:
		fmt.Println("It's a weekday")
	}
}

func f3(t time.Time) {
	// 不含条件表达式
	switch {
	case t.Hour() < 12:
		fmt.Println("It's at morning")
	case t.Hour() == 12:
		fmt.Println("It's at noon")
	case t.Hour() > 12:
		fmt.Println("It's after noon")
	}
}

func f4(i interface{}) {
	switch t := i.(type) {
	case bool:
		fmt.Println("I'm a bool")
	case int:
		fmt.Println("I'm an int")
	case string:
		fmt.Println("I'm a string")
	default:
		fmt.Printf("Type: %T\n", t)
	}
}

func main() {
	f0(2)
	f1(2)
	f2(time.Now().Weekday())
	f3(time.Now())
	f4(false)
	f4(99)
	f4("hello world")
}
```

**输出**

```bash
two
two
three
It's the weekend
It's after noon
I'm a bool
I'm an int
I'm a string
```

## 字符串

**功能：**字符串的基础使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/string.go)

```go
package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	// 查找
	var str1, str2 string
	str1 = "12,30,34"
	str2 = str1[0:strings.Index(str1, ",")]
	fmt.Println(str2)

	tagIDs := make([]int, 0)
	// 字符串切割
	tagIDsStr := strings.Split("1,2,3,5,4", ",")
	for _, tagIDStr := range tagIDsStr {
		// 字符串转整数
		tagID, err := strconv.Atoi(tagIDStr)
		if err != nil {
			fmt.Println("unexpected error: ", err.Error())
		} else {
			tagIDs = append(tagIDs, tagID)
		}
	}

	for _, tagID := range tagIDs {
		fmt.Println("TagID: ", tagID)
	}

	ids := []string{"a", "b", "c", "d"}
	// 字符串拼接
	idsStr := strings.Join(ids, "#")
	fmt.Println("idsStr:", idsStr)

	// 字符串替换
	str := "kevin's blog"
	str = strings.Replace(str, "'", "\\'", -1)
	fmt.Println(str)

	str3 := "hello"
	data := []byte(str3)
	fmt.Println(data)
	str3 = string(data[:])
	fmt.Println(str3)
}
```

**输出**

```bash
12
TagID:  1
TagID:  2
TagID:  3
TagID:  5
TagID:  4
idsStr: a#b#c#d
kevin\'s blog
[104 101 108 108 111]
hello
```

## 时间

**功能：**时间相关的基础使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/time.go)

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	// 获取时间戳
	fmt.Println(time.Now().Unix())
	fmt.Println(time.Now().UnixNano())

	// 获取年、月、日、星期
	fmt.Println(time.Now().Year(),
		time.Now().Month(),
		time.Now().Day(),
		time.Now().Weekday())

	// 将当前时间以字符串形式输出
	fmt.Println(time.Now().String())
	fmt.Println(time.Now().Local())
    
    // UTC 时间、本地时间
    now := time.Now()
	year, mon, day := now.UTC().Date()
	hour, min, sec := now.UTC().Clock()
	zone, _ := now.UTC().Zone()
    fmt.Printf("UTC: %d-%d-%d %02d:%02d:%02d %s\n", year, mon, day, hour, min, sec, zone)

	year, mon, day = now.Date()
	hour, min, sec = now.Clock()
	zone, _ = now.Zone()
    fmt.Printf("Local: %d-%d-%d %02d:%02d:%02d %s\n", year, mon, day, hour, min, sec, zone)

	// 按照模板指定格式将时间以字符串输出
	strTime := time.Now().Format("2006-01-02 15:04:05")
	fmt.Println(strTime)
	strTime = time.Now().Format("2006/01/02 15")
	fmt.Println(strTime)
	strTime = time.Now().UTC().Add(8 * time.Hour).Format("20060102_1504")
	fmt.Println(strTime)
}
```

**输出**

```bash
1589854668
1589854668221668760
2020 May 19 Tuesday
2020-05-19 10:17:48.221818757 +0800 CST m=+0.000249605
2020-05-19 10:17:48.221838231 +0800 CST
UTC: 2020-5-19 02:17:48 UTC
Local: 2020-5-19 10:17:48 CST
2020-05-19 10:17:48
2020/05/19 10
20200519_1017
```

## array 数组

**功能：**array 数组基础使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/array.go)

```go
package main

import "fmt"

func main() {

	var array [5]int
	fmt.Println("init(default):", array)
	fmt.Println("len:", len(array))

	for i := 0; i < 4; i++ {
		array[i] = i * 10
	}
	fmt.Println("array:", array)
	fmt.Println("get array[4]:", array[4])

	array2 := [5]int{1, 2, 3, 4, 5}
	fmt.Println("init:", array2)

	// array[x, y]
	var arrayXY [2][3]int
	for x := 0; x < 2; x++ {
		for y := 0; y < 3; y++ {
			arrayXY[x][y] = x + y
		}
	}

	fmt.Println("array[x, y]:", arrayXY)
	fmt.Printf("array[x, y]: %v\n", arrayXY)
	fmt.Printf("%T\n", arrayXY)
}
```

**输出**

```bash
init(default): [0 0 0 0 0]
len: 5
array: [0 10 20 30 0]
get array[4]: 0
init: [1 2 3 4 5]
array[x, y]: [[0 1 2] [1 2 3]]
array[x, y]: [[0 1 2] [1 2 3]]
[2][3]int
```

## map

**功能：** map 基础使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/map_without_init.go)

```go
package main

import "fmt"

func f1() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println(err)
		}
	}()

	// 声明变量，默认 map 是 nil，如果直接对其操作会报错
	var kv map[int]string
	kv[1] = "hello"
}

func f2() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println(err)
		}
	}()

	var kv map[int]string = make(map[int]string)
	kv[1] = "hello"
	kv[2] = "world"

	for k, v := range kv {
		fmt.Println(k, v)
	}
}

func main() {
	f1()
	f2()
}
```

**输出**

```bash
assignment to entry in nil map
1 hello
2 world
```

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/map.go)

```go
package main

import "fmt"

func main() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println(err)
		}
	}()

	// 声明变量，默认 map 是 nil，如果直接对其操作会报错
	var kv map[int]string
	// 初始化
	kv = make(map[int]string)
	// 添加元素
	kv[1] = "hello"
	kv[2] = "dummy"
	kv[3] = "world"

	// 遍历
	for k, v := range kv {
		fmt.Println("key:", k, ", value:", v)
	}

	// 删除元素
	delete(kv, 2)

	fmt.Println("info: after deleting element")
	for k, v := range kv {
		fmt.Println("key:", k, ", value:", v)
	}

	// 查找元素
	v, found := kv[2]
	if found {
		fmt.Println("found, value:", v)
	} else {
		fmt.Println("not found")
	}

	v, found = kv[3]
	if found {
		fmt.Println("found, value:", v)
	} else {
		fmt.Println("not found")
	}

	// 声明、初始化
	kv2 := make(map[int]string)
	kv2[1] = "k"
	kv2[2] = "v"
	for k, v := range kv2 {
		fmt.Println("key:", k, ", value:", v)
	}

	// 声明、初始化、添加元素
	kv3 := map[int]string{
		1: "A",
		2: "B",
		3: "C",
	}

	for k, v := range kv3 {
		fmt.Println("key:", k, ", value:", v)
	}
}
```

**输出**

```bash
key: 1 , value: hello
key: 2 , value: dummy
key: 3 , value: world
info: after deleting element
key: 1 , value: hello
key: 3 , value: world
not found
found, value: world
key: 1 , value: k
key: 2 , value: v
key: 1 , value: A
key: 2 , value: B
key: 3 , value: C
```

## slice 切片

**功能：**slice 基础使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/slice.go)

```go
package main

import "fmt"

func main() {
	// 创建切片
	numbers := []int{0, 1, 2, 3, 4, 5, 6, 7, 8}

	// 初始化
	numbers2 := numbers[1:5]
	numbers3 := numbers[:2]
	numbers4 := numbers[3:]
	numbers5 := numbers[:]

	printSlice(numbers)
	printSlice(numbers2)
	printSlice(numbers3)
	printSlice(numbers4)
	printSlice(numbers5)

	// 子切片是切片的引用，对子切片的修改也直接反映到切片
	numbers2[1] = 100
	printSlice(numbers2)
	printSlice(numbers)

	// 切片元素追加
	numbers2 = append(numbers2, 99)
	printSlice(numbers2)

	// 遍历切片
	for index, value := range numbers {
		fmt.Println("index: ", index, ", value: ", value)
	}
}

func printSlice(x []int) {
	fmt.Printf("len=%d cap=%d slice=%v\n", len(x), cap(x), x)
}
```

**输出**

```bash
len=9 cap=9 slice=[0 1 2 3 4 5 6 7 8]
len=4 cap=8 slice=[1 2 3 4]
len=2 cap=9 slice=[0 1]
len=6 cap=6 slice=[3 4 5 6 7 8]
len=9 cap=9 slice=[0 1 2 3 4 5 6 7 8]
len=4 cap=8 slice=[1 100 3 4]
len=9 cap=9 slice=[0 1 100 3 4 5 6 7 8]
len=5 cap=8 slice=[1 100 3 4 99]
index:  0 , value:  0
index:  1 , value:  1
index:  2 , value:  100
index:  3 , value:  3
index:  4 , value:  4
index:  5 , value:  99
index:  6 , value:  6
index:  7 , value:  7
index:  8 , value:  8
```
## 传递指针和对象的区别

**功能：**传递指针改变原对象，传对象类似于传值，不改变原对象。

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/pointer_or_object.go)

```go
package main

import (
	"fmt"
)

type T struct {
	identity string
}

func (t T) f1() {
	t.identity = "lucy"
}

func (t *T) f2() {
	t.identity = "lily"
}

func main() {
	t := T{"hello"}

	fmt.Println(t.identity)
	t.f1()
	fmt.Println(t.identity)

	t.f2()
	fmt.Println(t.identity)
}
```

**输出**

```bash
hello
hello
lily
```

## 指针综合使用

```go
package main

import (
	"fmt"
)

func change(val *int) {
	*val = 55
}

func modify1(arr *[3]int) {
	(*arr)[0] = 90
}

func modify2(arr *[3]int) {
	arr[0] = 90
}

func modify3(sls []int) {
	sls[0] = 90
}

func main() {
	// 创建指针
	b := 255
	var a *int = &b
	fmt.Printf("Type of a is %T\n", a)
	fmt.Println("address of b is", a)

	// 未经初始化的指针为 nil
	d := 25
	var p *int
	if p == nil {
		fmt.Println("\np is", p)
		p = &d
		fmt.Println("p after initialization is", p)
	}

	i := 255
	j := &i
	fmt.Println("\naddress of i is", j)
	fmt.Println("value of i is", *j)
	*j++
	fmt.Println("new value of i is", i)

	// 指针不允许指针加减运算，如下报错 invalid operation: j++ (non-numeric type *int)
	// j++

	k := 58
	fmt.Println("\nvalue of k before function call is", k)
	l := &k
	change(l)
	fmt.Println("value of k after function call is", k)

	// 通过传递数组指针给函数的方式来修改原始数组的值
	m := [3]int{89, 90, 91}
	modify1(&m)
	fmt.Println("\nmodify1 using pointer to an array", m)

	n := [3]int{89, 90, 91}
	modify2(&n)
	fmt.Println("modify2 using pointer to an array", n)

	// 使用切片作为函数参数，代码更加简洁，在 Go 中更常被使用
	o := [3]int{89, 90, 91}
	modify3(o[:])
	fmt.Println("modify3 using slice", o)
}
```

**输出**

```bash
Type of a is *int
address of b is 0xc042058080
p is <nil>
p after initialization is 0xc042058088
address of i is 0xc0420580b0
value of i is 255
new value of i is 256
value of k before function call is 58
```

## struct 结构体

**功能：**struct 的定义、实例化、使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/struct.go)

```go
package main

import "fmt"

// 属性的开头字母是大写或小写决定该属性的访问权限，
// 开头字母是大写的则在其他包中可以访问，否则只能在本包中访问
type Human struct {
	Age  int8
	Sex  byte
	name string
}

func NewHuman(age int8, sex byte, name_ string) (h *Human) {
	h = &Human{
		Age:  age,
		Sex:  sex,
		name: name_,
	}
	return
}

// 类方法声明
func (h Human) printInfo() {
	fmt.Printf("Age: %d, Sex: %c, Name: %s\n", h.Age, h.Sex, h.name)
	h.name = "sb"
}

// 类方法声明
func (h *Human) printInfo2() {
	fmt.Printf("Age: %d, Sex: %c, Name: %s\n", h.Age, h.Sex, h.name)
	h.name = "sb"
}

// 匿名结构体
func printInfo() {
	h := struct {
		Age  int8
		Name string
	}{22, "jiakong"}

	fmt.Printf("%s is %d\n", h.Name, h.Age)
}

func main() {
	h := Human{99, 'M', "jiakong"}

	h.printInfo()
	fmt.Println("after pass-by object: ", h.name)
	h.printInfo2()
	fmt.Println("after pass-by pointer: ", h.name)

	printInfo()

	// 实例化对象
	// 1. 值对象
	h1 := Human{}
	h1.name = "sb"

	h2 := Human{99, 'M', "sb"}
	h2.name = "sb"

	h3 := Human{
		Age: 99,
		Sex: 'M',
	}
	h3.name = "sb"

	// 2. 指针对象
	h4 := new(Human)
	h4.name = "sb"

	h5 := &Human{}
	h5.name = "sb"

	h6 := &Human{
		Sex: 'M',
	}
	h6.name = "sb"

	// 3. 构造函数
	h7 := NewHuman(22, 'M', "jiakong")
	fmt.Println(h7.Age, h7.Sex, h7.name)
}
```

**输出**

```bash
Age: 99, Sex: M, Name: jiakong
after pass-by object:  jiakong
Age: 99, Sex: M, Name: jiakong
after pass-by pointer:  sb
jiakong is 22
22 77 jiakong
```

## 自定义结构体 slice 排序

**功能：**自定义结构体 slice 对象，对其进行升序、降序排序

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/sort/slice_sort.go)

```go
package main

import (
	"fmt"
	"sort"
)

type ContentScore struct {
	ContentID int64
	Score     float32
}

type ContentScoreList []ContentScore

func (csl ContentScoreList) Len() int {
	return len(csl)
}

func (csl ContentScoreList) Swap(i, j int) {
	csl[i], csl[j] = csl[j], csl[i]
}

// 按照 score 逆序排序
func (csl ContentScoreList) Less(i, j int) bool {
	return csl[j].Score < csl[i].Score
}

func main() {
	contentScoreList := ContentScoreList{
		{100, 12.34},
		{200, 9.35},
		{99, 7.90},
		{400, 8.91},
	}

	fmt.Println("按照 score 逆序排序")
	sort.Sort(ContentScoreList(contentScoreList))
	for _, contentScore := range contentScoreList {
		fmt.Printf("Conent ID: %d, Score: %f\n", contentScore.ContentID, contentScore.Score)
	}

	fmt.Println("按照 score 升序排序")
	sort.Sort(sort.Reverse((ContentScoreList(contentScoreList))))
	for _, contentScore := range contentScoreList {
		fmt.Printf("Conent ID: %d, Score: %f\n", contentScore.ContentID, contentScore.Score)
	}
}
```

**输出**

```bash
按照 score 逆序排序
Conent ID: 100, Score: 12.340000
Conent ID: 200, Score: 9.350000
Conent ID: 400, Score: 8.910000
Conent ID: 99, Score: 7.900000
按照 score 升序排序
Conent ID: 99, Score: 7.900000
Conent ID: 400, Score: 8.910000
Conent ID: 200, Score: 9.350000
Conent ID: 100, Score: 12.340000
```

## map 排序

**功能：**借助 slice，实现 map 的按序输出

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/sort/map_sort.go)

```go
package main

import (
	"fmt"
	"sort"
)

func main() {
	// map 本身无序，如果需要按序输出，需要借助一些技巧，如下所示
	var m = map[string]int{
		"unix":         0,
		"python":       1,
		"go":           2,
		"javascript":   3,
		"testing":      4,
		"philosophy":   5,
		"startups":     6,
		"productivity": 7,
		"hn":           8,
		"reddit":       9,
		"C++":          10,
	}
	// 遍历输出
	fmt.Println("Before sort")
	for key, value := range m {
		fmt.Println("Key: ", key, ", Value: ", value)
	}

	// 保存所有的 key
	var keys []string
	for k := range m {
		keys = append(keys, k)
	}
	// key 排序
	sort.Strings(keys)

	fmt.Println("After sort")
	// 利用排过序的 key 找到对应的 value
	for _, k := range keys {
		fmt.Println("Key:", k, ", Value:", m[k])
	}
}
```
**输出**
```bash
Before sort
Key:  C++ , Value:  10
Key:  go , Value:  2
Key:  javascript , Value:  3
Key:  testing , Value:  4
Key:  philosophy , Value:  5
Key:  startups , Value:  6
Key:  productivity , Value:  7
Key:  reddit , Value:  9
Key:  unix , Value:  0
Key:  python , Value:  1
Key:  hn , Value:  8
After sort
Key: C++ , Value: 10
Key: go , Value: 2
Key: hn , Value: 8
Key: javascript , Value: 3
Key: philosophy , Value: 5
Key: productivity , Value: 7
Key: python , Value: 1
Key: reddit , Value: 9
Key: startups , Value: 6
Key: testing , Value: 4
Key: unix , Value: 0
```

## 通用单链表

**功能：**通用单链表，包含统计链表长度，头部插入、尾部插入

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/sort/single_linked_list.go)

```go
package main

import "fmt"

type LinkNode struct {
	data interface{}
	next *LinkNode
}

type Link struct {
	head *LinkNode
	tail *LinkNode
}

func (p *Link) Count() int {
	count := 0
	head := p.head
	for head != nil {
		head = head.next
		count++
	}

	return count
}

func (p *Link) InsertHead(data interface{}) {
	node := &LinkNode{
		data: data,
		next: nil,
	}

	if p.tail == nil && p.head == nil {
		p.tail = node
		p.head = node
		return
	}

	node.next = p.head
	p.head = node
}

func (p *Link) InsertTail(data interface{}) {
	node := &LinkNode{
		data: data,
		next: nil,
	}

	if p.tail == nil && p.head == nil {
		p.tail = node
		p.head = node
		return
	}

	p.tail.next = node
	p.tail = node
}

func (p *Link) Trans() {
	q := p.head
	for q != nil {
		fmt.Println(q.data)
		q = q.next
	}
}

func main() {
	var link Link
	for i := 0; i < 10; i++ {
		if i%2 == 0 {
			link.InsertHead(i)
		} else {
			link.InsertTail(fmt.Sprintf("str %d", i))
		}
	}

	link.Trans()

	fmt.Printf("Contains %d element(s)", link.Count())
}
```

**输出**

```bash
8
6
4
2
0
str 1
str 3
str 5
str 7
str 9
Contains 10 element(s)
```

## 继承

**功能：**单继承、多继承

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/sort/inherit.go)

```go
package main

import (
	"fmt"
)

type Father struct {
	CN string
}

func (this *Father) Say() {
	fmt.Println("大家好, 我是", this.CN)
}

type Mother struct {
	EN string
}

func (this *Mother) Say() {
	fmt.Println("Hello, I am", this.EN)
}

type Child1 struct {
	Father
	Age int8
}

type Child2 struct {
	Father
	Mother
	Age int8
}

func main() {
	child1 := new(Child1)
	child1.CN = "小呆比"
	child1.Age = 22
	child1.Say()

	child2 := new(Child2)
	child2.CN = "小呆比"
	child2.EN = "little silly B"
	child2.Father.Say()
	child2.Mother.Say()
}
```

**输出**

```bash
大家好, 我是 小呆比
大家好, 我是 小呆比
Hello, I am little silly B
```

## 匿名函数

**功能：**介绍匿名函数的使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/anonymous_func.go)

```go
package main

import "fmt"

func main() {
	func(x, y int) {
		fmt.Printf("x + y = %d\n", x+y)
	}(19, 96)

	f := func(x, y int) int {
		return x * y
	}

	fmt.Printf("x * y = %d\n", f(16, 2))
}
```

**输出**

```bash
x + y = 115
x * y = 32
```

## 函数闭包

**功能：**介绍函数闭包的使用

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/basic/closure.go)

```go
package main

import "fmt"

func add() func(int) int {
	sum := 0
	fmt.Println("sum: ", sum)
	return func(x int) int {
		sum += x
		fmt.Println("x: ", x, ", sum += x: ", sum)
		return sum
	}
}

func main() {
	fmt.Println("declare f()")
	f := add()

	fmt.Println("call f()")
	for i := 0; i < 10; i++ {
		fmt.Println("f(i): ", f(i))
	}
}
```

**输出**

```bash
declare f()
sum:  0
call f()
x:  0 , sum += x:  0
f(i):  0
x:  1 , sum += x:  1
f(i):  1
x:  2 , sum += x:  3
f(i):  3
x:  3 , sum += x:  6
f(i):  6
x:  4 , sum += x:  10
f(i):  10
x:  5 , sum += x:  15
f(i):  15
x:  6 , sum += x:  21
f(i):  21
x:  7 , sum += x:  28
f(i):  28
x:  8 , sum += x:  36
f(i):  36
x:  9 , sum += x:  45
f(i):  45
```

## json 使用

### 常见数据结构序列为 json

**功能：**使用 json

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/json/json.go)

```go
package main

import (
	"encoding/json"
	"fmt"
)

type Person struct {
	ID   int64
	Name string
}

func main() {
	// slice 序列化为 json
	var s []string = []string{"Go", "Java", "Python", "Android"}
	if j, err := json.Marshal(s); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}

	// map 序列化为 json
	var m map[string]string = make(map[string]string)
	m["Go"] = "No.1"
	m["Java"] = "No.2"
	m["C"] = "No.3"
	if j, err := json.Marshal(m); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}

	// 自定义结构序列化为 json
	var p []Person = []Person{
		{99, "Kevin"},
		{100, "Jianghai He"},
	}
	// 压缩输出
	if j, err := json.Marshal(p); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}
	// 非压缩，带缩进、换行
	if j, err := json.MarshalIndent(p, "", "  "); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}
}
```

**输出**

```bash
["Go","Java","Python","Android"]
{"C":"No.3","Go":"No.1","Java":"No.2"}
[{"ID":99,"Name":"Kevin"},{"ID":100,"Name":"Jianghai He"}]
[
  {
    "ID": 99,
    "Name": "Kevin"
  },
  {
    "ID": 100,
    "Name": "Jianghai He"
  }
]
```

### struct field's tag in json

**功能：**在 json 中使用结构体字段标签，实现结构体与 json 的映射，一般在服务调用之间通过 json 打包数据场合，例如，解析 json 请求到结构体中，将结构体序列化到回复 json 中

- `` 即，struct filed's tag
- 第一个参数，指定别名，可以灵活地调整结构体与序列化对应的字段；如果不需要指定别名但需要指定其他参数，留空以逗号分隔即可
- `omitempty` 修饰一个字段时，如果该字段值缺省或者赋值为`零`（非狭义的数字 0，例如，该字段为 bool 类型时，false 被当做`零`），序列化时将被忽略
- `-` 修饰一个字段时，序列化会忽略该字段
- `string` 修改一个字段时，序列化时该字段被转换成 string 类型

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/json/struct_tag_json.go)

```go
package main

import (
	"encoding/json"
	"fmt"
)

type Person struct {
	Name        string `json:"User"`
	Age         int    `json:"Age"`
	Gender      bool   `json:",omitempty"`
	Profile     string
	OmitContent string `json:"-"`
	Count       int    `json:",string"`
}

func main() {
	var p *Person = &Person{
		Name:        "Kevin",
		Age:         22,
		Gender:      true,
		Profile:     "Coding Dog",
		OmitContent: "Hello World",
	}
	if j, err := json.Marshal(&p); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}

	var p2 *Person = &Person{
		Name:        "Kevin",
		Age:         22,
		Gender:      false,
		Profile:     "Coding Dog",
		OmitContent: "Hello World",
	}
	if j, err := json.Marshal(&p2); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}

	var p3 *Person = &Person{
		Name:        "Kevin",
		Gender:      false,
		Profile:     "Coding Dog",
		OmitContent: "Hello World",
	}
	if j, err := json.Marshal(&p3); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}
}
```

**输出**

```bash
{"User":"Kevin","Age":22,"Gender":true,"Profile":"Coding Dog","Count":"0"}
{"User":"Kevin","Age":22,"Profile":"Coding Dog","Count":"0"}
{"User":"Kevin","Age":0,"Profile":"Coding Dog","Count":"0"}
```

## protobuf 使用

### 数据结构无嵌套

**功能：**使用 protobuf

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/protobuf/1.tar.gz)

1. 定义 proto 文件

```basic
   syntax = "proto3";

   package hello;

   message Message {
       int32 id = 1;
       string message = 2;
   }
```

2. 利用 protoc 编译 proto 文件，生成对应的 Golang 文件，命令如下（根据实际情况替换目录）

```bash
protoc.exe --proto_path=/d/Blog/archives/go/protobuf/1/proto --go_out=/d/Blog/archives/go/protobuf/1/proto hello.proto
```

3. 使用 protobuf 示例

```go
package main

import (
	"fmt"

	"../proto"

	"github.com/golang/protobuf/proto"
)

func main() {
	hello1 := &hello.Message{
		Id:      *proto.Int32(99),
		Message: *proto.String("hello world"),
	}

	data, err := proto.Marshal(hello1)
	if err != nil {
		fmt.Println("marshaling error: ", err)
	}

	hello2 := &hello.Message{}
	err = proto.Unmarshal(data, hello2)
	if err != nil {
		fmt.Println("unmarshaling error: ", err)
	}

	fmt.Println("ID: ", hello2.GetId())
	fmt.Println("Message: ", hello2.GetMessage())
}
```

**输出**

```bash
ID:  99
Message:  hello world
```

**附**：工程目录结构

```bash
├── proto
│   ├── hello.pb.go
│   └── hello.proto
└── main
    └── protobuf.go
```

### 数据结构有嵌套

**功能：**使用 protobuf

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/protobuf/2.tar.gz)

1. 定义 proto 文件

```basic
syntax = "proto3";

package hello;

enum ErrorCode {
    EnumSuccess = 0;
    EnumError = 1;
    EnumUnknown = 2;
}

message Message {
    int32 id = 1;
    string message = 2;
    ErrorCode errorCode = 3;
    repeated string extra = 4;
}

message MessageBox {
    repeated Message messages = 1;
}
```

2. 利用 protoc 编译 proto 文件，生成对应的 Golang 文件，命令如下（根据实际情况替换目录）

```bash
protoc.exe --proto_path=/d/Blog/archives/go/protobuf/2/proto --go_out=/d/Blog/archives/go/protobuf/2/proto hello.proto
```

3. 使用 protobuf 示例

```go
package main

import (
	"fmt"

	"../proto"

	"github.com/golang/protobuf/proto"
)

func main() {
	message1 := &hello.Message{
		Id:        *proto.Int32(99),
		Message:   *proto.String("hello world 1"),
		ErrorCode: hello.ErrorCode_EnumSuccess,
		Extra: []string{
			*proto.String("protobuf"),
			*proto.String("example"),
		},
	}

	message2 := &hello.Message{
		Id:        *proto.Int32(100),
		Message:   *proto.String("hello world 2"),
		ErrorCode: hello.ErrorCode_EnumSuccess,
		Extra: []string{
			*proto.String("protobuf"),
			*proto.String("example"),
		},
	}

	messageBox := &hello.MessageBox{}
	messageBox.Messages = append(messageBox.Messages, message1)
	messageBox.Messages = append(messageBox.Messages, message2)

	data, err := proto.Marshal(messageBox)
	if err != nil {
		fmt.Println("marshaling error: ", err)
	}

	messageBox2 := &hello.MessageBox{}
	err = proto.Unmarshal(data, messageBox2)
	if err != nil {
		fmt.Println("unmarshaling error: ", err)
	}

	messages := messageBox2.GetMessages()
	if messages != nil {
		for _, message := range messages {
			fmt.Println("ID: ", message.GetId())
			fmt.Println("Message: ", message.GetMessage())
			fmt.Println("ErrorCode: ", message.GetErrorCode())
			fmt.Println("Extra: ", message.GetExtra())
		}
	}
}
```

**输出**

```bash
ID:  99
Message:  hello world 1
ErrorCode:  EnumSuccess
Extra:  [protobuf example]
ID:  100
Message:  hello world 2
ErrorCode:  EnumSuccess
Extra:  [protobuf example]
```

**附**：工程目录结构

```bash
├── proto
│   ├── hello.pb.go
│   └── hello.proto
└── main
    └── protobuf.go
```
## Redis 客户端

### Redis 集群

**功能：**连接 redis 集群，进行存取操作

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/redis/redis_cluster.go)

```go
package main

import (
	"fmt"
	"time"

	"github.com/go-redis/redis"
)

func main() {
	client := redis.NewClusterClient(&redis.ClusterOptions{
		Addrs: []string{
			"192.168.0.3:6371",
			"192.168.0.3:6372",
			"192.168.0.3:6373"},
		Password:           "", // no password set
		PoolSize:           50,
		ReadTimeout:        30 * time.Second,
		WriteTimeout:       30 * time.Second,
		PoolTimeout:        30 * time.Second,
		IdleCheckFrequency: 2 * time.Minute,
	})

	pong, err := client.Ping().Result()
	fmt.Println(pong, ", ", err)

	err = client.Set("key", "value", 0).Err()
	if err != nil {
		panic(err)
	}

	val, err := client.Get("key").Result()
	if err != nil {
		panic(err)
	}
	fmt.Println("key", val, ", ", err)

	val2, err := client.Get("key2").Result()
	if err == redis.Nil {
		fmt.Println("key2 not existed", ", ", err)
	} else if err != nil {
		panic(err)
	} else {
		fmt.Println("key2", val2, ", ", err)
	}

	existed, err := client.Exists("key3").Result()
	if err != nil {
		panic(err)
	}
	if existed == 0 {
		fmt.Println("key3 not existed", ", ", err)
	} else {
		fmt.Println("key3 existed", ", ", err)
	}
}
```

**输出**

```bash
PONG ,  <nil>
key value ,  <nil>
key2 not existed ,  redis: nil
key3 not existed ,  <nil>
```

### Redis Server

**功能：**连接 redis server，进行存取操作

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/redis/redis.go)

```go
package main

import (
	"fmt"
	"time"

	"github.com/go-redis/redis"
)

func main() {
	client := redis.NewClient(&redis.Options{
		Addr:               "192.168.2.99:6379",
		Password:           "", // no password set,
		DB:                 1,
		PoolSize:           50,
		ReadTimeout:        30 * time.Second,
		WriteTimeout:       30 * time.Second,
		PoolTimeout:        30 * time.Second,
		IdleCheckFrequency: 2 * time.Minute,
	})

	pong, err := client.Ping().Result()
	fmt.Println(pong, ", ", err)

	err = client.Set("key", "value", 0).Err()
	if err != nil {
		panic(err)
	}

	val, err := client.Get("key").Result()
	if err != nil {
		panic(err)
	}
	fmt.Println("key", val, ", ", err)

	val2, err := client.Get("key2").Result()
	if err == redis.Nil {
		fmt.Println("key2 not existed", ", ", err)
	} else if err != nil {
		panic(err)
	} else {
		fmt.Println("key2", val2, ", ", err)
	}

	existed, err := client.Exists("key3").Result()
	if err != nil {
		panic(err)
	}
	if existed == 0 {
		fmt.Println("key3 not existed", ", ", err)
	} else {
		fmt.Println("key3 existed", ", ", err)
	}
}
```

**输出**

```bash
PONG ,  <nil>
key value ,  <nil>
key2 not existed ,  redis: nil
key3 not existed ,  <nil>
```

## HTTP 服务器

**功能：**

- 启动一个 HTTP 服务器，监听 12306 端口

- 支持的请求

  | 请求类型 | 请求 URL | 备注 |
  | -------- | -------- | ---- |
  | `GET`    | `/`      |      |

### 基础 HTTP 服务器

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/http/server1.go)

```go
package main

import (
	"fmt"
	"log"
	"net/http"
)

type Hello struct{}

func (h Hello) ServeHTTP(
	w http.ResponseWriter,
	r *http.Request) {
	fmt.Fprint(w, "Hello World!")
}

func main() {
	h := Hello{}
	err := http.ListenAndServe("localhost:12306", h)
	if err != nil {
		log.Fatal(err)
	}
}
```

**输出**

```bash
$ curl http://localhost:12306 -s
Hello World!
```

**wrk 压力测试**

> 服务器压测表现良好，平均每秒能够处理 5 W 个请求。

```bash
[root@localhost ~]# wrk -t2 -c2000 -d10 http://192.168.2.99:12306/ 
Running 10s test @ http://192.168.2.99:12306/
  2 threads and 2000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    73.61ms  227.39ms   2.00s    90.46%
    Req/Sec    25.59k     3.05k   30.56k    74.00%
  509425 requests in 10.07s, 62.67MB read
  Socket errors: connect 0, read 0, write 0, timeout 2085
Requests/sec:  50577.10
Transfer/sec:      6.22MB
```

### gin 基础 HTTP 服务器

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/http/server2.go)

```go
package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()

	router.GET("/", func(c *gin.Context) {
		c.String(http.StatusOK, "Hello World")
	})

	router.Run(":12306")
}
```

**输出**

- 服务端启动成功，输出如下信息

```bash
[GIN-debug] [WARNING] Creating an Engine instance with the Logger and Recovery middleware already attached.
[GIN-debug] [WARNING] Running in "debug" mode. Switch to "release" mode in production.
 - using env:	export GIN_MODE=release
 - using code:	gin.SetMode(gin.ReleaseMode)
[GIN-debug] GET    /                         --> main.main.func1 (3 handlers)
[GIN-debug] Listening and serving HTTP on :12306
```

- 通过 CURL 访问
```bash
$ curl http://localhost:12306/ -s
Hello World
```

### gin 处理多路由请求

**功能：**

- 启动一个 HTTP 服务器，监听 12306 端口

- 支持的请求

  | 请求类型     | 请求 URL       | 备注         |
  | ------------ | -------------- | ------------ |
  | `GET`        | `/`            |              |
  | `GET` `POST` | `/api/version` | 获取版本信息 |
  | `POST`       | `/debug/ping`  | PING         |

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/http/server_multirouter.go)

```go
package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func version(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{"code": 0, "version": "v1.0.1.0"})
}

func ping(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{"code": 0, "message": "pong"})
}

func main() {
	router := gin.Default()
	rGroup := router.Group("api")
	{
		rGroup.GET("version", version)
	}

	rGroup = router.Group("debug")
	{
		rGroup.GET("ping", ping)
		rGroup.POST("ping", ping)
	}

	router.GET("/", func(c *gin.Context) {
		c.String(http.StatusOK, "Hello World")
	})

	router.Run(":12306")
}
```

**输出**

- 服务端启动成功，处理请求，输出如下信息

```bash
[GIN-debug] [WARNING] Creating an Engine instance with the Logger and Recovery middleware already attached.
[GIN-debug] [WARNING] Running in "debug" mode. Switch to "release" mode in production.
 - using env:	export GIN_MODE=release
 - using code:	gin.SetMode(gin.ReleaseMode)
[GIN-debug] GET    /api/version              --> main.version (3 handlers)
[GIN-debug] GET    /debug/ping               --> main.ping (3 handlers)
[GIN-debug] POST   /debug/ping               --> main.ping (3 handlers)
[GIN-debug] GET    /                         --> main.main.func1 (3 handlers)
[GIN-debug] Listening and serving HTTP on :12306
[GIN] 2018/04/22 - 23:50:55 | 404 |            0s |             ::1 | POST     /api/version
[GIN] 2018/04/22 - 23:51:02 | 200 |            0s |             ::1 | GET      /api/version
[GIN] 2018/04/22 - 23:51:13 | 404 |            0s |             ::1 | GET      /api/ping
[GIN] 2018/04/22 - 23:51:29 | 200 |            0s |             ::1 | GET      /api/version
```

- 通过 CURL 访问
```bash
$ curl http://localhost:12306/api/version -X GET -s
{"code":0,"version":"v1.0.1.0"}
$ curl http://localhost:12306/api/version -X POST -s
404 page not found

$ curl http://localhost:12306/debug/ping -X POST -s
{"code":0,"message":"pong"}
$ curl http://localhost:12306/debug/ping -X GET -s
{"code":0,"message":"pong"}

$ curl http://localhost:12306/ -X GET -s
Hello World
$ curl http://localhost:12306/ -X POST -s
404 page not found
```

### gin 支持跨域

- 定义跨域中间件

```go
func Cors() gin.HandlerFunc {
	return func(c *gin.Context) {
		method := c.Request.Method
		origin := c.Request.Header.Get("Origin")
		var headerKeys []string
		for k, _ := range c.Request.Header {
			headerKeys = append(headerKeys, k)
		}

		headerStr := strings.Join(headerKeys, ", ")
		if headerStr != "" {
			headerStr = fmt.Sprintf("access-control-allow-origin, access-control-allow-headers, %s", headerStr)
		} else {
			headerStr = "access-control-allow-origin, access-control-allow-headers"
		}
		if origin != "" {
			c.Writer.Header().Set("Access-Control-Allow-Origin", "*")
			c.Header("Access-Control-Allow-Origin", "*")
			c.Header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE, UPDATE")
			c.Header("Access-Control-Allow-Headers", "Authorization, Content-Length, X-CSRF-Token, Token,session,X_Requested_With,Accept, Origin, Host, Connection, Accept-Encoding, Accept-Language, DNT, X-CustomHeader, Keep-Alive, User-Agent, X-Requested-With, If-Modified-Since, Cache-Control, Content-Type, Pragma")
			c.Header("Access-Control-Expose-Headers", "Content-Length, Access-Control-Allow-Origin, Access-Control-Allow-Headers, Cache-Control, Content-Language, Content-Type, Expires, Last-Modified, Pragma, FooBar")
			c.Header("Access-Control-Max-Age", "172800")
			c.Header("Access-Control-Allow-Credentials", "false")
			c.Set("content-type", "application/json")
		}

		c.Next()
	}
}
```

- 添加跨域中间件

```go
router.Use(Cors())
```

## HTTP 客户端

**功能：**HTTP 客户端，请求 http://localhost:12306/api/version

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/http/client.go)

```go
package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
)

func main() {
	client := &http.Client{}
	url := "http://localhost:12306/api/version"

	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		panic(err)
	}

	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	code := resp.StatusCode
	if code == http.StatusOK {
		body, _ := ioutil.ReadAll(resp.Body)
		fmt.Println("Code: ", code, ", Body: ", string(body))
	} else {
		fmt.Println("Code: ", resp.StatusCode)
	}
}
```

**输出**

​	当启动 HTTP 服务器端并能够处理该请求时，客户端返回结果如下所示

```bash
Code:  200 , Body:  {"code":0,"version":"v1.0.1.0"}
```

## 程序优雅退出（信号处理）

**功能：**

- 程序捕获信号，执行清理动作之后，优雅地退出
- 一般地，捕获 SIGINT 信号（`Ctrl + C` 产生）、SIGTERM 信号（`kill PID`）即可

**点击下载：**[源码](https://dudebing99.github.io/Blog/archives/go/signal/signal.go)

```go
package main

import "fmt"
import "os"
import "os/signal"
import "syscall"

func main() {
	// Go signal notification works by sending `os.Signal`
	// values on a channel. We'll create a channel to
	// receive these notifications (we'll also make one to
	// notify us when the program can exit).
	sigs := make(chan os.Signal, 1)
	done := make(chan bool, 1)
	// `signal.Notify` registers the given channel to
	// receive notifications of the specified signals.
	signal.Notify(sigs, syscall.SIGINT, syscall.SIGTERM)
	// This goroutine executes a blocking receive for
	// signals. When it gets one it'll print it out
	// and then notify the program that it can finish.
	go func() {
		sig := <-sigs
		fmt.Println()
		fmt.Println(sig)
		done <- true
	}()
	// The program will wait here until it gets the
	// expected signal (as indicated by the goroutine
	// above sending a value on `done`) and then exit.
	fmt.Println("awaiting signal")
	<-done
	fmt.Println("exiting")
}
```

**输出**

启动程序，按 `Ctrl + C`，输出如下

```bash
awaiting signal

interrupt
exiting
```
## 阿里云 OSS 上传文件

```go
package main

import (
    "fmt"
    "os"
    "github.com/aliyun/aliyun-oss-go-sdk/oss"
)

func main() {
    // 创建OSSClient实例。
  client, err := oss.New("your-endpoint(oss-cn-qingdao.aliyuncs.com)", "your-api-key", "your-api-secret")
    if err != nil {
        fmt.Println("Error:", err)
        os.Exit(-1)
    }

    // 获取存储空间。
    bucket, err := client.Bucket("your-bucket")
    if err != nil {
        fmt.Println("Error:", err)
        os.Exit(-1)
    }

    // 上传本地文件。
    err = bucket.PutObjectFromFile("hello/world/cor.jpeg", "/Users/kevin/Downloads/cor.jpeg")
    if err != nil {
        fmt.Println("Error:", err)
        os.Exit(-1)
    }
}
```

## JWT

**功能：**JWT 生成、校验、刷新 token

```go
package main

import (
	"errors"
	"fmt"
	"github.com/dgrijalva/jwt-go"
	"github.com/gin-gonic/gin"
	"net/http"
	"time"
)

func main() {
	r := gin.Default()
	r.GET("/login/:username/:password", login)
	r.GET("/verify/:token", verify)
	r.GET("/refresh/:token", refresh)
	r.GET("/sayHello/:token", sayHello)
	r.Run(":9090")
}

const (
	ErrorReason_ServerBusy = "服务器繁忙"
	ErrorReason_ReLogin    = "请重新登陆"
)

func sayHello(c *gin.Context) {
	strToken := c.Param("token")
	claim, err := verifyAction(strToken)
	if err != nil {
		c.String(http.StatusNotFound, err.Error())
		return
	}
	c.String(http.StatusOK, "hello,", claim.Username)
}

type JWTClaims struct { // token里面添加用户信息，验证token后可能会用到用户信息
	jwt.StandardClaims
	UserID      int      `json:"user_id"`
	Password    string   `json:"password"`
	Username    string   `json:"username"`
	FullName    string   `json:"full_name"`
	Permissions []string `json:"permissions"`
}

var (
	Secret     = "dong_tech" // 加盐
	ExpireTime = 3600        // token有效期
)

func login(c *gin.Context) {
	username := c.Param("username")
	password := c.Param("password")
	claims := &JWTClaims{
		UserID:      1,
		Username:    username,
		Password:    password,
		FullName:    username,
		Permissions: []string{},
	}
	claims.IssuedAt = time.Now().Unix()
	claims.ExpiresAt = time.Now().Add(time.Second * time.Duration(ExpireTime)).Unix()
	signedToken, err := getToken(claims)
	if err != nil {
		c.String(http.StatusNotFound, err.Error())
		return
	}
	c.String(http.StatusOK, signedToken)
}

func verify(c *gin.Context) {
	strToken := c.Param("token")
	claim, err := verifyAction(strToken)
	if err != nil {
		c.String(http.StatusNotFound, err.Error())
		return
	}
	c.String(http.StatusOK, "verify,", claim.Username)
}

func refresh(c *gin.Context) {
	strToken := c.Param("token")
	claims, err := verifyAction(strToken)
	if err != nil {
		c.String(http.StatusNotFound, err.Error())
		return
	}
	claims.ExpiresAt = time.Now().Unix() + (claims.ExpiresAt - claims.IssuedAt)
	signedToken, err := getToken(claims)
	if err != nil {
		c.String(http.StatusNotFound, err.Error())
		return
	}
	c.String(http.StatusOK, signedToken)
}

func verifyAction(strToken string) (*JWTClaims, error) {
	token, err := jwt.ParseWithClaims(strToken, &JWTClaims{}, func(token *jwt.Token) (interface{}, error) {
		return []byte(Secret), nil
	})
	if err != nil {
		return nil, errors.New(ErrorReason_ServerBusy)
	}
	claims, ok := token.Claims.(*JWTClaims)
	if !ok {
		return nil, errors.New(ErrorReason_ReLogin)
	}
	if err := token.Claims.Valid(); err != nil {
		return nil, errors.New(ErrorReason_ReLogin)
	}
	fmt.Println("verify")
	return claims, nil
}

func getToken(claims *JWTClaims) (string, error) {
	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	signedToken, err := token.SignedString([]byte(Secret))
	if err != nil {
		return "", errors.New(ErrorReason_ServerBusy)
	}
	return signedToken, nil
}
```

