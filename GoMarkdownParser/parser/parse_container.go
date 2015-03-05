package parser

func parseContainer(doc *Document, line *UTF8String) (int, bool) {
	length := line.Length()
	offset := 0
	doc.CurrentContainers = make([]IElement, 0)
	firstLine := false
	subsequent := false
	if doc.LastLeaf != nil {
		if doc.LastLeaf.GetBase().Function == ELEMENT_TYPE_LEAF_HTML_BLOCK || doc.LastLeaf.GetBase().Function == ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK {
			subsequent = true
		}
	}
	for offset < length {
		start := SkipLeadingSpace(line, offset)
		if start == length {
			break
		}
		if !firstLine && subsequent && len(doc.CurrentContainers) == len(doc.LastContainers) {
			break
		}
		r := line.RuneAt(start)
		success := false
		size := 0
		if IsDigit(r) {
			//success, size := parseContainerListOrdered(doc, line, offset)
		} else {
			switch r {
			case '>':
				success, size = parseContainerBlockQuote(doc, line, offset)
			case '-':
				fallthrough
			case '+':
				fallthrough
			case '*':
				//success, size := parseContainerListBullet(doc, line, offset)
			}
		}
		if !success {
			break
		}
		if !firstLine {
			index := len(doc.CurrentContainers) - 1
			if index >= len(doc.LastContainers) {
				firstLine = true
			} else if doc.CurrentContainers[index].GetBase().Function != doc.LastContainers[index].GetBase().Function {
				firstLine = true
			}
		}
		offset += size
	}
	if len(doc.CurrentContainers) < len(doc.LastContainers) {
		firstLine = true
	}
	return offset, firstLine
}
