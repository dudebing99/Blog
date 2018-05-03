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
