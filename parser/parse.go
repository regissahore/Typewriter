package parser

import (
	"log"
	"os"
)

func Parse(inputPath, outputPath string) {
	outputFile, err := os.Create(outputPath)
	defer outputFile.Close()
	if err != nil {
		log.Fatal(err)
		return
	}
	input := make(chan string)
	errors := make(chan error)
	go ReadDocumentFromFile(inputPath, input, errors)
	for {
		select {
		case line, ok := <-input:
			if !ok {
				return
			}
			outputFile.WriteString(line + "\n")
		case err := <-errors:
			log.Fatal(err)
			return
		}
	}
}
