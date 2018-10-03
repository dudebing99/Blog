package main

import "fmt"

type LinkNode struct {
	data interface{}
	next *LinkNode
}

type Link struct {
	head *LinkNode
	tail *LinkNode
}

func (p *Link) Count() int {
	count := 0
	head := p.head
	for head != nil {
		head = head.next
		count++
	}

	return count
}

func (p *Link) InsertHead(data interface{}) {
	node := &LinkNode{
		data: data,
		next: nil,
	}

	if p.tail == nil && p.head == nil {
		p.tail = node
		p.head = node
		return
	}

	node.next = p.head
	p.head = node
}

func (p *Link) InsertTail(data interface{}) {
	node := &LinkNode{
		data: data,
		next: nil,
	}

	if p.tail == nil && p.head == nil {
		p.tail = node
		p.head = node
		return
	}

	p.tail.next = node
	p.tail = node
}

func (p *Link) Trans() {
	q := p.head
	for q != nil {
		fmt.Println(q.data)
		q = q.next
	}
}

func main() {
	var link Link
	for i := 0; i < 10; i++ {
		if i%2 == 0 {
			link.InsertHead(i)
		} else {
			link.InsertTail(fmt.Sprintf("str %d", i))
		}
	}

	link.Trans()

	fmt.Printf("Contains %d element(s)", link.Count())
}
