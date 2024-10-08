package main

import (
	"fmt"
	"sync"
)

var (
	buffer [5]int = [5]int{-1, -1, -1, -1, -1}
	index int
	controlConsumidor chan bool = make(chan bool, 5)
	controlProductor chan bool = make(chan bool, 5)
	wg sync.WaitGroup
	mutex sync.Mutex
)

func productor() {
	for n := 0; n < 20; n++ {
		item := n * n
		index = n % 5
		controlProductor <- true
		mutex.Lock()
		buffer[index] = item
		fmt.Printf("Productor %d %d %v\n", index, item, buffer)
		mutex.Unlock()
		controlConsumidor <- true
	}
	wg.Done()
}

func consumidor() {
	var item int
	for n := 0; n < 20; n++ {
		index = n % 5
		<- controlConsumidor
		mutex.Lock()
		item = buffer[index]
		buffer[index] = -1
		fmt.Printf("Consumidor %d %d %v\n", index, item, buffer)
		mutex.Unlock()
		<- controlProductor
	}
	wg.Done()
}

func main() {
	wg.Add(2)
	go consumidor()
	go productor()
	wg.Wait()
}