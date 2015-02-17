package parser

import (
	"log"
	"os"
)

func ParseFile(inputPath, outputPath string) {
	outputFile, err := os.Create(outputPath)
	defer outputFile.Close()
	if err != nil {
		log.Panic(err)
		return
	}
	input := make(chan string, 10)
	output := make(chan string, 10)
	errors := make(chan error)
	finished := make(chan bool)
	go Parse(input, output, errors)
	go ReadDocumentFromFile(inputPath, input, errors)
	go WriteDocumentToFile(outputPath, output, errors, finished)
	<-finished
}

func Parse(input <-chan string, output chan<- string, errors <-chan error) {
	defer close(output)
	// First phase: parse block elements and form the tree structure.
	doc := NewDocument()
	var readFinished bool = false
	for !readFinished {
		select {
		case line, ok := <-input:
			if !ok {
				readFinished = true
				break
			}
			parseBlock(doc, NewUTF8StringExpanded(line+"\n"))
		case <-errors:
			return
		}
	}
	// Second phase: parse inline elements.
	progress := make(chan int, 100)
	sum := 0
	go func() {
		progress <- 1
		parseInline(doc, progress)
		progress <- -1
	}()
	for {
		sum += <-progress
		if sum == 0 {
			break
		}
	}
	// Third phase: translate to HTML and output.
	doc.Translate(output)
}
