package parser

type ElementLeafHTMLBlock struct {
	element *Element
	raw     *UTF8String
}

func NewElementLeafHTMLBlock(raw *UTF8String) *ElementLeafHTMLBlock {
	elem := &ElementLeafHTMLBlock{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_HTML_BLOCK,
		isOpen:        true,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          NewUTF8String(""),
	}
	elem.raw = raw
	return elem
}

func (elem *ElementLeafHTMLBlock) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafHTMLBlock) OpenString() string {
	return elem.raw.String()
}

func (elem *ElementLeafHTMLBlock) CloseString() string {
	return ""
}

func (elem *ElementLeafHTMLBlock) TryAppend(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_LEAF_HTML_BLOCK {
		elem.raw = elem.raw.Append(last.(*ElementLeafHTMLBlock).raw)
		return true
	}
	return false
}

func (elem *ElementLeafHTMLBlock) TryClose(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_LEAF_BLANK_LINE {
		return true
	}
	return false
}

var htmlBlockTagMap map[string]bool

func initHTMLBlockTagMap() {
	if htmlBlockTagMap == nil {
		htmlBlockTagMap = map[string]bool{
			"article":    true,
			"header":     true,
			"aside":      true,
			"hgroup":     true,
			"blockquote": true,
			"hr":         true,
			"iframe":     true,
			"body":       true,
			"li":         true,
			"map":        true,
			"button":     true,
			"object":     true,
			"canvas":     true,
			"ol":         true,
			"caption":    true,
			"output":     true,
			"col":        true,
			"p":          true,
			"colgroup":   true,
			"pre":        true,
			"dd":         true,
			"progress":   true,
			"div":        true,
			"section":    true,
			"dl":         true,
			"table":      true,
			"td":         true,
			"dt":         true,
			"tbody":      true,
			"embed":      true,
			"textarea":   true,
			"fieldset":   true,
			"tfoot":      true,
			"figcaption": true,
			"th":         true,
			"figure":     true,
			"thead":      true,
			"footer":     true,
			"tr":         true,
			"form":       true,
			"ul":         true,
			"h1":         true,
			"h2":         true,
			"h3":         true,
			"h4":         true,
			"h5":         true,
			"h6":         true,
			"video":      true,
			"script":     true,
			"style":      true,
		}
	}
}

func ParseLeafHTMLBlock(doc *Document, line *UTF8String, offset int) (bool, int) {
	switch doc.GetLastOpen().GetElement().functionType {
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		return false, 0
	}
	length := line.Length()
	index := SkipLeadingSpace(line, offset)
	if index == length {
		return false, 0
	}
	if doc.GetLastOpen().GetElement().functionType == ELEMENT_TYPE_LEAF_HTML_BLOCK {
		doc.AddElement(NewElementLeafHTMLBlock(line.Right(offset)))
		return true, length - offset
	}
	if index-offset >= 4 {
		return false, 0
	}
	if line.RuneAt(index) != '<' {
		return false, 0
	}
	if index <= length-2 {
		if line.RuneAt(index+1) == '?' || line.RuneAt(index+1) == '!' {
			doc.AddElement(NewElementLeafHTMLBlock(line.Right(offset)))
			return true, length - offset
		}
	}
	tagBegin := SkipLeadingSpace(line, index+1)
	if tagBegin >= length-1 {
		return false, 0
	}
	if line.RuneAt(tagBegin) == '/' {
		tagBegin = SkipLeadingSpace(line, tagBegin+1)
	}
	tagEnd := length
	for i := tagBegin; i < length; i++ {
		r := line.RuneAt(i)
		if !IsAlphaOrDigit(r) {
			if !IsWhitespace(r) && r != '/' && r != '>' {
				return false, 0
			}
			tagEnd = i
			break
		}
	}
	tag := line.Substring(tagBegin, tagEnd-tagBegin)
	initHTMLBlockTagMap()
	_, exists := htmlBlockTagMap[tag.String()]
	if exists {
		doc.AddElement(NewElementLeafHTMLBlock(line.Right(offset)))
		return true, length - offset
	}
	return false, 0
}
