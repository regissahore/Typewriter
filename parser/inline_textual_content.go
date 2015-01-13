package parser

type ElementInlineTextualContent struct {
	element *Element
}

func NewElementInlineTextualContent(r rune) *ElementInlineTextualContent {
	elem := &ElementInlineTextualContent{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_INLINE,
		functionType:  ELEMENT_TYPE_INLINE_TEXTUAL_CONTENT,
		isOpen:        true,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          NewUTF8String(string(r)),
	}
	return elem
}

func (elem *ElementInlineTextualContent) GetElement() *Element {
	return elem.element
}

func (elem *ElementInlineTextualContent) OpenString() string {
	return elem.element.text.TranslateHTML()
}

func (elem *ElementInlineTextualContent) CloseString() string {
	return ""
}

func (elem *ElementInlineTextualContent) TryAppend(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_INLINE_TEXTUAL_CONTENT {
		elem.element.text = elem.element.text.Append(last.GetElement().text)
		return true
	}
	return false
}

func (elem *ElementInlineTextualContent) TryClose(last IElement) bool {
	return true
}

func ParseInlineTextualContent(doc *Document, line *UTF8String, offset int) (bool, int) {
	doc.AddElement(NewElementInlineTextualContent(line.RuneAt(offset)))
	return true, 1
}
