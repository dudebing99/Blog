[TOC]

------

## Hello World

**功能：**向控制台打印 Hello World

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/hello_world/hello_world.go)

```go
package main

import "fmt"

func main() {
	fmt.Printf("%s\n", "Hello World")
}
```

**输出**

```basic
Hello World
```

## 自定义结构体 slice 排序

**功能：**自定义结构体 slice 对象，对其进行升序、降序排序

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/sort/slice_sort.go)

```go
package main

import (
	"fmt"
	"sort"
)

type ContentScore struct {
	ContentID int64
	Score     float32
}

type ContentScoreList []ContentScore

func (csl ContentScoreList) Len() int {
	return len(csl)
}

func (csl ContentScoreList) Swap(i, j int) {
	csl[i], csl[j] = csl[j], csl[i]
}

// 按照 score 逆序排序
func (csl ContentScoreList) Less(i, j int) bool {
	return csl[j].Score < csl[i].Score
}

func main() {
	contentScoreList := ContentScoreList{
		{100, 12.34},
		{200, 9.35},
		{99, 7.90},
		{400, 8.91},
	}

	fmt.Println("按照 score 逆序排序")
	sort.Sort(ContentScoreList(contentScoreList))
	for _, contentScore := range contentScoreList {
		fmt.Printf("Conent ID: %d, Score: %f\n", contentScore.ContentID, contentScore.Score)
	}

	fmt.Println("按照 score 升序排序")
	sort.Sort(sort.Reverse((ContentScoreList(contentScoreList))))
	for _, contentScore := range contentScoreList {
		fmt.Printf("Conent ID: %d, Score: %f\n", contentScore.ContentID, contentScore.Score)
	}
}
```

**输出**

```basic
按照 score 逆序排序
Conent ID: 100, Score: 12.340000
Conent ID: 200, Score: 9.350000
Conent ID: 400, Score: 8.910000
Conent ID: 99, Score: 7.900000
按照 score 升序排序
Conent ID: 99, Score: 7.900000
Conent ID: 400, Score: 8.910000
Conent ID: 200, Score: 9.350000
Conent ID: 100, Score: 12.340000
```

## map 排序

**功能：**借助 slice，实现 map 的按序输出

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/sort/map_sort.go)

```go
package main

import (
	"fmt"
	"sort"
)

func main() {
	// map 本身无序，如果需要按序输出，需要借助一些技巧，如下所示
	var m = map[string]int{
		"unix":         0,
		"python":       1,
		"go":           2,
		"javascript":   3,
		"testing":      4,
		"philosophy":   5,
		"startups":     6,
		"productivity": 7,
		"hn":           8,
		"reddit":       9,
		"C++":          10,
	}
	// 遍历输出
	fmt.Println("Before sort")
	for key, value := range m {
		fmt.Println("Key: ", key, ", Value: ", value)
	}

	// 保存所有的 key
	var keys []string
	for k := range m {
		keys = append(keys, k)
	}
	// key 排序
	sort.Strings(keys)

	fmt.Println("After sort")
	// 利用排过序的 key 找到对应的 value
	for _, k := range keys {
		fmt.Println("Key:", k, ", Value:", m[k])
	}
}
```
**输出**
```basic
Before sort
Key:  C++ , Value:  10
Key:  go , Value:  2
Key:  javascript , Value:  3
Key:  testing , Value:  4
Key:  philosophy , Value:  5
Key:  startups , Value:  6
Key:  productivity , Value:  7
Key:  reddit , Value:  9
Key:  unix , Value:  0
Key:  python , Value:  1
Key:  hn , Value:  8
After sort
Key: C++ , Value: 10
Key: go , Value: 2
Key: hn , Value: 8
Key: javascript , Value: 3
Key: philosophy , Value: 5
Key: productivity , Value: 7
Key: python , Value: 1
Key: reddit , Value: 9
Key: startups , Value: 6
Key: testing , Value: 4
Key: unix , Value: 0
```

## Redis 客户端

### Redis 集群

**功能：**连接 redis 集群，进行存取操作

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/redis/redis_cluster.go)

```go
package main

import (
	"fmt"

	"github.com/go-redis/redis"
)

func main() {
	client := redis.NewClusterClient(&redis.ClusterOptions{
		Addrs: []string{
			"192.168.0.3:6371",
			"192.168.0.3:6372",
			"192.168.0.3:6373"},
		Password: "", // no password set
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
```

**输出**

