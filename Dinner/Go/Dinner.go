package main

import (
	"fmt"
	"strconv"
)

const (
	PHILOSOPHERS = 5
	FORKS = 5
)

func philosopher(id int, first_fork chan struct{}, second_fork chan struct{}){
	for {
		fmt.Println(strconv.Itoa(id) + " senta")
		<-first_fork // pega o primeiro fork
		fmt.Println(strconv.Itoa(id) + " pegou o primeiro fork")
		<-second_fork // pega o segundo fork
		fmt.Println(strconv.Itoa(id) + " pegou o segundo fork")
		first_fork <- struct{}{} // libera o primeiro fork
		second_fork <- struct{}{} // libera o segundo fork
		fmt.Println(strconv.Itoa(id) + " liberou os forks")
	}
}


func main() {
	var forks_chanels = [FORKS]chan struct{}
	for i := 0; i < FORKS; i++ {
		forks_chanels[i] = make(chan struct{}, 1)
		forks_chanels[i] <- struct{}{}// no inicio o garfo esta livre
	}
	for i := 0; i < PHILOSOPHERS; i++ {
		fmt.Println("Filosofo" + strconv.Itoa(i))
		go philosopher(i, forks_chanels[i], forks_chanels[(i+1)%PHILOSOPHERS])
	}
	var blq chan struct{} = make(chan struct{})
	<- blq 
	
}