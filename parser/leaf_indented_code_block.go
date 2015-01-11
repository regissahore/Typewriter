package parser

type ElementLeafIndentedCodeBlock struct {
	element *Element
}

func NewElementLeafIndentedCodeBlock(text *UTF8String) *ElementLeafIndentedCodeBlock {
	elem := &ElementLeafIndentedCodeBlock{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK,
		isOpen:        true,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          text,
	}
	return elem
}

func (elem *ElementLeafIndentedCodeBlock) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafIndentedCodeBlock) OpenString() string {
	return "<pre><code>"
}

func (elem *ElementLeafIndentedCodeBlock) CloseString() string {
	return "</code></pre>\n"
}

func (elem *ElementLeafIndentedCodeBlock) TryAppend(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK {
		elem.element.text = elem.element.text.Append(last.GetElement().text)
		return true
	} else if last.GetElement().functionType == ELEMENT_TYPE_LEAF_BLANK_LINE {
		if last.GetElement().text.Length() > 4 {
			elem.element.text = elem.element.text.Append(last.GetElement().text.Right(4))
		} else {
			elem.element.text = elem.element.text.Append(NewUTF8String("\n"))
		}
		return true
	}
	return false
}

func (elem *ElementLeafIndentedCodeBlock) TryClose(last IElement) bool {
	return true
}

func ParseLeafIndentedCodeBlock(doc *Document, line *UTF8String, offset int) (bool, int) {
	// Cannot interrupt paragraph.
	if doc.GetLastOpen().GetElement().functionType == ELEMENT_TYPE_LEAF_PARAGRAPH {
		return false, 0
	}
	// Count spaces.
	spaceNum := 0
	length := line.Length()
	for i := offset; i < length; i++ {
		if line.RuneAt(i) != ' ' {
			return false, 0
		}
		spaceNum++
		if spaceNum == 4 {
			break
		}
	}
	doc.AddElement(NewElementLeafIndentedCodeBlock(line.Substring(offset+4, length-offset-4)))
	return true, length - offset
}
