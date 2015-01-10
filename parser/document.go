package parser

type Document struct {
	element   *Element
	openStack []IElement
}

func NewDocument() *Document {
	doc := &Document{}
	doc.element = &Element{
		structureType: ELEMENT_TYPE_ROOT,
		functionType:  ELEMENT_TYPE_ROOT,
		isOpen:        true,
		parent:        nil,
		children:      make([]IElement, 0),
	}
	doc.openStack = make([]IElement, 0)
	doc.openStack = append(doc.openStack, doc)
	return doc
}

func (doc *Document) GetElement() *Element {
	return doc.element
}

func (doc *Document) OpenString() string {
	return ""
}

func (doc *Document) CloseString() string {
	return ""
}

func (doc *Document) GetLastOpen() IElement {
	return doc.openStack[len(doc.openStack)-1]
}

func (doc *Document) AddElement(elem IElement) {
	lastOpen := doc.GetLastOpen()
	elem.GetElement().parent = lastOpen
	lastOpen.GetElement().children = append(lastOpen.GetElement().children, elem)
	if elem.GetElement().isOpen {
		doc.openStack = append(doc.openStack, elem)
	}
}
