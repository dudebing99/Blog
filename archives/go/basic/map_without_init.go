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
	kv[1] = "hello"
}
