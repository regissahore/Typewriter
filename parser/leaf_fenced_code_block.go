package parser

import (
	"fmt"
)

type ElementLeafFencedCodeBlock struct {
	element   *Element
	symbol    rune
	symbolLen int
	leading   int
	info      *UTF8String
	code      *UTF8String
	end       bool
}

func NewElementLeafFencedCodeBlockBegin(symbol rune, symbolLen int, leading int, info *UTF8String) *ElementLeafFencedCodeBlock {
	elem := &ElementLeafFencedCodeBlock{}
	elem.element = &Element{
		structureType: ELEMENT_TYPE_LEAF,
		functionType:  ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK,
		isOpen:        true,
		parent:        nil,
		children:      make([]IElement, 0),
		text:          NewUTF8String(""),
	}
	elem.symbol = symbol
	elem.symbolLen = symbolLen
	elem.leading = leading
	elem.info = info
	elem.code = NewUTF8String("")
	elem.end = false
	return elem
}

func NewElementLeafFencedCodeBlockCode(code *UTF8String) *ElementLeafFencedCodeBlock {
	elem := &ElementLeafFencedCodeBlock{}
	elem.element = &Element{
		functionType: ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK,
	}
	elem.code = code
	elem.end = false
	return elem
}

func NewElementLeafFencedCodeBlockEnd() *ElementLeafFencedCodeBlock {
	elem := &ElementLeafFencedCodeBlock{}
	elem.element = &Element{
		functionType: ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK,
	}
	elem.end = true
	return elem
}

func (elem *ElementLeafFencedCodeBlock) GetElement() *Element {
	return elem.element
}

func (elem *ElementLeafFencedCodeBlock) OpenString() string {
	if elem.end {
		return ""
	}
	if elem.info != nil {
		if elem.info.Length() != 0 {
			return fmt.Sprintf("<pre><code class=\"language-%s\">\n", elem.info) + elem.code.TranslateHTML()
		}
	}
	return "<pre><code>\n" + elem.code.TranslateHTML()
}

func (elem *ElementLeafFencedCodeBlock) CloseString() string {
	if elem.end {
		return ""
	}
	return "</code></pre>\n"
}

func (elem *ElementLeafFencedCodeBlock) TryAppend(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK {
		if last.(*ElementLeafFencedCodeBlock).end {
			return false
		}
		lastCode := last.(*ElementLeafFencedCodeBlock).code
		spaceNum := lastCode.LeadingSpaceNum()
		if elem.leading < spaceNum {
			spaceNum = elem.leading
		}
		lastCode = lastCode.Right(spaceNum)
		elem.code = elem.code.Append(lastCode)
		return true
	}
	return false
}

func (elem *ElementLeafFencedCodeBlock) TryClose(last IElement) bool {
	if last.GetElement().functionType == ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK {
		if last.(*ElementLeafFencedCodeBlock).end {
			return true
		}
	}
	return false
}

func parseLeafFencedCodeBlockBegin(doc *Document, line *UTF8String, offset int) bool {
	length := line.Length()
	leading := SkipLeadingSpace(line, offset)
	if leading == length || leading-offset >= 4 {
		return false
	}
	symbol := line.RuneAt(leading)
	if symbol != '`' && symbol != '~' {
		return false
	}
	symbolLen := 1
	index := length
	for i := leading + 1; i < length; i++ {
		r := line.RuneAt(i)
		if r == symbol {
			symbolLen++
		} else {
			index = i
			break
		}
	}
	first := true
	info := NewUTF8String("")
	for i := index; i < length; i++ {
		r := line.RuneAt(i)
		if r == '`' {
			return false
		} else if IsWhitespace(r) {
			if first {
				first = false
				info = line.Substring(index, i-index)
			}
		}
	}
	doc.AddElement(NewElementLeafFencedCodeBlockBegin(symbol, symbolLen, leading, info))
	return true
}

func parseLeafFencedCodeBlockEnd(doc *Document, line *UTF8String, offset int) bool {
	length := line.Length()
	index := SkipLeadingSpace(line, offset)
	if index == length || index-offset >= 4 {
		return false
	}
	symbol := line.RuneAt(index)
	if symbol != doc.GetLastOpen().(*ElementLeafFencedCodeBlock).symbol {
		return false
	}
	symbolLen := 1
	for i := index + 1; i < length; i++ {
		r := line.RuneAt(i)
		if r == symbol {
			symbolLen++
		} else if IsWhitespace(r) {
			index = i
			break
		} else {
			return false
		}
	}
	for i := index + 1; i < length; i++ {
		r := line.RuneAt(i)
		if !IsWhitespace(r) {
			return false
		}
	}
	if symbolLen < doc.GetLastOpen().(*ElementLeafFencedCodeBlock).symbolLen {
		return false
	}
	doc.AddElement(NewElementLeafFencedCodeBlockEnd())
	return true
}

func ParseLeafFencedCodeBlock(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	// Inherit from last open code block.
	if doc.GetLastOpen().GetElement().functionType == ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK {
		if parseLeafFencedCodeBlockEnd(doc, line, offset) {
			return true, length - offset
		}
		doc.AddElement(NewElementLeafFencedCodeBlockCode(line.Right(offset)))
		return true, length - offset
	}
	// Whether code block begins.
	if parseLeafFencedCodeBlockBegin(doc, line, offset) {
		return true, length - offset
	}
	return false, 0
}
