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
			parseBlock(doc, NewUTF8String(line+"\n"))
		case <-errors:
			return
		}
	}
	// Second phase: parse inline elements.
	progress := make(chan int)
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

func parseInline(node IElement, progress chan int) {
	if node.GetBase().Children != nil && len(node.GetBase().Children) > 0 {
		for _, child := range node.GetBase().Children {
			parseInline(child, progress)
		}
	} else {
		if node.GetBase().Inlines != nil {
			node.GetBase().Children = make([]IElement, len(node.GetBase().Inlines))
			for index, inline := range node.GetBase().Inlines {
				progress <- 1
				go func() {
					textElem := NewElementInlineTextualContent(inline)
					node.GetBase().Children[index] = textElem
					progress <- -1
				}()
			}
		}
	}
}
