package main

import (
	"encoding/json"
	"fmt"
)

type Person struct {
	Name        string `json:"User"`
	Age         int    `json:"Age"`
	Gender      bool   `json:",omitempty"`
	Profile     string
	OmitContent string `json:"-"`
	Count       int    `json:",string"`
}

func main() {
	var p *Person = &Person{
		Name:        "Kevin",
		Age:         22,
		Gender:      true,
		Profile:     "Coding Dog",
		OmitContent: "Hello World",
	}
	if j, err := json.Marshal(&p); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}

	var p2 *Person = &Person{
		Name:        "Kevin",
		Age:         22,
		Gender:      false,
		Profile:     "Coding Dog",
		OmitContent: "Hello World",
	}
	if j, err := json.Marshal(&p2); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}

	var p3 *Person = &Person{
		Name:        "Kevin",
		Gender:      false,
		Profile:     "Coding Dog",
		OmitContent: "Hello World",
	}
	if j, err := json.Marshal(&p3); err != nil {
		panic(err)
	} else {
		fmt.Println(string(j))
	}
}
