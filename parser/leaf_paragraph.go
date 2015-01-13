package parser

type ElementLeafParagraph struct {
	element *Element
	lineNum int
	abondon bool // Change to setext header.
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
	elem.lineNum = 1
	elem.abondon = false
	return elem
}

func (elem *ElementLeafParagraph) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafParagraph) OpenString() string {
	if elem.abondon {
		return ""
	}
	return "<p>"
}

func (elem *ElementLeafParagraph) CloseString() string {
	if elem.abondon {
		return ""
	}
	return "</p>\n"
}

func (elem *ElementLeafParagraph) TryAppend(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_LEAF_PARAGRAPH {
		elem.GetElement().text = elem.GetElement().text.Append(NewUTF8String("\n").Append(last.GetElement().text))
		elem.lineNum++
		return true
	}
	return false
}

func (elem *ElementLeafParagraph) TryClose(last IElement) bool {
	switch last.GetElement().functionType {
	case ELEMENT_TYPE_LEAF_BLANK_LINE:
		fallthrough
	case ELEMENT_TYPE_LEAF_HORIZONTAL_RULE:
		fallthrough
	case ELEMENT_TYPE_LEAF_ATX_HEADER:
		return true
	}
	return false
}

func (elem *ElementLeafParagraph) Abondon() {
	elem.abondon = true
	elem.element.text = NewUTF8String("")
	elem.element.isOpen = false
}

func paragraphTrim(line *UTF8String) *UTF8String {
	length := line.Length()
	if length >= 3 {
		if line.RuneAt(length-2) == ' ' && line.RuneAt(length-3) == ' ' {
			return line.Trim().Append(NewUTF8String("  "))
		}
	}
	return line.Trim()
}

func ParseLeafParagraph(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	doc.AddElement(NewElementLeafParagraph(paragraphTrim(line.Substring(offset, length-offset))))
	return true, length - offset
}
