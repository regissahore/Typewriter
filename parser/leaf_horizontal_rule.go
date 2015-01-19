package parser

type ElementLeafHorizontalRule struct {
	Base *Element
}

func NewElementLeafHorizontalRule() *ElementLeafHorizontalRule {
	elem := &ElementLeafHorizontalRule{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_HORIZONTAL_RULE,
		Open:     false,
		Children: nil,
		Inlines:  nil,
	}
	return elem
}

func (elem *ElementLeafHorizontalRule) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafHorizontalRule) Translate(output chan<- string) {
	output <- "<hr />\n"
}

func (elem *ElementLeafHorizontalRule) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafHorizontalRule) TryClose(last IElement) bool {
	return true
}

func parseLeafHorizontalRule(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	index := SkipLeadingSpace(line, offset)
	symbol := line.RuneAt(index)
	if symbol != '-' && symbol != '_' && symbol != '*' {
		return false, 0
	}
	symbolNum := 1
	for i := index + 1; i < length; i++ {
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
