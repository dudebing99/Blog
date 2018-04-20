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
