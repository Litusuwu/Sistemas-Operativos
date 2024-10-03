package main

import(
	"fmt"
	"sync"
)

func gorutina(n int, arr*[5000]int, mu *sync.Mutex, wg *sync.WaitGroup, cant int){
	defer wg.Done()
	for i:=0;i<cant;i++{
		for j:=0;j<5000;j++{
			mu.Lock()
			if(arr[j]==-1){
				arr[j] = n
				break
			}
			mu.Unlock()
		}
		mu.Unlock()
	}
}
func main(){
	var(
		mu sync.Mutex
		wd sync.WaitGroup
	)
	arr := [5000]int{}
	arrCount := [20]int{}
	for i:=range arr{
		arr[i] = -1
	}
	for i:=range arrCount{
		arrCount[i]=0
	}
	cant := 5000/20
	wd.Add(20)
	for i:=0;i<20;i++{
		go gorutina(i, &arr, &mu, &wd, cant)
	}
	wd.Wait()
	for i:=range arr{
		fmt.Printf("%d ", arr[i])
		arrCount[arr[i]]++
	}
	fmt.Println()
	for i:=range arrCount{
		fmt.Printf("Cantidad de '%d' : %d\n",i, arrCount[i])
	}
	fmt.Println()
}