package main

import (
	"fmt"
)

type Father struct {
	CN string
}

func (this *Father) Say() {
	fmt.Println("大家好, 我是", this.CN)
}

type Mother struct {
	EN string
}

func (this *Mother) Say() {
	fmt.Println("Hello, I am", this.EN)
}

type Child1 struct {
	Father
	Age int8
}

type Child2 struct {
	Father
	Mother
	Age int8
}

func main() {
	child1 := new(Child1)
	child1.CN = "小呆比"
	child1.Age = 22
	child1.Say()

	child2 := new(Child2)
	child2.CN = "小呆比"
	child2.EN = "little silly B"
	child2.Father.Say()
	child2.Mother.Say()
}
