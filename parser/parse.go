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

var spanParsers []func(line *UTF8String) (bool, int, int, IElement)

func GetSpanParsers() []func(line *UTF8String) (bool, int, int, IElement) {
	if spanParsers == nil {
		spanParsers = make([]func(line *UTF8String) (bool, int, int, IElement), 0)
		//spanParsers = append(spanParsers, ParseInlineHardLineBreak)
		//spanParsers = append(spanParsers, ParseInlineBackslashEscape)
		//spanParsers = append(spanParsers, ParseInlineEntity)
		//spanParsers = append(spanParsers, ParseInlineTextualContent)
	}
	return spanParsers
}

func Parse(input <-chan string, output chan<- string, errors <-chan error) {
	defer close(output)
	GetSpanParsers()
	// First phase: read the entire document.
	source := NewUTF8StringEmpty()
	var readFinished bool = false
	for !readFinished {
		select {
		case line, ok := <-input:
			if !ok {
				readFinished = true
				break
			}
			source = source.Append(NewUTF8String(line + "\n"))
		case <-errors:
			return
		}
	}
	// Second phase: parse block elements and form the tree structure.
	doc := parseBlock(source)
	// Third phase: parse inline elements.
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
	// Fourth phase: translate to HTML and output.
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
					parsers := GetSpanParsers()
					parsed := false
					for _, parser := range parsers {
						success, offset, length, elem := parser(inline)
						if success {
							parsed = true
							node.GetBase().Children[index] = NewDocument()
							if offset > 0 {
								textElem := NewElementInlineTextualContent(inline.Left(offset))
								node.GetBase().Children[index].GetBase().AddChild(textElem)
							}
							node.GetBase().Children[index].GetBase().AddChild(elem)
							if length < inline.Length() {
								textElem := NewElementInlineTextualContent(inline.Right(length))
								node.GetBase().Children[index].GetBase().AddChild(textElem)
							}
							parseInline(node.GetBase().Children[index], progress)
							break
						}
					}
					if !parsed {
						textElem := NewElementInlineTextualContent(inline)
						node.GetBase().Children[index] = textElem
					}
					progress <- -1
				}()
			}
		}
	}
}
