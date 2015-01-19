package parser

import (
	"fmt"
)

func print(a ...interface{}) {
	fmt.Print(a)
}

func printf(format string, a ...interface{}) {
	fmt.Printf(format, a)
}

func println(a ...interface{}) {
	fmt.Println(a)
}
