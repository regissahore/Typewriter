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
	blockParsers = append(blockParsers, ParseLeafFencedCodeBlock)
	blockParsers = append(blockParsers, ParseLeafBlankLine)
	blockParsers = append(blockParsers, ParseLeafHTMLBlock)
	blockParsers = append(blockParsers, ParseLeafIndentedCodeBlock)
	blockParsers = append(blockParsers, ParseLeafATXHeader)
	blockParsers = append(blockParsers, ParseLeafSetextHeader)
	blockParsers = append(blockParsers, ParseLeafHorizontalRule)
	blockParsers = append(blockParsers, ParseLeafParagraph)
	inlineParsers := make([]func(doc *Document, line *UTF8String, offset int) (bool, int), 0)
	inlineParsers = append(inlineParsers, ParseInlineHardLineBreak)
	inlineParsers = append(inlineParsers, ParseInlineTextualContent)
	// First phase: build the tree structure of block elements.
	var readFinished bool = false
	for !readFinished {
		select {
		case text, ok := <-input:
			if !ok {
				readFinished = true
				break
			}
			line := NewUTF8String(text + "\n")
			var offset int
			for {
				for _, parser := range blockParsers {
					success, length := parser(doc, line, offset)
					if success {
						offset += length
						break
					}
				}
				if offset == line.Length() {
					break
				}
			}
		case <-errors:
			return
		}
	}
	// Second phase: detect inline elements.
	progress := make(chan bool)
	totalNum := parseInline(doc, progress, inlineParsers)
	for totalNum > 0 {
		<-progress
		totalNum--
	}
	// Third phase: transform elements to strings.
	parseToString(doc, output)
}

func parseInline(node IElement,
	progress chan bool,
	inlineParsers []func(doc *Document, line *UTF8String, offset int) (bool, int)) int {
	num := 0
	if node.GetElement().structureType == ELEMENT_TYPE_LEAF {
		go func() {
			subDoc := NewDocument()
			offset := 0
			length := node.GetElement().text.Length()
			for offset < length {
				for _, parser := range inlineParsers {
					success, length := parser(subDoc, node.GetElement().text, offset)
					if success {
						offset += length
						break
					}
				}
			}
			node.GetElement().children = append(node.GetElement().children, subDoc)
			progress <- true
		}()
		num++
	}
	for _, child := range node.GetElement().children {
		num += parseInline(child, progress, inlineParsers)
	}
	return num
}

func parseToString(node IElement, output chan<- string) {
	output <- node.OpenString()
	for _, child := range node.GetElement().children {
		parseToString(child, output)
	}
	output <- node.CloseString()
}
