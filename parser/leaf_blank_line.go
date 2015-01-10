package parser

type ElementLeafBlankLine struct {
	element *Element
}

func NewElementLeafBlankLine() *ElementLeafBlankLine {
	elem := &ElementLeafBlankLine{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_BLANK_LINE,
		isOpen:        false,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          NewUTF8String(""),
	}
	return elem
}

func (elem *ElementLeafBlankLine) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafBlankLine) OpenString() string {
	return ""
}

func (elem *ElementLeafBlankLine) CloseString() string {
	return ""
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
	doc.AddElement(NewElementLeafBlankLine())
	return true, length - offset
}
