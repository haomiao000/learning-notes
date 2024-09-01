package service

type Manager interface {
	Add(a int64 , b int64)(int64)
}

type ServiceImpl struct {
	Manager Manager
}

func(s *ServiceImpl) Call(a int64 , b int64) (int64) {
	c := s.Manager.Add(a , b)
	return c
}