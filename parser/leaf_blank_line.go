package parser

type ElementLeafBlankLine struct {
	Base  *Element
	Blank *UTF8String
}

func NewElementLeafBlankLine(blank *UTF8String) *ElementLeafBlankLine {
	elem := &ElementLeafBlankLine{}
	elem.Base = &Element{
		Structure: ELEMENT_TYPE_LEAF,
		Function:  ELEMENT_TYPE_LEAF_BLANK_LINE,
		Open:      false,
		Children:  make([]IElement, 0),
		Inlines:   nil,
	}
	elem.Blank = blank
	return elem
}

func (elem *ElementLeafBlankLine) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafBlankLine) Translate(output chan<- string) {
	output <- "\n"
}

func (elem *ElementLeafBlankLine) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafBlankLine) TryClose(last IElement) bool {
	return true
}

func ParseLeafBlankLine(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	for i := offset; i < length; i++ {
		if !IsWhitespace(line.RuneAt(i)) {
			return false, 0
		}
	}
	doc.AddElement(NewElementLeafBlankLine(line.Right(offset)))
	return true, length - offset
}
