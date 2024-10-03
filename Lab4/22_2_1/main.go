package main

import "fmt"

func main() {
    naturals := make(chan int)
    squares := make(chan int)

    // Counter
    go func() {
        /* Nro de Línea   Counter        Main-Gorutina   Squarer
           11             Run            Ready           Ready
        */
        for x := 0; x < 3; x++ {
            naturals <- x
            /* Nro de Línea   Counter        Main-Gorutina   Squarer
               13             Run            Ready           Ready
            */
        }
        close(naturals)
        /* Nro de Línea   Counter        Main-Gorutina   Squarer
           15             Run            Ready           Ready
        */
    }()

    // Squarer
    go func() {
        /* Nro de Línea   Counter        Main-Gorutina   Squarer
           18             Ready          Ready           Run
        */
        for x := range naturals {
            squares <- x * x
            /* Nro de Línea   Counter        Main-Gorutina   Squarer
               20             Ready          Ready           Run
            */
        }
        close(squares)
        /* Nro de Línea   Counter        Main-Gorutina   Squarer
           22             Ready          Ready           Run
        */
    }()

    // Printer (in main goroutine)
    for x := range squares {
        /* Nro de Línea   Counter        Main-Gorutina   Squarer
           24             Ready          Run             Ready
        */
        fmt.Println(x)
        /* Nro de Línea   Counter        Main-Gorutina   Squarer
           25             Ready          Run             Ready
        */
    }
    /* Nro de Línea   Counter        Main-Gorutina   Squarer
       28             Ready          Run             Ready
    */
}
