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

	// 按照模板指定格式将时间以字符串输出
	strTime := time.Now().Format("2006-01-02 15:04:05")
	fmt.Println(strTime)
	strTime = time.Now().Format("2006/01/02 15")
	fmt.Println(strTime)
	strTime = time.Now().UTC().Add(8 * time.Hour).Format("20060102_1504")
	fmt.Println(strTime)
}
