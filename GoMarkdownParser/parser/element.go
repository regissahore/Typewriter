package parser

// Types of the elements.
const (
	ELEMENT_TYPE_DOCUMENT  = iota
	ELEMENT_TYPE_LEAF      = iota
	ELEMENT_TYPE_CONTAINER = iota
	ELEMENT_TYPE_INLINE    = iota
	ELEMENT_TYPE_INVALID   = iota

	ELEMENT_TYPE_LEAF_HORIZONTAL_RULE           = iota
	ELEMENT_TYPE_LEAF_ATX_HEADER                = iota
	ELEMENT_TYPE_LEAF_SETEXT_HEADER             = iota
	ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK       = iota
	ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK         = iota
	ELEMENT_TYPE_LEAF_HTML_BLOCK                = iota
	ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION = iota
	ELEMENT_TYPE_LEAF_PARAGRAPH                 = iota
	ELEMENT_TYPE_LEAF_BLANK_LINE                = iota

	ELEMENT_TYPE_CONTAINER_BLOCK_QUOTE       = iota
	ELEMENT_TYPE_CONTAINER_LIST_ITEM_BULLET  = iota
	ELEMENT_TYPE_CONTAINER_LIST_ITEM_ORDERED = iota
	ELEMENT_TYPE_CONTAINER_LIST_BULLET       = iota
	ELEMENT_TYPE_CONTAINER_LIST_ORDERED      = iota

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
	Function int  // Specific type of the element.
	Open     bool // Used for parsing the structure of the document.
	Children []IElement
	Inlines  []*UTF8String // Inline texts to be parsed.
}

func (elem *Element) AddChild(child IElement) {
	if elem.Children == nil {
		elem.Children = make([]IElement, 0)
	}
	elem.Children = append(elem.Children, child)
}

type IElement interface {
	GetBase() *Element
	Translate(output chan<- string) // Translate to HTML.
	TryAppend(last IElement) bool   // Used for parsing the structure of the document.
	TryClose(last IElement) bool    // Used for parsing the structure of the document.
}

func (elem *Element) TranslateAllChildren(output chan<- string) {
	if elem.Children != nil {
		for _, child := range elem.Children {
			child.Translate(output)
		}
	}
}

func (elem *Element) Structure() int {
	switch elem.Function {
	case ELEMENT_TYPE_DOCUMENT:
		return ELEMENT_TYPE_DOCUMENT

	case ELEMENT_TYPE_LEAF_HORIZONTAL_RULE:
		fallthrough
	case ELEMENT_TYPE_LEAF_ATX_HEADER:
		fallthrough
	case ELEMENT_TYPE_LEAF_SETEXT_HEADER:
		fallthrough
	case ELEMENT_TYPE_LEAF_INDENTED_CODE_BLOCK:
		fallthrough
	case ELEMENT_TYPE_LEAF_FENCED_CODE_BLOCK:
		fallthrough
	case ELEMENT_TYPE_LEAF_HTML_BLOCK:
		fallthrough
	case ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION:
		fallthrough
	case ELEMENT_TYPE_LEAF_PARAGRAPH:
		fallthrough
	case ELEMENT_TYPE_LEAF_BLANK_LINE:
		return ELEMENT_TYPE_LEAF

	case ELEMENT_TYPE_CONTAINER_BLOCK_QUOTE:
		fallthrough
	case ELEMENT_TYPE_CONTAINER_LIST_ITEM_BULLET:
		fallthrough
	case ELEMENT_TYPE_CONTAINER_LIST_ITEM_ORDERED:
		fallthrough
	case ELEMENT_TYPE_CONTAINER_LIST_BULLET:
		fallthrough
	case ELEMENT_TYPE_CONTAINER_LIST_ORDERED:
		return ELEMENT_TYPE_CONTAINER

	case ELEMENT_TYPE_INLINE_BACKSLASH_ESCAPE:
		fallthrough
	case ELEMENT_TYPE_INLINE_ENTITY:
		fallthrough
	case ELEMENT_TYPE_INLINE_CODE_SPAN:
		fallthrough
	case ELEMENT_TYPE_INLINE_EMPHASIS:
		fallthrough
	case ELEMENT_TYPE_INLINE_STRONG_EMPHASIS:
		fallthrough
	case ELEMENT_TYPE_INLINE_LINK:
		fallthrough
	case ELEMENT_TYPE_INLINE_IMAGE:
		fallthrough
	case ELEMENT_TYPE_INLINE_AUTOLINK:
		fallthrough
	case ELEMENT_TYPE_INLINE_RAW_HTML:
		fallthrough
	case ELEMENT_TYPE_INLINE_HARD_LINE_BREAK:
		fallthrough
	case ELEMENT_TYPE_INLINE_SOFT_LINE_BREAK:
		fallthrough
	case ELEMENT_TYPE_INLINE_TEXTUAL_CONTENT:
		return ELEMENT_TYPE_INLINE
	}
	return ELEMENT_TYPE_INVALID
}
