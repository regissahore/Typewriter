package parser

type ElementInlineBackslashEscape struct {
	Base   *Element
	Symbol *UTF8String
}

func NewElementInlineBackslashEscape(symbol *UTF8String) *ElementInlineBackslashEscape {
	elem := &ElementInlineBackslashEscape{}
	elem.Base = &Element{
		Structure: ELEMENT_TYPE_INLINE,
		Function:  ELEMENT_TYPE_INLINE_BACKSLASH_ESCAPE,
		Open:      false,
		Children:  make([]IElement, 0),
		Inlines:   nil,
	}
	elem.Symbol = symbol
	return elem
}

func (elem *ElementInlineBackslashEscape) GetBase() *Element {
	return elem.Base
}

func (elem *ElementInlineBackslashEscape) Translate(output chan<- string) {
	output <- elem.Symbol.TranslateHTML()
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
	if offset < length-1 {
		if IsPunctuation(line.RuneAt(offset + 1)) {
			doc.AddElement(NewElementInlineBackslashEscape(line.Substring(offset+1, 1)))
			return true, 2
		}
	}
	return false, 0
}
