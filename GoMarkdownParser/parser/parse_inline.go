package parser

func parseInline(node IElement, progress chan int) {
	if node.GetBase().Children != nil && len(node.GetBase().Children) > 0 {
		for _, child := range node.GetBase().Children {
			parseInline(child, progress)
		}
	} else {
		if node.GetBase().Inlines != nil {
			node.GetBase().Children = make([]IElement, len(node.GetBase().Inlines))
			for index, inline := range node.GetBase().Inlines {
				progress <- 1
				go func() {
					textElem := NewElementInlineTextualContent(inline)
					node.GetBase().Children[index] = textElem
					progress <- -1
				}()
			}
		}
	}
}
