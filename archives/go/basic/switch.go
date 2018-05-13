package main

import "fmt"
import "time"

func f0(i int) {
	// 包含条件表达式
	switch i {
	case 1:
		fmt.Println("one")
	case 2:
		fmt.Println("two")
	case 3:
		fmt.Println("three")
	default:
		fmt.Println("unexpected")
	}
}

func f1(i int) {
	// 包含条件表达式
	switch i {
	case 1:
		fmt.Println("one")
	case 2:
		fmt.Println("two")
		fallthrough
	case 3:
		fmt.Println("three")
	default:
		fmt.Println("unexpected")
	}
}

func f2(weekday time.Weekday) {
	// 包含条件表达式，多重条件
	switch weekday {
	case time.Saturday, time.Sunday:
		fmt.Println("It's the weekend")
	default:
		fmt.Println("It's a weekday")
	}
}

func f3(t time.Time) {
	// 不含条件表达式
	switch {
	case t.Hour() < 12:
		fmt.Println("It's at morning")
	case t.Hour() == 12:
		fmt.Println("It's at noon")
	case t.Hour() > 12:
		fmt.Println("It's after noon")
	}
}

func f4(i interface{}) {
	switch t := i.(type) {
	case bool:
		fmt.Println("I'm a bool")
	case int:
		fmt.Println("I'm an int")
	case string:
		fmt.Println("I'm a string")
	default:
		fmt.Printf("Type: %T\n", t)
	}
}

func main() {
	f0(2)
	f1(2)
	f2(time.Now().Weekday())
	f3(time.Now())
	f4(false)
	f4(99)
	f4("hello world")
}
