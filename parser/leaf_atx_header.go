package parser

import (
	"fmt"
)

type ElementLeafATXHeader struct {
	Base  *Element
	Level int
}

func NewElementLeafATXHeader(text *UTF8String, level int) *ElementLeafATXHeader {
	elem := &ElementLeafATXHeader{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_ATX_HEADER,
		Open:     false,
		Children: nil,
		Inlines:  []*UTF8String{text},
	}
	elem.Level = level
	return elem
}

func (elem *ElementLeafATXHeader) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafATXHeader) Translate(output chan<- string) {
	output <- fmt.Sprintf("<h%d>", elem.Level)
	elem.Base.TranslateAllChildren(output)
	output <- fmt.Sprintf("</h%d>\n", elem.Level)
}

func (elem *ElementLeafATXHeader) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafATXHeader) TryClose(last IElement) bool {
	return true
}

// ATX Header may have 0~3 leading spaces.
// Begins with 1~6 consecutive '#'s and one space.
// Ends with one space and any number of consecutive '#'s follows any number of tailing spaces.
// Leading and tailing spaces will be removed in the header.
func parseLeafATXHeader(doc *Document, line *UTF8String, offset int) (bool, int) {
	// Skip leading blanks.
	length := line.Length()
	beginIndex := SkipLeadingSpace(line, offset)
	if line.RuneAt(beginIndex) != '#' {
		return false, 0
	}
	// Count levels.
	level := 1
	for i := beginIndex + 1; i < length; i++ {
		r := line.RuneAt(i)
		if r == '#' {
			level++
			if level > 6 {
				return false, 0
			}
		} else if IsWhitespace(r) {
			beginIndex = i + 1
			break
		} else {
			return false, 0
		}
	}
	// Skip tailing blanks.
	var endIndex int = beginIndex
	if beginIndex != length {
		var tailSpaceIndex int = beginIndex
		for i := length - 1; i >= beginIndex; i-- {
			r := line.RuneAt(i)
			if IsWhitespace(r) {
				continue
			} else {
				tailSpaceIndex = i
				break
			}
		}
		// Skip tailing sharps.
		for i := tailSpaceIndex; i >= beginIndex; i-- {
			r := line.RuneAt(i)
			if r == '#' {
				continue
			} else if IsWhitespace(r) {
				endIndex = i
				break
			} else {
				endIndex = tailSpaceIndex + 1
				break
			}
		}
	}
	doc.AddElement(NewElementLeafATXHeader(line.Substring(beginIndex, endIndex-beginIndex).Trim(), level))
	return true, length - offset
}
