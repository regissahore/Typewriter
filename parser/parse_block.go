package parser

func parseBlock(doc *Document, line *UTF8String) *Document {
	offset, firstLine := parseContainer(doc, line)
	leaf := parseLeaf(doc, line, offset, firstLine)
	// Add container element(s).
	var i int
	for i = 0; i < len(doc.CurrentContainers) && i < len(doc.LastContainers); i++ {
		if doc.CurrentContainers[i].GetBase().Function != doc.LastContainers[i].GetBase().Function {
			break
		}
	}
	if i == len(doc.CurrentContainers) {
		if i == len(doc.LastContainers) {
			// The status is unchanged.
		} else {
			if leaf.GetBase().Function == ELEMENT_TYPE_LEAF_PARAGRAPH && doc.LastLeaf.GetBase().Function == ELEMENT_TYPE_LEAF_PARAGRAPH {
				// Lazy.
			} else {
				// Non-lazy.
				doc.CloseTo(doc.LastContainers[i])
				doc.LastContainers = doc.LastContainers[:i]
			}
		}
	} else {
		if i < len(doc.LastContainers) {
			doc.CloseTo(doc.LastContainers[i])
		}
		for j := i; j < len(doc.CurrentContainers); j++ {
			doc.AddElement(doc.CurrentContainers[j])
		}
		doc.LastContainers = append(doc.LastContainers[:i], doc.CurrentContainers[i:]...)
	}
	// Add leaf element.
	doc.AddElement(leaf)
	return doc
}
