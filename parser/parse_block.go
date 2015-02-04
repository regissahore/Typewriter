package parser

func parseBlock(doc *Document, line *UTF8String) *Document {
	parseLeaf(doc, line, parseContainer(doc, line))
	return doc
}
