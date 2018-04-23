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

## for 循环

**功能：**输出九九乘法口诀表

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/recycle/for.go)

```go
package main

import "fmt"

func main() {
	for i := 1; i <= 9; i++ {
		for j := 1; j <= i; j++ {
			fmt.Printf("%d*%d=%d ", j, i, j*i)
		}
		fmt.Println("")
	}
}
```

**输出**

```basic
1*1=1 
1*2=2 2*2=4 
1*3=3 2*3=6 3*3=9 
1*4=4 2*4=8 3*4=12 4*4=16 
1*5=5 2*5=10 3*5=15 4*5=20 5*5=25 
1*6=6 2*6=12 3*6=18 4*6=24 5*6=30 6*6=36 
1*7=7 2*7=14 3*7=21 4*7=28 5*7=35 6*7=42 7*7=49 
1*8=8 2*8=16 3*8=24 4*8=32 5*8=40 6*8=48 7*8=56 8*8=64 
1*9=9 2*9=18 3*9=27 4*9=36 5*9=45 6*9=54 7*9=63 8*9=72 9*9=81 
```

**功能：**实现 while 逻辑（Golang 中无 while 循环，可借助 for 实现）

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/recycle/while.go)

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	var count uint32 = 0
	for true {
		count++
		if count == 3 {
			goto loop
		}
		fmt.Println("count: ", count, " in infinite loop")
		time.Sleep(time.Second * 3)
	}
loop:
	fmt.Println("Go to loop")
}
```

**输出**

```basic

count:  1  in infinite loop
count:  2  in infinite loop
Go to loop
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

## HTTP 客户端

**功能：**HTTP 客户端，请求 http://localhost:12306/api/version

**点击下载：**[源码](https://dudebing99.github.io/blog/archives/go/http/client.go)

```go
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
```

**输出**

​	备注：当启动 HTTP 服务器端并能够处理该请求时，客户端返回结果如下所示

```basic
Code:  200 , Body:  {"code":0,"version":"v1.0.1.0"}
```

