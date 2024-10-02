package main

import (
	"fmt"
	"sync"
)

var(
	buffer [5]int = [5]int{-1, -1, -1, -1, -1}
	index int
	wg sync.WaitGroup
	mu sync.Mutex
	espacio = make(chan int, 5)
	objetos = make(chan int, 5)

)

func productor(){
	for n:=0;n<20;n++{
		<-espacio
		mu.Lock()
		item := n*n
		index := n%5
		buffer[index] = item
		mu.Unlock()
		objetos<-1
		fmt.Printf("productor %d %d %v\n",index, item, buffer)
	}
	wg.Done()
}

func consumidor(){
	var item int
	for n:=0;n<20;n++{
		<-objetos
		mu.Lock()
		index = n%5
		item = buffer[index]
		buffer[index] = -1
		mu.Unlock()
		espacio<-1
		fmt.Printf("consumidor %d %d %v\n", index, item, buffer)
	}
	wg.Done()
}
func main(){
	objetos = make(chan int, 5)
	espacio = make(chan int, 5)
	for i:=0;i<5;i++{
		espacio<-1
	}
	wg.Add(2)
	go productor()
	go consumidor()
	wg.Wait()
}