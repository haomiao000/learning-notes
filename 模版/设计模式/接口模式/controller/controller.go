package controller

type Manager struct {}

func (m *Manager)Add(a int64 , b int64) (int64) {
	return a+b
}
func NewManager() *Manager {
	return &Manager{}
}