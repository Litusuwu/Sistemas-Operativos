package main

import (
	"fmt"
	"sync"
	"time"
)
var(
	nranas int = 8
	slice = make([]int, nranas+1)
	channels = make([]chan bool, nranas)
	done = make(chan bool)
	mu sync.Mutex
)
func imprimir(){
	fmt.Println(slice)
}
func consola(){
	vueltas := 1
	exIzq := (nranas/2) - 1
	exDer := exIzq + 1
	flag := true
	var id, count, lim int
	
	for{
		if(flag==true){
			id = exIzq
			count = -1
			lim = 0
			flag = false
		}else{
			id = exDer
			count = 1
			lim = nranas
			flag = true
		}
		// fmt.Printf("%d %d-------\n", id, exDer)
		for i:=0;i<vueltas;i++{
			channels[id]<-true
			<-done
			//time.Sleep(time.Second*2)
			if(id==lim){
				continue
			}else{
				id = id + count
			}
		}
		if(vueltas != nranas/2){
			vueltas++
		}
		time.Sleep(time.Second*2)
	}
}
func rutina(n int){
	for{
		<-channels[n]
		// fmt.Printf("%d - %d\n", n+1, (nranas+1)/2)
		mu.Lock()
		if((n+1) <= ((nranas+1)/2)){
			var index,indexV int
			for i:=0;i<nranas+1;i++{
				if(n+1 == slice[i]){
					index = i
				}
				if(slice[i] == -1){
					indexV = i
				}
			}
			if(!(indexV < index) && (indexV - index <= 2)){
				slice[index] = -1
				slice[indexV] = n+1
			} 
			fmt.Printf("Der: %d ", n+1)
			imprimir() 
		}else{
			var index,indexV int
			for i:=0;i<nranas+1;i++{
				if(n+1 == slice[i]){
					index = i
				}
				if(slice[i] == -1){
					indexV = i
				}
			}
			if(!(indexV > index) && (index - indexV <= 2)){
				slice[index] = -1
				slice[indexV] = n+1
			}
			fmt.Printf("Izq: %d ", n)
			imprimir() 
		}
		mu.Unlock()
		done<-true	
	}
}
func main(){
	var input string
	done = make(chan bool, 0)
	for i:=0;i<nranas;i++{
		channels[i] = make(chan bool, 2)
	}
	med := nranas/2
	for i:=0;i<med;i++{
		slice[i]=i+1
	}
	slice[med]=-1
	for i:=med+1;i<=nranas;i++{
		slice[i]=i
	}
	for i:=0;i<nranas;i++{
		go rutina(i)
	}

	imprimir()
	go consola()
	fmt.Scan(&input)
}