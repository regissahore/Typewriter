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
func parseLeafHTMLBlock(doc *Document, source *UTF8String, offset, last int) (bool, int) {
	switch doc.GetLastOpen().GetBase().Function {
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		return false, 0
	}
	index := SkipLeadingSpace(source, offset)
	if doc.GetLastOpen().GetBase().Function == ELEMENT_TYPE_LEAF_HTML_BLOCK {
		doc.AddElement(NewElementLeafHTMLBlock(source.Substring(offset, last-offset)))
		return true, last - offset
	}
	if index-offset >= 4 {
		return false, 0
	}
	if source.RuneAt(index) != '<' {
		return false, 0
	}
	if index <= last-2 {
		if source.RuneAt(index+1) == '?' || source.RuneAt(index+1) == '!' {
			doc.AddElement(NewElementLeafHTMLBlock(source.Substring(offset, last-offset)))
			return true, last - offset
		}
	}
	tagBegin := SkipLeadingSpace(source, index+1)
	if tagBegin >= last-1 {
		return false, 0
	}
	if source.RuneAt(tagBegin) == '/' {
		tagBegin = SkipLeadingSpace(source, tagBegin+1)
	}
	tagEnd := last
	for i := tagBegin; i < last; i++ {
		r := source.RuneAt(i)
		if !IsAlphaOrDigit(r) {
			if !IsWhitespace(r) && r != '/' && r != '>' {
				return false, 0
			}
			tagEnd = i
			break
		}
	}
	tag := source.Substring(tagBegin, tagEnd-tagBegin)
	_, exist := GetHTMLBlockMap()[tag.String()]
	if exist {
		doc.AddElement(NewElementLeafHTMLBlock(source.Substring(offset, last-offset)))
		return true, last - offset
	}
	return false, 0
}
