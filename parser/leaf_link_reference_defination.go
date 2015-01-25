package parser

type ElementLeafLinkReferenceDefination struct {
	Base        *Element
	Label       *UTF8String
	Destination *UTF8String
	Title       *UTF8String
}

func NewElementLeafLinkReferenceDefination(label, destination, title *UTF8String) *ElementLeafLinkReferenceDefination {
	elem := &ElementLeafLinkReferenceDefination{}
	elem.Base = &Element{
		Function: ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION,
		Open:     false,
		Children: nil,
		Inlines:  nil,
	}
	elem.Label = label
	elem.Destination = destination
	elem.Title = title
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

func skipSpacesWithAtMostOneLineBreak(source *UTF8String, index int) (bool, int) {
	lineBreakNum := 0
	length := source.Length()
	for ; index < length; index++ {
		r := source.RuneAt(index)
		if r == '\n' {
			lineBreakNum++
			if lineBreakNum > 1 {
				return false, 0
			}
		} else if !IsWhitespace(r) {
			break
		}
	}
	return true, index
}

// Link reference: <Link label>: <Link destination> <Optional link title>
// There is at most one line break between label and destination.
// There is at most one line break between destination and title.
func parseLeafLinkReferenceDefination(doc *Document, source *UTF8String, offset, last int) (bool, int) {
	index := SkipLeadingSpace(source, offset)
	var state int
	var label *UTF8String
	state, label, index = parseLinkLabel(source, index)
	if state != STATE_ACCEPT || source.RuneAt(index) != ':' {
		return false, 0
	}
	var success bool
	index++
	success, index = skipSpacesWithAtMostOneLineBreak(source, index)
	if !success {
		return false, 0
	}
	var destination *UTF8String
	state, destination, index = parseLinkDestination(source, index)
	destinationEnd := index
	if state != STATE_ACCEPT {
		return false, 0
	}
	success, index = skipSpacesWithAtMostOneLineBreak(source, index)
	if !success {
		return false, 0
	}
	var title *UTF8String
	var optIndex int
	state, title, optIndex = parseLinkTitle(source, index)
	if state == STATE_ACCEPT {
		index = optIndex
	} else {
		index = destinationEnd
		title = nil
	}
	last = FindLineEnd(source, index)
	for ; index < last; index++ {
		r := source.RuneAt(index)
		if !IsWhitespace(r) {
			return false, 0
		}
	}
	doc.AddLinkReferenceDefinations(NewElementLeafLinkReferenceDefination(label, destination, title))
	return true, last - offset
}
