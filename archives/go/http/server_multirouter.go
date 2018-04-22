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
