package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
)

func main() {
	client := &http.Client{}
	url := "http://localhost:12306/api/version"

	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		panic(err)
	}

	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	code := resp.StatusCode
	if code == http.StatusOK {
		body, _ := ioutil.ReadAll(resp.Body)
		fmt.Println("Code: ", code, ", Body: ", string(body))
	} else {
		fmt.Println("Code: ", resp.StatusCode)
	}
}
