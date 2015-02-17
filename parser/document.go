package parser

type Document struct {
	Base              *Element
	OpenElements      []IElement
	LastLeaf          IElement
	LastLeafParent    IElement
	LinkRefDefs       []*ElementLeafLinkReferenceDefination
	LinkRefMap        map[*UTF8String]*ElementLeafLinkReferenceDefination
	LastIndent        int
	LastContainers    []IElement
	CurrentContainers []IElement
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
	doc.CurrentContainers = make([]IElement, 0)
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

/**
 * Only used for discarding:
 * 1. the paragraph followed by setext header.
 * 2. the link label of link reference defination with no link destination.
 */
func (doc *Document) RemoveLastLeaf() {
	elem := doc.LastLeafParent.GetBase()
	for i := 0; i < len(elem.Children); i++ {
		if elem.Children[i] == doc.LastLeaf {
			elem.Children = append(elem.Children[:i], elem.Children[i+1:]...)
			break
		}
	}
	if doc.LastLeaf.GetBase().Open {
		for i := 0; i < len(doc.OpenElements); i++ {
			if doc.OpenElements[i] == doc.LastLeaf {
				doc.OpenElements = append(doc.OpenElements[:i], doc.OpenElements[i+1:]...)
				break
			}
		}
	}
}

func (doc *Document) GetLastLeafFunction() int {
	if doc.LastLeaf == nil || !doc.LastLeaf.GetBase().Open {
		return ELEMENT_TYPE_INVALID
	}
	return doc.LastLeaf.GetBase().Function
}

func (doc *Document) CloseTo(elem IElement) {
	for {
		lastOpen := doc.OpenElements[len(doc.OpenElements)-1]
		doc.OpenElements = doc.OpenElements[0 : len(doc.OpenElements)-1]
		if lastOpen == elem {
			break
		}
	}
}

func (doc *Document) AddElement(elem IElement) {
	lastOpen := doc.OpenElements[len(doc.OpenElements)-1]
	// Try to append homogeneous element.
	if lastOpen.TryAppend(elem) {
		return
	}
	// Try to close the open blocks.
	for lastOpen.TryClose(elem) {
		doc.OpenElements = doc.OpenElements[0 : len(doc.OpenElements)-1]
		lastOpen = doc.OpenElements[len(doc.OpenElements)-1]
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

func (doc *Document) AddCurrentContainer(elem IElement) {
	doc.CurrentContainers = append(doc.CurrentContainers, elem)
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
