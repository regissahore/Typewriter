package parser

func parseLeaf(doc *Document, line *UTF8String, offset int, firstLine bool) IElement {
	var elem IElement
	length := line.Length()
	first := SkipLeadingSpace(line, offset)
	switch doc.GetLastLeafFunction() {
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		elem = parseLeafFencedCodeBlock(doc, line, offset, firstLine)
	case ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION:
		elem = parseLeafLinkReferenceDefination(doc, line, offset, firstLine)
	}
	if elem != nil {
		return elem
	}
	if first == length {
		lineNum := 1
		if doc.LastLeaf != nil {
			if doc.GetLastLeafFunction() == ELEMENT_TYPE_LEAF_BLANK_LINE {
				lineNum = doc.LastLeaf.(*ElementLeafBlankLine).LineNum + 1
			}
		}
		return NewElementLeafBlankLine(line.Right(offset), lineNum)
	}
	if doc.GetLastLeafFunction() == ELEMENT_TYPE_LEAF_HTML_BLOCK {
		elem := parseLeafHTMLBlock(doc, line, offset, firstLine)
		if elem != nil {
			return elem
		}
	}
	if first-offset >= 4 {
		if doc.GetLastLeafFunction() == ELEMENT_TYPE_LEAF_PARAGRAPH {
			return parseLeafParagraph(doc, line, offset)
		} else {
			return NewElementLeafIndentedCodeBlock(line.Right(offset + 4))
		}
	}
	switch line.RuneAt(first) {
	case '=':
		elem = parseLeafSetextHeader(doc, line, offset, firstLine)
	case '-':
		// Setext header has higher priority than horizontal rule.
		elem = parseLeafSetextHeader(doc, line, offset, firstLine)
		if elem == nil {
			elem = parseLeafHorizontalRule(doc, line, offset)
		}
	case '_':
		fallthrough
	case '*':
		elem = parseLeafHorizontalRule(doc, line, offset)
	case '#':
		elem = parseLeafATXHeader(doc, line, offset)
	case '`':
		fallthrough
	case '~':
		elem = parseLeafFencedCodeBlock(doc, line, offset, firstLine)
	case '<':
		elem = parseLeafHTMLBlock(doc, line, offset, firstLine)
	case '[':
		elem = parseLeafLinkReferenceDefination(doc, line, offset, firstLine)
	}
	if elem != nil {
		return elem
	}
	return parseLeafParagraph(doc, line, offset)
}