```basic
PONG ,  <nil>
key value ,  <nil>
key2 not existed ,  redis: nil
key3 not existed ,  <nil>
```

### Redis Server

**功能：**连接 redis server，进行存取操作

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/redis/redis.go)

```go
package main

import (
	"fmt"

	"github.com/go-redis/redis"
)

func main() {
	client := redis.NewClient(&redis.Options{
		Addr:     "192.168.2.99:6379",
		Password: "", // no password set,
		DB:       1,
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
```

**输出**

```basic
PONG ,  <nil>
key value ,  <nil>
key2 not existed ,  redis: nil
key3 not existed ,  <nil>
```

## HTTP 服务器

### 基础 HTTP 服务器

**功能：**

- 启动一个 HTTP 服务器，监听 12306 端口

- 支持的请求

  | 请求类型 | 请求 URL | 备注 |
  | -------- | -------- | ---- |
  | `GET`    | `/`      |      |

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/http/server.go)

```go
package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()

	router.GET("/", func(c *gin.Context) {
		c.String(http.StatusOK, "Hello World")
	})

	router.Run(":12306")
}
```

**输出**

- 服务端启动成功，输出如下信息

```basic
[GIN-debug] [WARNING] Creating an Engine instance with the Logger and Recovery middleware already attached.
[GIN-debug] [WARNING] Running in "debug" mode. Switch to "release" mode in production.
 - using env:	export GIN_MODE=release
 - using code:	gin.SetMode(gin.ReleaseMode)
[GIN-debug] GET    /                         --> main.main.func1 (3 handlers)
[GIN-debug] Listening and serving HTTP on :12306
```

- 通过 CURL 访问
```basic
$ curl http://localhost:12306/ -s
Hello World
```

### 处理多路由请求的 HTTP 服务器

**功能：**

- 启动一个 HTTP 服务器，监听 12306 端口

- 支持的请求

  | 请求类型     | 请求 URL       | 备注         |
  | ------------ | -------------- | ------------ |
  | `GET`        | `/`            |              |
  | `GET` `POST` | `/api/version` | 获取版本信息 |
  | `POST`       | `/debug/ping`  | PING         |

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/http/server_multirouter.go)

```go
package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func version(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{"code": 0, "version": "v1.0.1.0"})
}

func ping(c *gin.Context) {
	c.JSON(http.StatusOK, gin.H{"code": 0, "message": "pong"})
}

func main() {
	router := gin.Default()
	rGroup := router.Group("api")
	{
		rGroup.GET("version", version)
	}

	rGroup = router.Group("debug")
	{
		rGroup.GET("ping", ping)
		rGroup.POST("ping", ping)
	}

	router.GET("/", func(c *gin.Context) {
		c.String(http.StatusOK, "Hello World")
	})

	router.Run(":12306")
}
```

**输出**

- 服务端启动成功，处理请求，输出如下信息

```basic
[GIN-debug] [WARNING] Creating an Engine instance with the Logger and Recovery middleware already attached.
[GIN-debug] [WARNING] Running in "debug" mode. Switch to "release" mode in production.
 - using env:	export GIN_MODE=release
 - using code:	gin.SetMode(gin.ReleaseMode)
[GIN-debug] GET    /api/version              --> main.version (3 handlers)
[GIN-debug] GET    /debug/ping               --> main.ping (3 handlers)
[GIN-debug] POST   /debug/ping               --> main.ping (3 handlers)
[GIN-debug] GET    /                         --> main.main.func1 (3 handlers)
[GIN-debug] Listening and serving HTTP on :12306
[GIN] 2018/04/22 - 23:50:55 | 404 |            0s |             ::1 | POST     /api/version
[GIN] 2018/04/22 - 23:51:02 | 200 |            0s |             ::1 | GET      /api/version
[GIN] 2018/04/22 - 23:51:13 | 404 |            0s |             ::1 | GET      /api/ping
[GIN] 2018/04/22 - 23:51:29 | 200 |            0s |             ::1 | GET      /api/version
```

- 通过 CURL 访问
```basic
$ curl http://localhost:12306/api/version -X GET -s
{"code":0,"version":"v1.0.1.0"}
$ curl http://localhost:12306/api/version -X POST -s
404 page not found

$ curl http://localhost:12306/debug/ping -X POST -s
{"code":0,"message":"pong"}
$ curl http://localhost:12306/debug/ping -X GET -s
{"code":0,"message":"pong"}

$ curl http://localhost:12306/ -X GET -s
Hello World
$ curl http://localhost:12306/ -X POST -s
404 page not found
```
