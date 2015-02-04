package parser

import (
	"fmt"
)

type ElementLeafFencedCodeBlock struct {
	Base      *Element
	Symbol    rune
	SymbolLen int
	Leading   int
	Info      *UTF8String
	Code      *UTF8String
	End       bool
}

func NewElementLeafFencedCodeBlockBegin(symbol rune, symbolLen int, leading int, info *UTF8String) *ElementLeafFencedCodeBlock {
	elem := &ElementLeafFencedCodeBlock{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK,
		Open:     true,
		Children: nil,
		Inlines:  nil,
	}
	elem.Symbol = symbol
	elem.SymbolLen = symbolLen
	elem.Leading = leading
	elem.Info = info
	elem.Code = NewUTF8String("")
	elem.End = false
	return elem
}

func NewElementLeafFencedCodeBlockCode(code *UTF8String) *ElementLeafFencedCodeBlock {
	elem := &ElementLeafFencedCodeBlock{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK,
	}
	elem.Code = code
	elem.End = false
	return elem
}

func NewElementLeafFencedCodeBlockEnd() *ElementLeafFencedCodeBlock {
	elem := &ElementLeafFencedCodeBlock{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK,
	}
	elem.End = true
	return elem
}

func (elem *ElementLeafFencedCodeBlock) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafFencedCodeBlock) Translate(output chan<- string) {
	if elem.End {
		return
	}
	pre := "<pre><code>\n"
	if elem.Info != nil {
		if elem.Info.Length() != 0 {
			pre = fmt.Sprintf("<pre><code class=\"language-%s\">\n", elem.Info) + elem.Code.TranslateHTML()
		}
	}
	output <- pre
	output <- elem.Code.TranslateHTML()
	output <- "</code></pre>\n"
}

func (elem *ElementLeafFencedCodeBlock) TryAppend(last IElement) bool {
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK {
		if last.(*ElementLeafFencedCodeBlock).End {
			return false
		}
		lastCode := last.(*ElementLeafFencedCodeBlock).Code
		spaceNum := lastCode.LeadingSpaceNum()
		if elem.Leading < spaceNum {
			spaceNum = elem.Leading
		}
		lastCode = lastCode.Right(spaceNum)
		elem.Code = elem.Code.Append(lastCode)
		return true
	}
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_BLANK_LINE {
		blank := last.(*ElementLeafBlankLine).Blank
		spaceNum := blank.LeadingSpaceNum()
		if elem.Leading < spaceNum {
			spaceNum = elem.Leading
		}
		lastCode := blank.Right(spaceNum)
		elem.Code = elem.Code.Append(lastCode)
		return true
	}
	return false
}

func (elem *ElementLeafFencedCodeBlock) TryClose(last IElement) bool {
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK {
		if last.(*ElementLeafFencedCodeBlock).End {
			return true
		}
	}
	return false
}

func parseLeafFencedCodeBlockBegin(doc *Document, line *UTF8String, offset int) bool {
	length := line.Length()
	switch doc.GetLastLeafFunction() {
	case ELEMENT_TYPE_LEAF_HTML_BLOCK:
		return false
	}
	leading := SkipLeadingSpace(line, offset)
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
	index = SkipLeadingSpace(line, index)
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
	if symbol != doc.LastLeaf.(*ElementLeafFencedCodeBlock).Symbol {
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
	if symbolLen < doc.LastLeaf.(*ElementLeafFencedCodeBlock).SymbolLen {
		return false
	}
	doc.AddElement(NewElementLeafFencedCodeBlockEnd())
	return true
}

// Fenced code blocks begins with at least 3 consecutive '`'s or '~'s.
// Ends with at least the same number '`'s or '~'s.
// '`' and '~' cannot be mixed.
// Info string is optional and should not contain '`'.
// Indentation will be removed the same length as the leading code fence.
func parseLeafFencedCodeBlock(doc *Document, line *UTF8String, offset int) bool {
	// Inherit from length open code block.
	if doc.GetLastLeafFunction() == ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK {
		if parseLeafFencedCodeBlockEnd(doc, line, offset) {
			return true
		}
		doc.AddElement(NewElementLeafFencedCodeBlockCode(line.Right(offset)))
		return true
	}
	// Whether code block begins.
	if parseLeafFencedCodeBlockBegin(doc, line, offset) {
		return true
	}
	return false
}
