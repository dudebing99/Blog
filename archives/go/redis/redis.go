package main

import (
	"fmt"
	"time"

	"github.com/go-redis/redis"
)

func main() {
	client := redis.NewClient(&redis.Options{
		Addr:               "192.168.2.99:6379",
		Password:           "", // no password set,
		DB:                 1,
		PoolSize:           50,
		ReadTimeout:        30 * time.Second,
		WriteTimeout:       30 * time.Second,
		PoolTimeout:        30 * time.Second,
		IdleCheckFrequency: 2 * time.Minute,
	})

	pong, err := client.Ping().Result()
	fmt.Println(pong, ", ", err)

	err = client.Set("key", "value", 0).Err()
	if err != nil {
		panic(err)
	}

	val, err := client.Get("key").Result()
	if err != nil {
		panic(err)
	}
	fmt.Println("key", val, ", ", err)

	val2, err := client.Get("key2").Result()
	if err == redis.Nil {
		fmt.Println("key2 not existed", ", ", err)
	} else if err != nil {
		panic(err)
	} else {
		fmt.Println("key2", val2, ", ", err)
	}

	existed, err := client.Exists("key3").Result()
	if err != nil {
		panic(err)
	}
	if existed == 0 {
		fmt.Println("key3 not existed", ", ", err)
	} else {
		fmt.Println("key3 existed", ", ", err)
	}
}
