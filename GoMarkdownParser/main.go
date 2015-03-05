package main

import (
	"./parser"
	"fmt"
	"os"
	"runtime"
)

const (
	TEST    = iota
	RELEASE = iota
)

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	var mode = TEST
	switch mode {
	case RELEASE:
		if len(os.Args) < 2 {
			fmt.Println("Not enough input arguments.")
		} else {
			parser.ParseFile(os.Args[0], os.Args[1])
		}
	case TEST:
		Test()
	}
}
