package main

import (
	"fmt"
	"sync"
	"time"
)
var(
	wg sync.WaitGroup
	mu sync.Mutex
	done = make([]chan int, 5)
)
func funcA(){
	for {
		<-done[0]
		fmt.Printf("A")
		time.Sleep(2*time.Second)
		done[1]<-1
	}

}
func funcB(){
	for {
		<-done[0]
		fmt.Printf("B")
		done[1]<-1
	}

}
func funcC(){
	for{
		<-done[1]
		fmt.Printf("C");
		done[2]<-2
	}

}
func funcD(){
	for {
		<-done[2]
		fmt.Printf("D");
		done[3]<-3
	}

}
func funcE(){
	for {
		<-done[3]
		fmt.Printf("E");
		done[0]<-1
	}

}
func main(){
	var str string

	for i:=0;i<5;i++{
		done[i] = make(chan int, 1)
	}
	done[0]<-1
	go funcA();
	go funcB();
	go funcC();
	go funcD();
	go funcE();
	fmt.Scan(&str)
}