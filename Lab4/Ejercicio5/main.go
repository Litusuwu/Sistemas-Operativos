package main

import(
	"fmt"
	"sync"
)
var(
	wg sync.WaitGroup
	done = make([]chan bool, 5)
	counter int = 0
)

func task(n int){
	for x:=0;x<50;x++{
		fmt.Printf("%d", n)
		
	}
	wg.Done()
}

func main(){
	for i:=0;i<5;i++{
		done[i] = make(chan bool, 6)
	}
	for x:=0;x<5;x++{
		wg.Add(1)
		go task(x)
	}
	wg.Wait()
}