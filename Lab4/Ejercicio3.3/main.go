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
	index int = 0
)
func funcA(){
	for {
		<-done[0]
		fmt.Printf("A")
		index++
		if index==1 {
			done[1]<-1
		}else if index==2{
			done[0]<-1
			continue
		}else if index==3{
			done[2]<-1
			index = 0
		}
		
	}
}
func funcB(){
	for {
		<-done[0]
		fmt.Printf("B")
		index++
		if index==1 {
			done[1]<-1
		}else if index==2{
			done[0]<-1
			continue
		}else if index==3{
			done[2]<-1
			index = 0
		}
	}

}
func funcC(){
	for{
		<-done[1]
		fmt.Printf("C");
		done[3]<-1
	}

}
func funcD(){
	for {
		<-done[2]
		fmt.Printf("D");
		done[3]<-1
	}

}
func funcE(){
	for {
		<-done[3]
		fmt.Printf("E");
		time.Sleep(time.Second)
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
// package main

// import (
// 	"fmt"
// 	"sync"
// )

// func main() {
// 	var wg sync.WaitGroup

// 	wg.Add(1)

// 	aORB := make(chan int)
// 	c := make(chan int)
// 	d := make(chan int)
// 	e := make(chan int)
// 	aORB2 := make(chan int)
// 	ok := make(chan int)
// 	turno := 0
// 	//go routines

// 	go func() {
// 		for {
// 			select {
// 			case <-aORB:
// 				fmt.Printf("A")
// 				c <- 1
// 			case <-aORB2:
// 				fmt.Printf("A")
// 				//fmt.Printf("yee")
// 				ok <- 1
// 			}

// 		}
// 	}()

// 	go func() {
// 		for {
// 			select {
// 			case <-aORB:
// 				fmt.Printf("B")
// 				c <- 1
// 			case <-aORB2:
// 				fmt.Printf("B")
// 				//fmt.Printf("yee")
// 				ok <- 1
// 			}
// 		}
// 	}()

// 	go func() {
// 		for {
// 			<-c
// 			fmt.Printf("C")
// 			e <- 1
// 		}
// 	}()
// 	go func() {
// 		for {
// 			<-d
// 			fmt.Printf("D")
// 			e <- 1
// 		}
// 	}()
// 	go func() {
// 		for {
// 			<-e
// 			fmt.Printf("E")
// 			if turno == 0 {
// 				aORB2 <- 1
// 				<-ok
// 				aORB2 <- 1
// 				<-ok
// 				d <- 1
// 				turno = 1
// 			} else {
// 				aORB <- 1
// 				turno = 0
// 			}
// 			//fmt.Printf("%d", turno)
// 		}
// 	}()
// 	aORB <- 1
// 	wg.Wait()
// }
