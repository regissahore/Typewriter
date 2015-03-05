package parser

type ElementLeafBlankLine struct {
	Base    *Element
	Blank   *UTF8String
	LineNum int
}

func NewElementLeafBlankLine(blank *UTF8String, lineNum int) *ElementLeafBlankLine {
	elem := &ElementLeafBlankLine{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_BLANK_LINE,
		Open:     false,
		Children: nil,
		Inlines:  nil,
	}
	elem.Blank = blank
	elem.LineNum = lineNum
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
