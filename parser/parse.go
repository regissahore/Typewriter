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
	go Parse(input, output, errors)
	go ReadDocumentFromFile(inputPath, input, errors)
	go WriteDocumentToFile(outputPath, output, errors)
}

func Parse(input <-chan string, output chan<- string, errors <-chan error) {
	defer close(output)
	for {
		select {
		case line, ok := <-input:
			if !ok {
				return
			}
			output <- line
		case <-errors:
			return
		}
	}
}
