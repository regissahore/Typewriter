package parser

import (
	"bufio"
	"os"
)

func ReadDocumentFromFile(filePath string, input chan<- string, errors chan<- error) {
	defer close(input)
	file, err := os.Open(filePath)
	defer file.Close()
	if err != nil {
		errors <- err
		return
	}
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		input <- scanner.Text()
	}
}

func WriteDocumentToFile(filePath string, output <-chan string, errors chan<- error, finished chan<- bool) {
	file, err := os.Create(filePath)
	defer file.Close()
	if err != nil {
		errors <- err
		return
	}
	for {
		line, ok := <-output
		if !ok {
			finished <- true
			return
		}
		file.WriteString(line)
	}
}
