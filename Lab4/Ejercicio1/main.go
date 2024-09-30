package main

import(
	"fmt"
	"sync"
)

var(
	wg sync.WaitGroup
	done1 chan bool
	done2 chan bool
	done3 chan bool
)
func worker1(){
	<-done1
	fmt.Printf("Sistemas ")
	done2<-true
	wg.Done()
}
func worker2(){
	fmt.Printf("INF239 ")
	done1<-true
	wg.Done()
}
func worker3(){
	<-done2
	fmt.Printf("Operativos ")
	done3<-true
	wg.Done()
}
func worker4(){
	<-done3
	fmt.Printf("\n")
	wg.Done()
}
func main(){
	done1 = make(chan bool)
	done2 = make(chan bool)
	done3 = make(chan bool)
	wg.Add(4)
	go worker1()
	go worker2()
	go worker3()
	go worker4()
	wg.Wait()
}