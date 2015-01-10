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
	input := make(chan string)
	output := make(chan string)
	errors := make(chan error)
	finished := make(chan bool)
	go Parse(input, output, errors)
	go ReadDocumentFromFile(inputPath, input, errors)
	go WriteDocumentToFile(outputPath, output, errors, finished)
	<-finished
}

func Parse(input <-chan string, output chan<- string, errors <-chan error) {
	defer close(output)
	// Initialize document and parsers.
	doc := NewDocument()
	blockParsers := make([]func(doc *Document, line *UTF8String, offset int) (bool, int), 0)
	blockParsers = append(blockParsers, ParseLeafHorizontalRule)
	// First phase: build the tree structure of block elements.
	var readFinished bool = false
	for !readFinished {
		select {
		case text, ok := <-input:
			if !ok {
				readFinished = true
				break
			}
			line := NewUTF8String(text)
			var offset int
			for {
				var parsed bool = false
				for _, parser := range blockParsers {
					success, length := parser(doc, line, offset)
					if success {
						parsed = true
						offset += length
						break
					}
				}
				if !parsed || offset == line.Length() {
					break
				}
			}
		case <-errors:
			return
		}
	}
	// Second phase: detect inline elements.
	// Third phase: transform elements to strings.
	parseToString(doc, output)
}

func parseToString(node IElement, output chan<- string) {
	output <- node.OpenString()
	for _, child := range node.GetElement().children {
		parseToString(child, output)
	}
	output <- node.CloseString()
}
