package main 

import(
	"fmt"
	"os"
	"sync"
)

var (
	wg sync.WaitGroup
	arreglo = make([]chan bool, 5)
	valores []int
	ok = make(chan bool)
)
func admin(){
	for{
		for i:=0;i<len(valores);i++{
			arreglo[valores[i]]<-true
			<-ok
		}
	}
}

func worker1(){
	for{
		<-arreglo[0]
		fmt.Printf("A")
		ok<-true
	}
	wg.Done()
}
func worker2(){
	for{
		<-arreglo[1]
		fmt.Printf("B")
		ok<-true
	}
	wg.Done()
}
func worker3(){
	for{
		<-arreglo[2]
		fmt.Printf("C")
		ok<-true
	}
	wg.Done()
}
func worker4(){
	for{
		<-arreglo[3]
		fmt.Printf("D")
		ok<-true
	}
	wg.Done()
}
func worker5(){
	for{
		<-arreglo[4]
		fmt.Printf("E")
		ok<-true
	}
	wg.Done()
}

func main(){
	var cadena string
	valores = []int{}
	ok = make(chan bool, 0)
	for i:=0;i<5;i++{
		arreglo[i] = make(chan bool, 1)
	}
	for i:=0;i<len(os.Args);i++{
		cadena = os.Args[i]
		switch cadena{
		case "A":
			valores = append(valores, 0)
			fmt.Println(cadena)
		case "B":
			valores = append(valores, 1)
			fmt.Println(cadena)
		case "C":
			valores = append(valores, 2)
			fmt.Println(cadena)
		case "D":
			valores = append(valores, 3)
			fmt.Println(cadena)
		case "E":
			valores = append(valores, 4)
			fmt.Println(cadena)
		}
	}
	wg.Add(5)

	go admin()

	go worker1()
	go worker2()
	go worker3()
	go worker4()
	go worker5()
	
	wg.Wait()
}