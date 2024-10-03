package main

import (
	"fmt"
	"sync"
	"time"
)


func worker1(wg *sync.WaitGroup, canales []chan bool, counter *bool){
	for{
		<-canales[0]
		fmt.Printf("A")
		if(*counter == true){
			canales[1]<-true
		}else{
			canales[3]<-true
		}
	}
	wg.Done()
}
func worker2(wg *sync.WaitGroup, canales []chan bool, counter *bool){
	for{
		<-canales[1]
		fmt.Printf("B")
		if(*counter==true){
			canales[3]<-true
		}else{
			canales[0]<-true
		}
	}
	wg.Done()
}
func worker3(wg *sync.WaitGroup, canales []chan bool, counter *bool){
	for{
		<-canales[3]
		fmt.Printf("C")
		canales[2]<-true
	}
	wg.Done()
}
func worker4(wg *sync.WaitGroup, canales []chan bool, counter *bool){
	for{
		<-canales[2]
		fmt.Printf("D")
		canales[4]<-true
	}
	wg.Done()
}
func worker5(wg *sync.WaitGroup, canales []chan bool, counter *bool){
	for{
		<-canales[4]
		fmt.Printf("E")
		if(*counter==true){
			*counter=false
			canales[1]<-true
		}else{
			*counter=true
			canales[0]<-true
		}
		time.Sleep(time.Second)
	}
	wg.Done()
}
func main(){ 
	var	wg sync.WaitGroup
	var canales = make([]chan bool, 5)
	var	counter bool = true
	
	wg.Add(5)
	for i:=0;i<5;i++{
		canales[i] = make(chan bool, 1)
	}
	canales[0]<-true
	go worker1(&wg, canales, &counter)
	go worker2(&wg, canales, &counter)
	go worker3(&wg, canales, &counter)
	go worker4(&wg, canales, &counter)
	go worker5(&wg, canales, &counter)
	wg.Wait()
	fmt.Printf("\n")
}