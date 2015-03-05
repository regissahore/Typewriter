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
	return false
}

func parseContainerBlockQuote(doc *Document, line *UTF8String, offset int) (bool, int) {
	length := line.Length()
	start := SkipLeadingSpace(line, offset)
	if start == length || start-offset >= 4 {
		return false, 0
	}
	if line.RuneAt(start) == '>' {
		doc.AddCurrentContainer(NewElementContainerBlockQuote(start))
		if line.RuneAt(start+1) == '\n' {
			return true, start - offset + 1
		}
		if IsWhitespace(line.RuneAt(start + 1)) {
			return true, start - offset + 2
		}
		return true, start - offset + 1
	}
	return false, 0
}
