package main

import "fmt"

// 属性的开头字母是大写或小写决定该属性的访问权限，
// 开头字母是大写的则在其他包中可以访问，否则只能在本包中访问
type Human struct {
	Age  int8
	Sex  byte
	name string
}

func NewHuman(age int8, sex byte, name_ string) (h *Human) {
	h = &Human{
		Age:  age,
		Sex:  sex,
		name: name_,
	}
	return
}

// 类方法声明
func (h Human) printInfo() {
	fmt.Printf("Age: %d, Sex: %c, Name: %s\n", h.Age, h.Sex, h.name)
	h.name = "sb"
}

// 类方法声明
func (h *Human) printInfo2() {
	fmt.Printf("Age: %d, Sex: %c, Name: %s\n", h.Age, h.Sex, h.name)
	h.name = "sb"
}

// 匿名结构体
func printInfo() {
	h := struct {
		Age  int8
		Name string
	}{22, "jiakong"}

	fmt.Printf("%s is %d\n", h.Name, h.Age)
}

func main() {
	h := Human{99, 'M', "jiakong"}

	h.printInfo()
	fmt.Println("after pass-by object: ", h.name)
	h.printInfo2()
	fmt.Println("after pass-by pointer: ", h.name)

	printInfo()

	// 实例化对象
	// 1. 值对象
	h1 := Human{}
	h1.name = "sb"

	h2 := Human{99, 'M', "sb"}
	h2.name = "sb"

	h3 := Human{
		Age: 99,
		Sex: 'M',
	}
	h3.name = "sb"

	// 2. 指针对象
	h4 := new(Human)
	h4.name = "sb"

	h5 := &Human{}
	h5.name = "sb"

	h6 := &Human{
		Sex: 'M',
	}
	h6.name = "sb"

	// 3. 构造函数
	h7 := NewHuman(22, 'M', "jiakong")
	fmt.Println(h7.Age, h7.Sex, h7.name)
}