package parser

type ElementLeafParagraph struct {
	Base    *Element
	LineNum int
	Abondon bool // Change to setext header.
}

func NewElementLeafParagraph(text *UTF8String) *ElementLeafParagraph {
	elem := &ElementLeafParagraph{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_PARAGRAPH,
		Open:     true,
		Children: nil,
		Inlines:  []*UTF8String{text},
	}
	elem.LineNum = 1
	elem.Abondon = false
	return elem
}

func (elem *ElementLeafParagraph) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafParagraph) Translate(output chan<- string) {
	if elem.Abondon {
		return
	}
	output <- "<p>"
	elem.Base.TranslateAllChildren(output)
	output <- "</p>\n"
}

func (elem *ElementLeafParagraph) TryAppend(last IElement) bool {
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_PARAGRAPH {
		elem.GetBase().Inlines[0] = elem.GetBase().Inlines[0].Append(NewUTF8String("\n").Append(paragraphTrim(last.GetBase().Inlines[0])))
		elem.LineNum++
		return true
	}
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK {
		elem.GetBase().Inlines[0] = elem.GetBase().Inlines[0].Append(NewUTF8String("\n").Append(paragraphTrim(last.(*ElementLeafIndentedCodeBlock).Code)))
		elem.LineNum++
		return true
	}
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_SETEXT_HEADER {
		elem.Abondon = true
		elem.Base.Inlines = nil
	}
	return false
}

func (elem *ElementLeafParagraph) TryClose(last IElement) bool {
	switch last.GetBase().Function {
	case ELEMENT_TYPE_LEAF_BLANK_LINE:
		fallthrough
	case ELEMENT_TYPE_LEAF_HORIZONTAL_RULE:
		fallthrough
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		fallthrough
	case ELEMENT_TYPE_LEAF_HTML_BLOCK:
		fallthrough
	case ELEMENT_TYPE_LEAF_ATX_HEADER:
		fallthrough
	case ELEMENT_TYPE_LEAF_SETEXT_HEADER:
		return true
	}
	return false
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
	doc.AddElement(NewElementLeafParagraph(paragraphTrim(line.Right(offset))))
	return true, length - offset
}
