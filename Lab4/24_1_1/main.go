package main

import(
	"fmt"
	"sync"
	"strconv"
)
var(
	wg sync.WaitGroup
	done = make([]chan bool, 5)
	counter int = 0
	confirm = make(chan bool)
	mensaje = make(chan bool)
	secuencia string = ""
	elementos =make(map[string]bool)
	flag bool = false
)
func consola(){
	for{
		if(len(elementos)==50){
			break
		}
		confirm<-true
		<-mensaje
		confirm<-true
		<-mensaje
		confirm<-true
		<-mensaje
		confirm<-true
		<-mensaje
		confirm<-true
		<-mensaje
		secuencia = secuencia + "\n"
		if (elementos[secuencia]!=true){
			elementos[secuencia] = true	
			fmt.Printf(secuencia)
		}
		secuencia = ""
		for j:=0;j<5;j++{
			done[j]<-true
		}
	}
	flag = true
}
func task(n int){
	for{
		if(flag == true){
			break
		}
		<-confirm
		secuencia = secuencia + strconv.Itoa(n)
		mensaje<-true
		<-done[n]
	}
	wg.Done()
}

func main(){
	for i:=0;i<5;i++{
		done[i] = make(chan bool, 0)
	}
	
	for x:=0;x<5;x++{
		wg.Add(1)
		go task(x)
	}
	go consola()
	wg.Wait()
}