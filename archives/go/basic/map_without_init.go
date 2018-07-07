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
