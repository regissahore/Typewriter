package parser

type ElementLeafHorizontalRule struct {
	element *Element
}

func NewElementLeafHorizontalRule() *ElementLeafHorizontalRule {
	elem := &ElementLeafHorizontalRule{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_HORIZONTAL_RULE,
		isOpen:        false,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          NewUTF8String(""),
	}
	return elem
}

func (elem *ElementLeafHorizontalRule) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafHorizontalRule) OpenString() string {
	return "<hr />"
}

func (elem *ElementLeafHorizontalRule) CloseString() string {
	return "\n"
}

func (elem *ElementLeafHorizontalRule) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafHorizontalRule) TryClose(last IElement) bool {
	return true
}

func ParseLeafHorizontalRule(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	index := SkipLeadingSpace(line, offset)
	if index == length || index-offset >= 4 {
		return false, 0
	}
	symbol := line.RuneAt(index)
	if symbol != '-' && symbol != '_' && symbol != '*' {
		return false, 0
	}
	symbolNum := 1
	for i := index; i < length; i++ {
		r := line.RuneAt(i)
		if IsWhitespace(r) {
			continue
		}
		if r == symbol {
			symbolNum++
		} else {
			return false, 0
		}
	}
	if symbolNum < 3 {
		return false, 0
	}
	doc.AddElement(NewElementLeafHorizontalRule())
	return true, length - offset
}
