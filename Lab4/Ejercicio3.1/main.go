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
	count := 5
	for {
		<-done[0]
		fmt.Printf("A")
		count--
		done[1]<-1
		time.Sleep(2*time.Second)
	}

}
func funcB(){
	count := 5
	for {
		<-done[4]
		fmt.Printf("B")
		count--
		done[1]<-1
	}

}
func funcC(){
	count := 10
	for{
		<-done[1]
		fmt.Printf("C");
		count--
		done[2]<-2
	}

}
func funcD(){
	count := 10
	for {
		<-done[2]
		fmt.Printf("D");
		count--
		done[3]<-3
	}

}
func funcE(){
	count := 10
	for {
		<-done[3]
		fmt.Printf("E");
		if count % 2 == 0{
			done[4]<-4
		}else{
			done[0]<-1
		}
		count--
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
	fmt.Printf("\n")
}