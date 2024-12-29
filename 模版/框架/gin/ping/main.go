package main 

import (
	gin "github.com/gin-gonic/gin"
)

func main() {
	// 创建一个默认的 Gin 路由引擎
	r := gin.Default()

	// 定义一个简单的 GET 路由
	r.GET("/ping", func(c *gin.Context) {
		// 返回 JSON 响应
		c.JSON(200, gin.H{
			"message": "pong",
		})
	})

	// 启动 HTTP 服务并监听 8080 端口
	r.Run(":8080")
}