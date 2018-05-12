package main

import "fmt"

func add() func(int) int {
	sum := 0
	fmt.Println("sum: ", sum)
	return func(x int) int {
		sum += x
		fmt.Println("x: ", x, ", sum += x: ", sum)
		return sum
	}
}

func main() {
	fmt.Println("declare f()")
	f := add()

	fmt.Println("call f()")
	for i := 0; i < 10; i++ {
		fmt.Println("f(i): ", f(i))
	}
}
