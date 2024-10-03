package main

import(
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var(
	wg sync.WaitGroup
	t int
	mu sync.Mutex
	espacios = make(chan bool, 1)
	items = make(chan bool, 6)
)

func cook(){
	for{
		<-espacios
		mu.Lock()
		putServingsInPot(5)
		for i:=0;i<5;i++{
			items<-true
		}
		mu.Unlock()
	}
	wg.Done()
}

func putServingsInPot(n int){
	fmt.Printf("Put Servings %d In Pot\n", n)
	t = rand.Intn(10)
	time.Sleep(time.Duration(t)*time.Millisecond)
}
func getServingFromPot(n int){
	fmt.Printf("%d: Get serving from Pot\n", n)
}
func eat(n int){
	fmt.Printf("%d : eating . . . \n", n)
}
func savage(n int, counter *int){
	for{
		<-items
		mu.Lock()
		*counter++
		
		getServingFromPot(n)
		eat(n)
		
		if(*counter % 5 == 0){
			espacios<-true
		}
		mu.Unlock()
		t = rand.Intn(10)
		time.Sleep(time.Duration(t) * time.Millisecond)
	}
	wg.Done()
}
func main(){
	counter :=0
	var input string
	items = make(chan bool, 6)
	espacios = make(chan bool, 1)
	espacios<-true
	rand.Seed(time.Now().UnixNano())
	wg.Add(11)
	go cook()
	for x:=0; x < 10; x++{
		go savage(x, &counter)
	}
	wg.Wait()
	fmt.Scan(&input)
}