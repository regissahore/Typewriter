package parser

import (
	"fmt"
)

func Print(a ...interface{}) {
	fmt.Print(a)
}

func Printf(format string, a ...interface{}) {
	fmt.Printf(format, a)
}

func Println(a ...interface{}) {
	fmt.Println(a)
}
