package parser

type Document struct {
	Base         *Element
	OpenElements []IElement
}

func NewDocument() *Document {
	doc := &Document{}
	doc.Base = &Element{
		Function: ELEMENT_TYPE_DOCUMENT,
		Open:     true,
		Children: nil,
		Inlines:  nil,
	}
	doc.OpenElements = make([]IElement, 0)
	doc.OpenElements = append(doc.OpenElements, doc)
	return doc
}

func (doc *Document) GetBase() *Element {
	return doc.Base
}

func (doc *Document) Translate(output chan<- string) {
	doc.Base.TranslateAllChildren(output)
}

func (doc *Document) TryAppend(last IElement) bool {
	return false
}

// The document will never be closed to prevent the doc.OpenElements from being empty.
func (doc *Document) TryClose(last IElement) bool {
	return false
}

func (doc *Document) GetLastOpen() IElement {
	return doc.OpenElements[len(doc.OpenElements)-1]
}

func (doc *Document) RemoveLastOpen() {
	doc.OpenElements = doc.OpenElements[0 : len(doc.OpenElements)-1]
}

func (doc *Document) AddElement(elem IElement) {
	lastOpen := doc.GetLastOpen()
	// Try to append homogeneous element.
	if lastOpen.TryAppend(elem) {
		return
	}
	// Try to close the open blocks.
	for lastOpen.TryClose(elem) {
		doc.OpenElements = doc.OpenElements[0 : len(doc.OpenElements)-1]
		lastOpen = doc.GetLastOpen()
	}
	// Add to last open block.
	lastOpen.GetBase().AddChild(elem)
	// Add to open block stack.
	if elem.GetBase().Open {
		doc.OpenElements = append(doc.OpenElements, elem)
	}
}
