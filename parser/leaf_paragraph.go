package parser

type ElementLeafParagraph struct {
	element *Element
}

func NewElementLeafParagraph(text *UTF8String) *ElementLeafParagraph {
	elem := &ElementLeafParagraph{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_PARAGRAPH,
		isOpen:        true,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          text,
	}
	return elem
}

func (elem *ElementLeafParagraph) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafParagraph) OpenString() string {
	return "<p>"
}

func (elem *ElementLeafParagraph) CloseString() string {
	return "</p>\n"
}

func (elem *ElementLeafParagraph) TryAppend(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_LEAF_PARAGRAPH {
		elem.GetElement().text = elem.GetElement().text.Append(last.GetElement().text)
		return true
	}
	return false
}

func (elem *ElementLeafParagraph) TryClose(last IElement) bool {
	switch last.GetElement().functionType {
	case ELEMENT_TYPE_LEAF_BLANK_LINE:
		return true
	case ELEMENT_TYPE_LEAF_ATX_HEADER:
		return true
	}
	return false
}

func ParseLeafParagraph(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	doc.AddElement(NewElementLeafParagraph(line.Substring(offset, length-offset).Trim().Append(NewUTF8String("\n"))))
	return true, length - offset
}
