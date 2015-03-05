package parser

type ElementInlineTextualContent struct {
	Base *Element
}

func NewElementInlineTextualContent(text *UTF8String) *ElementInlineTextualContent {
	elem := &ElementInlineTextualContent{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_INLINE_TEXTUAL_CONTENT,
		Open:     true,
		Children: nil,
		Inlines:  []*UTF8String{text},
	}
	return elem
}

func (elem *ElementInlineTextualContent) GetBase() *Element {
	return elem.Base
}

func (elem *ElementInlineTextualContent) Translate(output chan<- string) {
	if len(elem.Base.Children) == 0 {
		output <- elem.Base.Inlines[0].TranslateHTML()
	} else {
		elem.Base.TranslateAllChildren(output)
	}
}

func (elem *ElementInlineTextualContent) TryAppend(last IElement) bool {
	if last.GetBase().Function == ELEMENT_TYPE_INLINE_TEXTUAL_CONTENT {
		elem.Base.Inlines[0] = elem.Base.Inlines[0].Append(last.GetBase().Inlines[0])
		return true
	}
	return false
}

func (elem *ElementInlineTextualContent) TryClose(last IElement) bool {
	return true
}
