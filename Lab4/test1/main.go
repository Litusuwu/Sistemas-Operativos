package main

import(
	"fmt"
	"sync"
)

var( 
	wg sync.WaitGroup
	mutex1 sync.Mutex
	mutex2 sync.Mutex
)
func worker1(){
	for x := 0; x< 10; x++{
		fmt.Printf("I like to ")
		mutex1.Unlock()
		mutex2.Lock()
		fmt.Println("systems")
	}
	wg.Done()
}
func worker2(){
	for x := 0; x< 10; x++{
		mutex1.Lock()
		fmt.Printf("study ")
		fmt.Printf("operating ")
		mutex2.Unlock()
	}
	wg.Done()
}
func main(){
	wg.Add(2)
	mutex1.Lock()
	mutex2.Lock()
	go worker1()
	go worker2()
	wg.Wait()
}