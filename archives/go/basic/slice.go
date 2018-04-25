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
