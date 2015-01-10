package main

import (
	"./parser"
	"bufio"
	"fmt"
	"log"
	"os"
	"time"
)

func Test() {
	testCaseFile, err := os.Open("./test/cases")
	defer testCaseFile.Close()
	if err != nil {
		log.Fatal(err)
		return
	}
	scanner := bufio.NewScanner(testCaseFile)
	totalNum, errorNum := 0, 0
	message := ""
	start := time.Now()
	for scanner.Scan() {
		testName := scanner.Text()
		totalNum++
		if !testCase(testName) {
			errorNum++
			message += fmt.Sprintf("[%d/%d] %s\n", errorNum, totalNum, testName)
		}
	}
	elapsed := time.Since(start)
	message += fmt.Sprintln("=========================")
	if errorNum == 0 {
		message += fmt.Sprintln("Passed all test cases.")
	} else {
		message += fmt.Sprintln("Total: \t", totalNum)
		message += fmt.Sprintln("Passed: \t", totalNum-errorNum)
		message += fmt.Sprintln("Error: \t", errorNum)
	}
	message += fmt.Sprintf("Total Time: %s\n", elapsed)
	fmt.Print(message)
	outputFile, err := os.Create("./test/results.test")
	defer outputFile.Close()
	if err != nil {
		log.Fatal(err)
		return
	}
	outputFile.WriteString(message)
}

func testCase(testName string) bool {
	stdInputName := "test/" + testName + ".in"
	stdOutputName := "test/" + testName + ".out"
	testOutputName := "test/" + testName + ".test"
	parser.ParseFile(stdInputName, testOutputName)
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
