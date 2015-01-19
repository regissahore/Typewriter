package parser

func parseBlock(doc *Document, text string) {
	line := NewUTF8String(text + "\n")
	for offset := 0; offset < line.Length(); {
		offset += parseBlockSub(doc, line, offset)
	}
}

func parseBlockSub(doc *Document, line *UTF8String, offset int) int {
	length := line.Length()
	first := SkipLeadingSpace(line, offset)
	if first == length {
		doc.AddElement(NewElementLeafBlankLine(line.Right(offset)))
		return length - offset
	}
	if first-offset >= 4 {
		doc.AddElement(NewElementLeafIndentedCodeBlock(line.Right(offset)))
		return length - offset
	}
	success := false
	increase := 0
	switch line.RuneAt(first) {
	case '=':
		success, increase = parseLeafSetextHeader(doc, line, first)
	case '-':
		// Setext header has higher priority than horizontal rule.
		success, increase = parseLeafSetextHeader(doc, line, first)
		if !success {
			success, increase = ParseLeafHorizontalRule(doc, line, first)
		}
	case '_':
		fallthrough
	case '*':
		success, increase = ParseLeafHorizontalRule(doc, line, first)
	case '#':
		success, increase = ParseLeafATXHeader(doc, line, first)
	case '`':
		success, increase = ParseLeafFencedCodeBlock(doc, line, first)
	case '<':
		success, increase = ParseLeafHTMLBlock(doc, line, first)
	case '[':
		success, increase = ParseLinkReferenceDefination(doc, line, first)
	case '>':
		//success, increase := ParseLeafBlockQuote(doc, line, first)
	}
	if !success {
		_, increase = ParseLeafParagraph(doc, line, first)
	}
	return increase + first - offset
}
