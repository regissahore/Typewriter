package parser

func parseBlock(doc *Document, text string) {
	line := NewUTF8String(text + "\n")
	offset := 0
	for {
		offset += parseBlockSub(doc, line, offset)
		if offset == line.Length() {
			break
		}
	}
}

func parseBlockSub(doc *Document, line *UTF8String, offset int) int {
	length := line.Length()
	first := SkipLeadingSpace(line, offset)
	if first == length {
		doc.AddElement(NewElementLeafBlankLine(line.Right(offset)))
		return length - offset
	}
	success := false
	switch doc.GetLastOpen().GetBase().Function {
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		success, length = parseLeafFencedCodeBlock(doc, line, offset)
	}
	if first-offset >= 4 {
		doc.AddElement(NewElementLeafIndentedCodeBlock(line.Right(offset + 4)))
		return length - offset
	}
	switch doc.GetLastOpen().GetBase().Function {
	case ELEMENT_TYPE_LEAF_HTML_BLOCK:
		success, length = parseLeafHTMLBlock(doc, line, offset)
	}
	if success {
		return length
	}
	switch line.RuneAt(first) {
	case '=':
		success, length = parseLeafSetextHeader(doc, line, offset)
	case '-':
		// Setext header has higher priority than horizontal rule.
		success, length = parseLeafSetextHeader(doc, line, offset)
		if !success {
			success, length = parseLeafHorizontalRule(doc, line, offset)
		}
	case '_':
		fallthrough
	case '*':
		success, length = parseLeafHorizontalRule(doc, line, offset)
	case '#':
		success, length = parseLeafATXHeader(doc, line, offset)
	case '`':
		fallthrough
	case '~':
		success, length = parseLeafFencedCodeBlock(doc, line, offset)
	case '<':
		success, length = parseLeafHTMLBlock(doc, line, offset)
	case '[':
		success, length = parseLinkReferenceDefination(doc, line, offset)
	case '>':
		//success, length := ParseLeafBlockQuote(doc, line, offset)
	}
	if !success {
		_, length = parseLeafParagraph(doc, line, offset)
	}
	return length
}
