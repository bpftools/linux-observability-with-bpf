package main

import "time"

func main() {
	j := 3
	for time.Since(time.Now()) < time.Second {
		for i := 1; i < 1000000; i++ {
			j *= i
		}
	}
}
