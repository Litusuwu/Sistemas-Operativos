package main

import(
	"fmt"
	"sync"
)

var(
	buffer[5]int = [5]int {-1,-1,-1,-1,-1}
	pos int
	wg sync.WaitGroup
	mu sync.Mutex // Mutex para proteger la sección crítica

	// Canales para controlar la sincronización
	producerSignal  = make(chan struct{}, 5) // Canal que controla cuándo el productor puede producir   (con un buffer de tamaño 5)
	consumerSignal  = make(chan struct{})    // Se desbloquea cuando el productor produce un nuevo ítem.  (sin buffer)
)

func productor(){
	defer wg.Done() // Se ejecuta cuando esta función termina
	for n:= 0; n<20; n++{
		item := n * n
		producerSignal <- struct{}{} // Espera hasta que haya espacio para producir (si buffer está lleno, se bloquea)
		mu.Lock() // Proteger acceso al buffer
		pos = n % 5
		buffer[pos] = item
		fmt.Printf("productor %d %d %v\n",pos,item,buffer)
		mu.Unlock()
		// Notificar que se ha producido un ítem y el consumidor puede consumir
		consumerSignal <- struct{}{}
	}
	//wg.Done()
}

func consumidor(){
	defer wg.Done() // Se ejecuta cuando esta función termina
	var item int
	for n:= 0; n<20; n++ {
		<-consumerSignal // Esperar hasta que haya un ítem para consumir
		mu.Lock() // Proteger acceso al buffer
		pos = n % 5 //calcula desde donde se extraerá un item
		item = buffer[pos] //extrae un item
		buffer[pos] = -1 //marca en el buffer como vacio
		fmt.Printf("consumidor %d %d %v\n", pos, item, buffer)
		mu.Unlock()
		// Notificar que hay espacio para producir más
		<-producerSignal
	}
	wg.Done()
}

func main(){
	wg.Add(2)
	go consumidor()
	go productor()
	wg.Wait() // Esperar a que ambas goroutines terminen
}