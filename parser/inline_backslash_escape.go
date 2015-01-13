package parser

type ElementInlineBackslashEscape struct {
	element *Element
	symbol	*UTF8String
}

func NewElementInlineBackslashEscape(symbol *UTF8String) *ElementInlineBackslashEscape {
	elem := &ElementInlineBackslashEscape{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_INLINE,
		functionType:  ELEMENT_TYPE_INLINE_BACKSLASH_ESCAPE,
		isOpen:        false,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          NewUTF8String(""),
	}
	elem.symbol = symbol
	return elem
}

func (elem *ElementInlineBackslashEscape) GetElement() *Element {
	return elem.element
}

func (elem *ElementInlineBackslashEscape) OpenString() string {
	return elem.symbol.TranslateHTML()
}

func (elem *ElementInlineBackslashEscape) CloseString() string {
	return ""
}

func (elem *ElementInlineBackslashEscape) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementInlineBackslashEscape) TryClose(last IElement) bool {
	return true
}

func ParseInlineBackslashEscape(doc *Document, line *UTF8String, offset int) (bool, int) {
	if line.RuneAt(offset) != '\\' {
		return false, 0
	}
	length := line.Length()
	if offset <= length-2 {
		if line.RuneAt(offset+1) == '\n' {
			return false, 0
		}
	}
	if offset < length - 1 {
		if IsPunction(line.RuneAt(offset + 1)) {
			doc.AddElement(NewElementInlineBackslashEscape(line.Substring(offset + 1, 1)))
			return true, 2
		}
	}
	return false, 0
}
