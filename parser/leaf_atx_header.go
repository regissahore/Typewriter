package parser

import (
	"fmt"
)

type ElementLeafATXHeader struct {
	element *Element
	level   int
}

func NewElementLeafATXHeader(text *UTF8String, level int) *ElementLeafATXHeader {
	elem := &ElementLeafATXHeader{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_ATX_HEADER,
		isOpen:        false,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          text,
	}
	elem.level = level
	return elem
}

func (elem *ElementLeafATXHeader) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafATXHeader) OpenString() string {
	return fmt.Sprintf("<h%d>", elem.level)
}

func (elem *ElementLeafATXHeader) CloseString() string {
	return fmt.Sprintf("</h%d>\n", elem.level)
}

func (elem *ElementLeafATXHeader) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafATXHeader) TryClose(last IElement) bool {
	return true
}

func ParseLeafATXHeader(doc *Document, line *UTF8String, offset int) (bool, int) {
	// Skip leading blanks.
	length := line.Length()
	beginIndex := SkipLeadingSpace(line, offset)
	if beginIndex == length || beginIndex-offset >= 4 {
		return false, 0
	}
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
