package parser

type ElementLeafIndentedCodeBlock struct {
	Base *Element
	Code *UTF8String
}

func NewElementLeafIndentedCodeBlock(text *UTF8String) *ElementLeafIndentedCodeBlock {
	elem := &ElementLeafIndentedCodeBlock{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK,
		Open:     true,
		Children: nil,
		Inlines:  nil,
	}
	elem.Code = text
	return elem
}

func (elem *ElementLeafIndentedCodeBlock) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafIndentedCodeBlock) Translate(output chan<- string) {
	output <- "<pre><code>"
	output <- elem.Code.Left(elem.Code.Length() - 1).TranslateHTML()
	output <- "</code></pre>\n"
}

func (elem *ElementLeafIndentedCodeBlock) TryAppend(last IElement) bool {
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK {
		elem.Code = elem.Code.Append(last.(*ElementLeafIndentedCodeBlock).Code)
		return true
	} else if last.GetBase().Function == ELEMENT_TYPE_LEAF_BLANK_LINE {
		blank := last.(*ElementLeafBlankLine).Blank
		if blank.Length() > 4 {
			elem.Code = elem.Code.Append(blank.Right(4))
		} else {
			elem.Code = elem.Code.Append(NewUTF8String("\n"))
		}
		return true
	}
	return false
}

func (elem *ElementLeafIndentedCodeBlock) TryClose(last IElement) bool {
	return true
}
