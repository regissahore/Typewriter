package parser

type ElementInlineHardLineBreak struct {
	element *Element
}

func NewElementInlineHardLineBreak() *ElementInlineHardLineBreak {
	elem := &ElementInlineHardLineBreak{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_INLINE,
		functionType:  ELEMENT_TYPE_INLINE_HARD_LINE_BREAK,
		isOpen:        false,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          NewUTF8String(""),
	}
	return elem
}

func (elem *ElementInlineHardLineBreak) GetElement() *Element {
	return elem.element
}

func (elem *ElementInlineHardLineBreak) OpenString() string {
	return "<br />\n"
}

func (elem *ElementInlineHardLineBreak) CloseString() string {
	return ""
}

func (elem *ElementInlineHardLineBreak) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementInlineHardLineBreak) TryClose(last IElement) bool {
	return true
}

func ParseInlineHardLineBreak(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	if offset <= length-2 {
		if line.RuneAt(offset) == '\\' && line.RuneAt(offset+1) == '\n' {
			doc.AddElement(NewElementInlineHardLineBreak())
			return true, 2
		}
	}
	if offset <= length-3 {
		if line.RuneAt(offset) == ' ' && line.RuneAt(offset+1) == ' ' && line.RuneAt(offset+2) == '\n' {
			doc.AddElement(NewElementInlineHardLineBreak())
			return true, 3
		}
	}
	return false, 0
}
