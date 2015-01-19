package parser

type ElementLeafLinkReferenceDefination struct {
	Base        *Element
	Destination *UTF8String
	Title       *UTF8String
}

func NewElementLeafLinkReferenceDefination(text *UTF8String, level int) *ElementLeafLinkReferenceDefination {
	elem := &ElementLeafLinkReferenceDefination{}
	elem.Base = &Element{
		Structure: ELEMENT_TYPE_LEAF,
		Function:  ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION,
		Open:      false,
		Children:  make([]IElement, 0),
		Inlines:   []*UTF8String{text},
	}
	return elem
}

func (elem *ElementLeafLinkReferenceDefination) GetBase() *Element {
	return elem.Base
}

func (elem *ElementLeafLinkReferenceDefination) Translate(output chan<- string) {
}

func (elem *ElementLeafLinkReferenceDefination) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementLeafLinkReferenceDefination) TryClose(last IElement) bool {
	return true
}

func ParseLinkReferenceDefination(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	return true, length - offset
}
