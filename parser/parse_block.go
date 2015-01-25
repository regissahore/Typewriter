package parser

func parseBlock(source *UTF8String) *Document {
	doc := NewDocument()
	offset := 0
	length := source.Length()
	for offset < length {
		offset += parseBlockSub(doc, source, offset)
	}
	return doc
}

func parseBlockSub(doc *Document, source *UTF8String, offset int) int {
	length := source.Length()
	first := SkipLeadingSpace(source, offset)
	last := FindLineEnd(source, offset)
	// The transformed source code will always ends with a '\n'.
	if source.RuneAt(first) == '\n' {
		doc.AddElement(NewElementLeafBlankLine(source.Substring(offset, last-offset)))
		return last - offset
	}
	success := false
	switch doc.GetLastOpen().GetBase().Function {
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		success, length = parseLeafFencedCodeBlock(doc, source, offset, last)
	case ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION:
		success, length = parseLeafLinkReferenceDefination(doc, source, offset, last)
	}
	if success {
		return length
	}
	if first-offset >= 4 {
		doc.AddElement(NewElementLeafIndentedCodeBlock(source.Substring(offset+4, last-offset-4)))
		return last - offset
	}
	switch doc.GetLastOpen().GetBase().Function {
	case ELEMENT_TYPE_LEAF_HTML_BLOCK:
		success, length = parseLeafHTMLBlock(doc, source, offset, last)
	}
	if success {
		return length
	}
	switch source.RuneAt(first) {
	case '=':
		success, length = parseLeafSetextHeader(doc, source, offset, last)
	case '-':
		// Setext header has higher priority than horizontal rule.
		success, length = parseLeafSetextHeader(doc, source, offset, last)
		if !success {
			success, length = parseLeafHorizontalRule(doc, source, offset, last)
		}
	case '_':
		fallthrough
	case '*':
		success, length = parseLeafHorizontalRule(doc, source, offset, last)
	case '#':
		success, length = parseLeafATXHeader(doc, source, offset, last)
	case '`':
		fallthrough
	case '~':
		success, length = parseLeafFencedCodeBlock(doc, source, offset, last)
	case '<':
		success, length = parseLeafHTMLBlock(doc, source, offset, last)
	case '[':
		success, length = parseLeafLinkReferenceDefination(doc, source, offset, last)
	case '>':
		//success, length := ParseLeafBlockQuote(doc, source, offset, last)
	}
	if !success {
		_, length = parseLeafParagraph(doc, source, offset, last)
	}
	return length
}
