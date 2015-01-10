package parser

const (
	ELEMENT_TYPE_ROOT      = iota
	ELEMENT_TYPE_LEAF      = iota
	ELEMENT_TYPE_CONTAINER = iota
	ELEMENT_TYPE_INLINE    = iota

	ELEMENT_TYPE_LEAF_HORIZONTAL_RULE           = iota
	ELEMENT_TYPE_LEAF_ATX_HEADER                = iota
	ELEMENT_TYPE_LEAF_SETEXT_HEADER             = iota
	ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK       = iota
	ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK         = iota
	ELEMENT_TYPE_LEAF_HTML_BLOCK                = iota
	ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION = iota
	ELEMENT_TYPE_LEAF_PARAGRAPH                 = iota
	ELEMENT_TYPE_LEAF_BLANK_LINE                = iota

	ELEMENT_TYPE_CONTAINER_BLOCK_QUOTE = iota
	ELEMENT_TYPE_CONTAINER_LIST_ITEM   = iota
	ELEMENT_TYPE_CONTAINER_LIST        = iota

	ELEMENT_TYPE_INLINE_BACKSLASH_ESCAPE = iota
	ELEMENT_TYPE_INLINE_ENTITY           = iota
	ELEMENT_TYPE_INLINE_CODE_SPAN        = iota
	ELEMENT_TYPE_INLINE_EMPHASIS         = iota
	ELEMENT_TYPE_INLINE_STRONG_EMPHASIS  = iota
	ELEMENT_TYPE_INLINE_LINK             = iota
	ELEMENT_TYPE_INLINE_IMAGE            = iota
	ELEMENT_TYPE_INLINE_AUTOLINK         = iota
	ELEMENT_TYPE_INLINE_RAW_HTML         = iota
	ELEMENT_TYPE_INLINE_HARD_LINE_BREAK  = iota
	ELEMENT_TYPE_INLINE_SOFT_LINE_BREAK  = iota
	ELEMENT_TYPE_INLINE_TEXTUAL_CONTENT  = iota
)

type Element struct {
	structureType int
	functionType  int
	isOpen        bool
	parent        IElement
	children      []IElement
	text          *UTF8String
}

func (elem *Element) Close() {
	elem.isOpen = false
}

type IElement interface {
	GetElement() *Element
	OpenString() string
	CloseString() string
	TryClose(last IElement) bool
}
