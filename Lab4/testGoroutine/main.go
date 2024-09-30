package main

import "fmt"

func main(){
	done := make(chan struct{})
	for x := 0 ; x < 5 ; x++{
		go func(count int){
			fmt.Printf("I'm a goroutine %d\n", count)
			done <- struct{}{}
		}(x)
	}
	for x:=0 ; x < 5 ; x++{
		<-done
	}
	
}