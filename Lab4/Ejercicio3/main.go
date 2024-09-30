package main

import (
	"fmt"
	"sync"
)
var(
	wg sync.WaitGroup
	mu sync.Mutex
	done = make([]chan int, 5)
)
func funcA(){
	count := 5
	for count>0 {
		<-done[0]
		fmt.Printf("A")
		count--
		done[1]<-1
	}
	wg.Done()
}
func funcB(){
	count := 5
	for count>0 {
		<-done[1]
		fmt.Printf("B")
		count--
		done[2]<-2
	}
	wg.Done()	
}
func funcC(){
	count := 5
	for count>0 {
		<-done[2]
		fmt.Printf("C");
		count--
		done[3]<-3
	}
	wg.Done()
}
func funcD(){
	count := 5
	for count>0 {
		<-done[3]
		fmt.Printf("D");
		count--
		done[4]<-4
	}
	wg.Done()
}
func funcE(){
	count := 5
	for count>0 {
		<-done[4]
		fmt.Printf("E");
		count--
		done[0]<-1
	}
	wg.Done()
}
func main(){
	// var str string
	wg.Add(5)
	for i:=0;i<5;i++{
		done[i] = make(chan int, 1)
	}
	done[0]<-1
	go funcA();
	go funcB();
	go funcC();
	go funcD();
	go funcE();
	wg.Wait()
	fmt.Printf("\n")
}