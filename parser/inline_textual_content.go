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
	str := NewUTF8String("")
	length := elem.element.text.Length()
	for i := 0; i < length; i++ {
		r := elem.element.text.RuneAt(i)
		switch r {
		case '"':
			str = str.Append(NewUTF8String("&quot;"))
		case '&':
			str = str.Append(NewUTF8String("&amp;"))
		case '<':
			str = str.Append(NewUTF8String("&lt;"))
		case '>':
			str = str.Append(NewUTF8String("&gt;"))
		default:
			str.Text = append(str.Text, r)
		}
	}
	return str.String()
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
