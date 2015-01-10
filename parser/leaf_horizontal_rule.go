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

func isHorizontalRuleSymbol(r rune) bool {
	return r == '-' || r == '_' || r == '*'
}

func ParseLeafHorizontalRule(doc *Document, line *UTF8String, offset int) (bool, int) {
	var symbol rune
	var symbolNum int
	length := line.Length()
	for i := offset; i < length; i++ {
		r := line.RuneAt(i)
		if IsWhitespace(r) {
			continue
		}
		if isHorizontalRuleSymbol(r) {
			if symbol == 0 {
				symbol = r
			} else if symbol != r {
				return false, 0
			}
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
