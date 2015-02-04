package parser

func parseBlock(doc *Document, line *UTF8String) *Document {
	parseLeaf(doc, line, parseContainer(doc, line))
	// TODO try close container.
	return doc
}

func parseContainer(doc *Document, line *UTF8String) int {
	return 0
}

func parseLeaf(doc *Document, line *UTF8String, offset int) {
	length := line.Length()
	first := SkipLeadingSpace(line, offset)
	success := false
	switch doc.GetLastOpen().GetBase().Function {
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		success = parseLeafFencedCodeBlock(doc, line, offset)
	case ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION:
		success = parseLeafLinkReferenceDefination(doc, line, offset)
	}
	if success {
		return
	}
	if first == length {
		doc.AddElement(NewElementLeafBlankLine(line.Right(offset)))
		return
	}
	if doc.GetLastOpen().GetBase().Function == ELEMENT_TYPE_LEAF_HTML_BLOCK {
		if parseLeafHTMLBlock(doc, line, offset) {
			return
		}
	}
	if first-offset >= 4 {
		if doc.GetLastOpen().GetBase().Function == ELEMENT_TYPE_LEAF_PARAGRAPH {
			parseLeafParagraph(doc, line, offset)
			return
		} else {
			doc.AddElement(NewElementLeafIndentedCodeBlock(line.Right(offset + 4)))
			return
		}
	}
	if success {
		return
	}
	switch line.RuneAt(first) {
	case '=':
		success = parseLeafSetextHeader(doc, line, offset)
	case '-':
		// Setext header has higher priority than horizontal rule.
		success = parseLeafSetextHeader(doc, line, offset)
		if !success {
			success = parseLeafHorizontalRule(doc, line, offset)
		}
	case '_':
		fallthrough
	case '*':
		success = parseLeafHorizontalRule(doc, line, offset)
	case '#':
		success = parseLeafATXHeader(doc, line, offset)
	case '`':
		fallthrough
	case '~':
		success = parseLeafFencedCodeBlock(doc, line, offset)
	case '<':
		success = parseLeafHTMLBlock(doc, line, offset)
	case '[':
		success = parseLeafLinkReferenceDefination(doc, line, offset)
	}
	if success {
		return
	}
	parseLeafParagraph(doc, line, offset)
}
