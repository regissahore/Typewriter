package parser

type Document struct {
	Base           *Element
	OpenElements   []IElement
	LastLeaf       IElement
	LastLeafParent IElement
	LinkRefDefs    []*ElementLeafLinkReferenceDefination
	LinkRefMap     map[*UTF8String]*ElementLeafLinkReferenceDefination
	LastIndent     int
	LastContainers []IElement
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
	doc.LastLeaf = nil
	doc.LastLeafParent = nil
	doc.LinkRefDefs = make([]*ElementLeafLinkReferenceDefination, 0)
	doc.LinkRefMap = make(map[*UTF8String]*ElementLeafLinkReferenceDefination)
	doc.LastIndent = 0
	doc.LastContainers = make([]IElement, 0)
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

/**
 * Only used for discarding:
 * 1. the paragraph followed by setext header.
 * 2. the link label of link reference defination with no link destination.
 */
func (doc *Document) RemoveLastLeaf() {
	elem := doc.LastLeafParent.GetBase()
	elem.Children = elem.Children[:len(elem.Children)-1]
	if doc.LastLeaf.GetBase().Open {
		doc.RemoveLastOpen()
	}
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
	if elem.GetBase().Structure() == ELEMENT_TYPE_LEAF {
		doc.LastLeaf = elem
		doc.LastLeafParent = lastOpen
	}
	// Add to open block stack.
	if elem.GetBase().Open {
		doc.OpenElements = append(doc.OpenElements, elem)
	}
}

func (doc *Document) AddLinkReferenceDefinations(elem *ElementLeafLinkReferenceDefination) {
	doc.LinkRefDefs = append(doc.LinkRefDefs, elem)
	refDef, exist := doc.LinkRefMap[elem.Label]
	if exist && refDef.Destination == nil {
		exist = false
	}
	if !exist {
		doc.LinkRefMap[elem.Label] = elem
	}
}
