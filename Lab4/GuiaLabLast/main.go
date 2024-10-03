package main

import (
	"fmt"
	"sync"
)

var (
	buffer [5]int = [5]int{-1, -1, -1, -1, -1}
	index int
	counter int = 0
	// controlConsumidor chan bool = make(chan bool, 5)
	vacio chan bool = make(chan bool, 1)
	lleno chan bool = make(chan bool, 1)
	wg sync.WaitGroup
	mutex sync.Mutex
)

func productor() {
	for n := 0; n < 20; n++ {
		mutex.Lock()
		item := n * n
		index = n % 5
		buffer[index] = item
		fmt.Printf("Productor %d %d %v\n", index, item, buffer)
		counter++
		if(counter == 5){
			lleno <- true
		}
		mutex.Unlock()
		if(counter == 5){
			<-vacio // esperar a que se vacie
		}
		// controlConsumidor <- true
	}
	wg.Done()
}

func consumidor() {
	var item int
	for n := 0; n < 20; n++ {
		if(counter == 0){
			<-lleno
		}
		mutex.Lock()
		index = n % 5
		// <- controlConsumidor
		item = buffer[index]
		buffer[index] = -1
		fmt.Printf("Consumidor %d %d %v\n", index, item, buffer)
		counter--
		mutex.Unlock()
		if(counter == 0){
			vacio <- true
		}
	}
	wg.Done()
}

func main() {
	wg.Add(2)
	// controlProductor<-true
	go productor()
	go consumidor()
	
	wg.Wait()
}