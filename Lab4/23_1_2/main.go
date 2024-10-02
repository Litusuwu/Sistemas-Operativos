package main 

import "fmt"
var(
	done1 = make(chan bool)
)
func main(){
	ch := make(chan int, 100)
	done := make(chan bool)
	done1 = make(chan bool, 1)
	// done2 := make(chan bool)
	go producer1(ch, done)
	go producer2(ch, done)
	go consumer1(ch)
	go producer3(ch, done)
	// go consumer2(ch)
	<-done
}
func producer1(ch chan int, done chan bool){
	for index:=0;index<3;index++{
		fmt.Printf("PRODUCTOR 1: envia %v\n",index)
		ch<-index
	}
	// close(ch)
	done<-true
}
func producer2(ch chan int, done chan bool){
	<-done
	for index:=3;index<6;index++{
		fmt.Printf("PRODUCTOR 2: envia %v\n",index)
		ch<-index
	}
	// close(ch)
	done<-true
	done1<-true
}
func producer3(ch chan int, done chan bool){
	for index:=7;index<10;index++{
		fmt.Printf("PRODUCTOR 3: envia %v\n",index)
		ch<-index
	}
	close(ch)
	done<-true
}
func consumer1(ch chan int){
	<-done1
	for val:= range ch{
		fmt.Printf("CONSUMIDOR 1: lee %v\n",val)
	}
}
// func consumer2(ch chan int){
// 	for val:= range ch{
// 		fmt.Printf("CONSUMIDOR 2: lee %v\n", val)
// 	}
// }