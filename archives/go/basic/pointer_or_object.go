package main

import (
	"fmt"
)

type T struct {
	identity string
}

func (t T) f1() {
	t.identity = "lucy"
}

func (t *T) f2() {
	t.identity = "lily"
}

func main() {
	t := T{"hello"}

	fmt.Println(t.identity)
	t.f1()
	fmt.Println(t.identity)

	t.f2()
	fmt.Println(t.identity)
}
