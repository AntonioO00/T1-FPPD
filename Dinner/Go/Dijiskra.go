package main

import (
	"fmt"
	"strconv"
)

const (
	PHILOSOPHERS = 5
	FORKS        = 5
)

func philosopher(id int, first_fork chan struct{}, second_fork chan struct{}) {
	for {
		fmt.Println(strconv.Itoa(id) + " senta")

		// O último filósofo pega os garfos na ordem inversa
		if id == PHILOSOPHERS-1 {
			<-second_fork // pega o segundo garfo
			fmt.Println(strconv.Itoa(id) + " pegou o segundo garfo")
			<-first_fork // pega o primeiro garfo
			fmt.Println(strconv.Itoa(id) + " pegou o primeiro garfo")
		} else {
			<-first_fork // pega o primeiro garfo
			fmt.Println(strconv.Itoa(id) + " pegou o primeiro garfo")
			<-second_fork // pega o segundo garfo
			fmt.Println(strconv.Itoa(id) + " pegou o segundo garfo")
		}

		// Simula que o filósofo terminou de comer
		first_fork <- struct{}{} // libera o primeiro garfo
		second_fork <- struct{}{} // libera o segundo garfo
		fmt.Println(strconv.Itoa(id) + " liberou os garfos")
	}
}

func main() {
	var forks_chanels = [FORKS]chan struct{}
	for i := 0; i < FORKS; i++ {
		forks_chanels[i] = make(chan struct{}, 1)
		forks_chanels[i] <- struct{}{} // no inicio o garfo está livre
	}
	for i := 0; i < PHILOSOPHERS; i++ {
		go philosopher(i, forks_chanels[i], forks_chanels[(i+1)%PHILOSOPHERS])
	}

	var blq chan struct{} = make(chan struct{})
	<-blq
}
