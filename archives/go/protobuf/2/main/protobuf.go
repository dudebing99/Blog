package main

import (
	"fmt"

	"../proto"

	"github.com/golang/protobuf/proto"
)

func main() {
	message1 := &hello.Message{
		Id:        *proto.Int32(99),
		Message:   *proto.String("hello world 1"),
		ErrorCode: hello.ErrorCode_EnumSuccess,
		Extra: []string{
			*proto.String("protobuf"),
			*proto.String("example"),
		},
	}

	message2 := &hello.Message{
		Id:        *proto.Int32(100),
		Message:   *proto.String("hello world 2"),
		ErrorCode: hello.ErrorCode_EnumSuccess,
		Extra: []string{
			*proto.String("protobuf"),
			*proto.String("example"),
		},
	}

	messageBox := &hello.MessageBox{}
	messageBox.Messages = append(messageBox.Messages, message1)
	messageBox.Messages = append(messageBox.Messages, message2)

	data, err := proto.Marshal(messageBox)
	if err != nil {
		fmt.Println("marshaling error: ", err)
	}

	messageBox2 := &hello.MessageBox{}
	err = proto.Unmarshal(data, messageBox2)
	if err != nil {
		fmt.Println("unmarshaling error: ", err)
	}

	messages := messageBox2.GetMessages()
	if messages != nil {
		for _, message := range messages {
			fmt.Println("ID: ", message.GetId())
			fmt.Println("Message: ", message.GetMessage())
			fmt.Println("ErrorCode: ", message.GetErrorCode())
			fmt.Println("Extra: ", message.GetExtra())
		}
	}
}
