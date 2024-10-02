package main

import (
	"fmt"
	"sync"
	"time"
)

var( 
	wg sync.WaitGroup
	canales = make([]chan bool, 5)
	counter bool = true
)
func worker1(){
	for{
		<-canales[0]
		fmt.Printf("A")
		if(counter == true){
			canales[1]<-true
		}else{
			canales[3]<-true
		}
	}
	wg.Done()
}
func worker2(){
	for{
		<-canales[1]
		fmt.Printf("B")
		if(counter==true){
			canales[3]<-true
		}else{
			canales[0]<-true
		}
	}
	wg.Done()
}
func worker3(){
	for{
		<-canales[3]
		fmt.Printf("C")
		canales[2]<-true
	}
	wg.Done()
}
func worker4(){
	for{
		<-canales[2]
		fmt.Printf("D")
		canales[4]<-true
	}
	wg.Done()
}
func worker5(){
	for{
		<-canales[4]
		fmt.Printf("E")
		if(counter==true){
			counter=false
			canales[1]<-true
		}else{
			counter=true
			canales[0]<-true
		}
		time.Sleep(time.Second)
	}
	wg.Done()
}
func main(){
	wg.Add(5)
	for i:=0;i<5;i++{
		canales[i] = make(chan bool, 1)
	}
	canales[0]<-true
	go worker1()
	go worker2()
	go worker3()
	go worker4()
	go worker5()
	wg.Wait()
	fmt.Printf("\n")
}