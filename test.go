package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"runtime"
	"sync"
)

func Test() {
	testCaseFile, err := os.Open("./test/cases")
	defer testCaseFile.Close()
	if err != nil {
		log.Fatal(err)
	}
	scanner := bufio.NewScanner(testCaseFile)
	tasks := make(chan string)
	var waitGroup sync.WaitGroup
	workerNum := runtime.NumCPU()
	for i := 0; i < workerNum; i++ {
		waitGroup.Add(1)
		go func() {
			for task := range tasks {
				if !testCase(task) {
					fmt.Println("Error at: " + task)
				}
			}
			waitGroup.Done()
		}()
	}
	for scanner.Scan() {
		tasks <- scanner.Text()
	}
}

func testCase(testName string) bool {
	stdInputName := "test/" + testName + ".in"
	stdOutputName := "test/" + testName + ".out"
	testOutputName := "test/" + testName + ".test"
	Parse(stdInputName, testOutputName)
	stdOutput, _ := readWithoutEOL(stdOutputName)
	testOutput, err := readWithoutEOL(testOutputName)
	if err != nil {
		return false
	}
	return stdOutput == testOutput
}

func readWithoutEOL(filePath string) (string, error) {
	file, err := os.Open(filePath)
	defer file.Close()
	if err != nil {
		return "", err
	}
	scanner := bufio.NewScanner(file)
	text := ""
	for scanner.Scan() {
		text += scanner.Text()
	}
	return text, nil
}
