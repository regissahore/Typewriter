package parser

import (
	"fmt"
)

type ElementLeafSetextHeader struct {
	element *Element
	level   int
}

func NewElementLeafSetextHeader(text *UTF8String, level int) *ElementLeafSetextHeader {
	elem := &ElementLeafSetextHeader{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_SETEXT_HEADER,
		isOpen:        false,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          text,
	}
	elem.level = level
	return elem
}

func (elem *ElementLeafSetextHeader) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafSetextHeader) OpenString() string {
	return fmt.Sprintf("<h%d>", elem.level)
}

func (elem *ElementLeafSetextHeader) CloseString() string {
	return fmt.Sprintf("</h%d>\n\n", elem.level)
}

func (elem *ElementLeafSetextHeader) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafSetextHeader) TryClose(last IElement) bool {
	return true
}

func ParseLeafSetextHeader(doc *Document, line *UTF8String, offset int) (bool, int) {
	// Check whether the last open block is a single line paragraph.
	lastOpen := doc.GetLastOpen()
	if lastOpen.GetElement().functionType != ELEMENT_TYPE_LEAF_PARAGRAPH {
		return false, 0
	}
	if lastOpen.(*ElementLeafParagraph).lineNum != 1 {
		return false, 0
	}
	// Skip leading blanks.
	length := line.Length()
	index := SkipLeadingSpace(line, offset)
	if index == length || index-offset >= 4 {
		return false, 0
	}
	symbol := line.RuneAt(index)
	if symbol != '=' && symbol != '-' {
		return false, 0
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
			return false, 0
		}
	}
	// Skip tailing blanks.
	for i := index; i < length; i++ {
		r := line.RuneAt(i)
		if !IsWhitespace(r) {
			return false, 0
		}
	}
	level := 1
	if symbol == '-' {
		level = 2
	}
	text := lastOpen.GetElement().text.Trim()
	lastOpen.(*ElementLeafParagraph).Abondon()
	doc.RemoveLastOpen()
	doc.AddElement(NewElementLeafATXHeader(text, level))
	return true, length - offset
}
