package parser

type ElementContainerBlockQuote struct {
	Base        *Element
	Indentation int
}

func NewElementContainerBlockQuote(indentation int) *ElementContainerBlockQuote {
	elem := &ElementContainerBlockQuote{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_CONTAINER_BLOCK_QUOTE,
		Open:     true,
		Children: nil,
		Inlines:  nil,
	}
	elem.Indentation = indentation
	return elem
}

func (elem *ElementContainerBlockQuote) GetBase() *Element {
	return elem.Base
}

func (elem *ElementContainerBlockQuote) Translate(output chan<- string) {
	output <- "<blockquote>"
	elem.Base.TranslateAllChildren(output)
	output <- "</blockquote>"
}

func (elem *ElementContainerBlockQuote) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementContainerBlockQuote) TryClose(last IElement) bool {
	return true
}

func parseContainerBlockQuote(doc *Document, line *UTF8String, offset, last int) (bool, int) {
	return false, 0
}
