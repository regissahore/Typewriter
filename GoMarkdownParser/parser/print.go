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

func printDocumentTree(elem IElement, spaces int) {
	for i := 0; i < spaces; i++ {
		fmt.Print(" ")
	}
	if elem == nil {
		fmt.Println(elem)
		return
	}
	fmt.Println(elem.GetBase().Function)
	if elem.GetBase().Children != nil {
		for _, child := range elem.GetBase().Children {
			printDocumentTree(child, spaces+4)
		}
	}
}
