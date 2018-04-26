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
}
