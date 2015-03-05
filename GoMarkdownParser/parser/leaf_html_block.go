package parser

type ElementLeafHTMLBlock struct {
	Base *Element
	Raw  *UTF8String
}

func NewElementLeafHTMLBlock(raw *UTF8String) *ElementLeafHTMLBlock {
	elem := &ElementLeafHTMLBlock{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_HTML_BLOCK,
		Open:     true,
		Children: nil,
		Inlines:  nil,
	}
	elem.Raw = raw
	return elem
}

func (elem *ElementLeafHTMLBlock) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafHTMLBlock) Translate(output chan<- string) {
	output <- elem.Raw.String()
}

func (elem *ElementLeafHTMLBlock) TryAppend(last IElement) bool {
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_HTML_BLOCK {
		elem.Raw = elem.Raw.Append(last.(*ElementLeafHTMLBlock).Raw)
		return true
	}
	return false
}

func (elem *ElementLeafHTMLBlock) TryClose(last IElement) bool {
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_BLANK_LINE {
		return true
	}
	return false
}

// HTML block begins with "<valid-tag>", "<!" or "<?".
// Ends with blank line.
func parseLeafHTMLBlock(doc *Document, line *UTF8String, offset int, firstLine bool) IElement {
	length := line.Length()
	switch doc.GetLastLeafFunction() {
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		return nil
	}
	index := SkipLeadingSpace(line, offset)
	if !firstLine && doc.GetLastLeafFunction() == ELEMENT_TYPE_LEAF_HTML_BLOCK {
		return NewElementLeafHTMLBlock(line.Right(offset))
	}
	if index-offset >= 4 {
		return nil
	}
	if line.RuneAt(index) != '<' {
		return nil
	}
	if index <= length-2 {
		if line.RuneAt(index+1) == '?' || line.RuneAt(index+1) == '!' {
			return NewElementLeafHTMLBlock(line.Right(offset))
		}
	}
	tagBegin := SkipLeadingSpace(line, index+1)
	if tagBegin >= length-1 {
		return nil
	}
	if line.RuneAt(tagBegin) == '/' {
		tagBegin = SkipLeadingSpace(line, tagBegin+1)
	}
	tagEnd := length
	for i := tagBegin; i < length; i++ {
		r := line.RuneAt(i)
		if !IsAlphaOrDigit(r) {
			if !IsWhitespace(r) && r != '/' && r != '>' {
				return nil
			}
			tagEnd = i
			break
		}
	}
	tag := line.Substring(tagBegin, tagEnd-tagBegin)
	_, exist := GetHTMLBlockMap()[tag.String()]
	if exist {
		return NewElementLeafHTMLBlock(line.Substring(offset, length-offset))
	}
	return nil
}
