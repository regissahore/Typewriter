package main

import (
	"bufio"
	"log"
	"os"
)

func Parse(inputPath, outputPath string) {
	inputFile, err := os.Open(inputPath)
	defer inputFile.Close()
	if err != nil {
		log.Fatal(err)
	}
	outputFile, err := os.Create(outputPath)
	defer outputFile.Close()
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(inputFile)
	for scanner.Scan() {
		outputFile.WriteString(scanner.Text() + "\n")
	}
}
