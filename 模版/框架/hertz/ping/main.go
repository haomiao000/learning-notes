package main

import (
	"context"
	"time"

	"github.com/cloudwego/hertz/pkg/app"
	"github.com/cloudwego/hertz/pkg/app/server"
	"github.com/cloudwego/hertz/pkg/common/hlog"
)

func main() {
	h := server.New(server.WithHostPorts(":8080"))

	// 自定义中间件：打印请求状态和耗时
	h.Use(func(c context.Context, ctx *app.RequestContext) {
		start := time.Now()

		// 打印请求方法和路径
		hlog.Infof("Incoming request: %s %s", string(ctx.Method()), string(ctx.Request.URI().Path()))

		// 继续处理请求
		ctx.Next(c)

		// 打印响应状态码和耗时
		duration := time.Since(start)
		hlog.Infof("Response status: %d, Duration: %v", ctx.Response.StatusCode(), duration)
	})

	// 路由
	h.GET("/ping", func(c context.Context, ctx *app.RequestContext) {
		ctx.JSON(200, map[string]string{"message": "pong"})
	})

	// 启动服务
	h.Spin()
}