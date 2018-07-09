package main

import (
	"fmt"
	"log"
	"net/http"
)

type Hello struct{}

func (h Hello) ServeHTTP(
	w http.ResponseWriter,
	r *http.Request) {
	fmt.Fprint(w, "Hello World!")
}

func main() {
	h := Hello{}
	err := http.ListenAndServe("localhost:12306", h)
	if err != nil {
		log.Fatal(err)
	}
}
