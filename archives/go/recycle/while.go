package main

import (
	"fmt"
	"time"
)

func main() {
	var count uint32 = 0
	for true {
		count++
		if count == 3 {
			goto loop
		}
		fmt.Println("count: ", count, " in infinite loop")
		time.Sleep(time.Second * 3)
	}
loop:
	fmt.Println("Go to loop")
}
