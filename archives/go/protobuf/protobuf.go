package main

import (
	"fmt"

	"../pb"

	"github.com/golang/protobuf/proto"
)

func main() {
	hello1 := &hello.Message{
		Id:      *proto.Int32(99),
		Message: *proto.String("hello world"),
	}

	data, err := proto.Marshal(hello1)
	if err != nil {
		fmt.Println("marshaling error: ", err)
	}

	hello2 := &hello.Message{}
	err = proto.Unmarshal(data, hello2)
	if err != nil {
		fmt.Println("unmarshaling error: ", err)
	}

	fmt.Println("ID: ", hello2.GetId())
	fmt.Println("Message: ", hello2.GetMessage())
}
