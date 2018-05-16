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
