package main

import "fmt"

func main() {
	func(x, y int) {
		fmt.Printf("x + y = %d\n", x+y)
	}(19, 96)

	f := func(x, y int) int {
		return x * y
	}

	fmt.Printf("x * y = %d\n", f(16, 2))
}
