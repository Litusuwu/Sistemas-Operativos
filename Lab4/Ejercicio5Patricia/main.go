// main.go
package main

import (
	"fmt"
	"sync"
)

var (
	cgen = make(chan int)
	ok   = make(chan int)
	wait = make([]chan int, 5)
)

func admin() {
	for x := 0; x < 50; x++ {
		cgen <- 1
		<-ok
		cgen <- 1
		<-ok
		cgen <- 1
		<-ok
		cgen <- 1
		<-ok
		cgen <- 1
		<-ok
		fmt.Printf("\n")
		for i := 0; i < 5; i++ { //desactivas todos los que estan en espera
			wait[i] <- 1
		}
	}
}

func task(n int) {
	for x := 0; x < 50; x++ {
		<-cgen
		fmt.Printf("%d", n)
		ok <- 1
		<-wait[n]
	}
	wg.Done()
}

var wg sync.WaitGroup

func main() {
	for x := 0; x < 5; x++ {
		wait[x] = make(chan int)
	}
	for x := 0; x < 5; x++ {
		wg.Add(1)
		go task(x)
	}
	go admin()
	wg.Wait()
	for x := 0; x < 5; x++ {
		close(wait[x])
	}
}
