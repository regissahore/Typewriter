package main

import (
	"fmt"
	"os"
)

const (
	TEST    = iota
	RELEASE = iota
)

func main() {
	var mode = TEST
	switch mode {
	case TEST:
		Test()
	case RELEASE:
		if len(os.Args) < 2 {
			fmt.Println("Not enough input arguments.")
		} else {
			Parse(os.Args[0], os.Args[1])
		}
	}
}
