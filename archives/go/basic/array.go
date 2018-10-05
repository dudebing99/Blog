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