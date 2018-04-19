[TOC]

------

## Hello World

> **功能：**向控制台打印 Hello World
>
> **点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/hello_world/hello_world.go)

```go
package main

import "fmt"

func main() {
    fmt.Printf("%s\n", "Hello World")
}
```

## 自定义结构体 slice 排序

> **功能：**自定义结构体 slice 对象，对其进行升序、降序排序
>
> **点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/sort/slice_sort.go)

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

## map 排序

> **功能：**借助 slice，实现 map 的按序输出
>
> **点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/sort/map_sort.go)

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
```basic
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

