package main

import (
	"fmt"
	"main/controller"
	"main/service"
)

func main() {
	m := controller.NewManager()
	impl := &service.ServiceImpl{
		Manager: m,
	}
	fmt.Println(impl.Call(1 , 2))
}