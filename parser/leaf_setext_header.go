package parser

import (
	"fmt"
)

type ElementLeafSetextHeader struct {
	Base  *Element
	Level int
}

func NewElementLeafSetextHeader(text *UTF8String, level int) *ElementLeafSetextHeader {
	elem := &ElementLeafSetextHeader{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_SETEXT_HEADER,
		Open:     false,
		Children: nil,
		Inlines:  []*UTF8String{text},
	}
	elem.Level = level
	return elem
}

func (elem *ElementLeafSetextHeader) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafSetextHeader) Translate(output chan<- string) {
	output <- fmt.Sprintf("<h%d>", elem.Level)
	elem.Base.TranslateAllChildren(output)
	output <- fmt.Sprintf("</h%d>\n\n", elem.Level)
}

func (elem *ElementLeafSetextHeader) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafSetextHeader) TryClose(last IElement) bool {
	return true
}

// Setext header containing at least one '=' or '-' and cannot be mixed.
// There is no space between '=' or '-'.
// Cannot interrupt paragraph.
// Leading spaces and tailing spaces will be removed in the header.
// Has lower priority than list.
// Has higher priority than horizontal rule.
func parseLeafSetextHeader(doc *Document, line *UTF8String, offset int) bool {
	length := line.Length()
	// Check whether the length open block is a single line paragraph.
	if doc.GetLastLeafFunction() != ELEMENT_TYPE_LEAF_PARAGRAPH {
		return false
	}
	if doc.LastLeaf.(*ElementLeafParagraph).LineNum != 1 {
		return false
	}
	// Skip leading blanks.
	index := SkipLeadingSpace(line, offset)
	symbol := line.RuneAt(index)
	if symbol != '=' && symbol != '-' {
		return false
	}
	// Skip symbols.
	for i := index + 1; i < length; i++ {
		r := line.RuneAt(i)
		if r == symbol {
			continue
		} else if IsWhitespace(r) {
			index = i + 1
			break
		} else {
			return false
		}
	}
	// Skip tailing blanks.
	for i := index; i < length; i++ {
		r := line.RuneAt(i)
		if !IsWhitespace(r) {
			return false
		}
	}
	level := 1
	if symbol == '-' {
		level = 2
	}
	doc.RemoveLastLeaf()
	text := doc.LastLeaf.GetBase().Inlines[0].Trim()
	doc.AddElement(NewElementLeafSetextHeader(text, level))
	return true
}
