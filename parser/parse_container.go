package parser

func parseContainer(doc *Document, line *UTF8String) int {
	return 0
	length := line.Length()
	offset := SkipLeadingSpace(line, 0)
	for offset < length {
		r := line.RuneAt(offset)
		success := false
		if IsDigit(r) {
			//success, size := parseContainerListOrdered(doc, line, offset)
		} else {
			switch r {
			case '>':
				//success, size := parseContainerBlockQuote(doc, line, offset)
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
	}
	for _, container := range doc.CurrentContainers {
		doc.AddElement(container)
	}
	return offset
}
