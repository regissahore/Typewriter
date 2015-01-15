package parser

type ElementInlineHardLineBreak struct {
	Base *Element
}

func NewElementInlineHardLineBreak() *ElementInlineHardLineBreak {
	elem := &ElementInlineHardLineBreak{}
	elem.Base = &Element{
		Structure: ELEMENT_TYPE_INLINE,
		Function:  ELEMENT_TYPE_INLINE_HARD_LINE_BREAK,
		Open:      false,
		Children:  make([]IElement, 0),
		Inlines:   nil,
	}
	return elem
}

func (elem *ElementInlineHardLineBreak) GetBase() *Element {
	return elem.Base
}

func (elem *ElementInlineHardLineBreak) Translate(output chan<- string) {
	output <- "<br />\n"
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
