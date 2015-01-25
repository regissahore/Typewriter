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
		Open:     true,
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
	if last.GetBase().Function == ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION {
		lastDef := last.(*ElementLeafLinkReferenceDefination)
		if lastDef.Label == nil {
			if lastDef.Destination != nil {
				elem.Destination = lastDef.Destination
			}
			if lastDef.Title != nil {
				elem.Title = lastDef.Title
			}
			return true
		}
	}
	return false
}

func (elem *ElementLeafLinkReferenceDefination) TryClose(last IElement) bool {
	return true
}

// Link reference: <Link label>: <Link destination> <Optional link title>
// There is at most one line break between label and destination.
// There is at most one line break between destination and title.
func parseLeafLinkReferenceDefination(doc *Document, line *UTF8String, offset int) bool {
	length := line.Length()
	isParseLabel := true
	isParseDestination := true
	isParseTitle := true
	index := SkipLeadingSpace(line, offset)
	if index == length || line.RuneAt(index) != '[' {
		if doc.GetLastOpen().GetBase().Function == ELEMENT_TYPE_LEAF_LINK_REFERENCE_DEFINATION {
			lastDef := doc.GetLastOpen().(*ElementLeafLinkReferenceDefination)
			if lastDef.Destination == nil {
				isParseLabel = false
			} else if lastDef.Title == nil {
				isParseLabel = false
				isParseDestination = false
			}
		}
	}
	var state int
	var label *UTF8String = nil
	if isParseLabel {
		state, label, index = parseLinkLabel(line, index)
		if state != STATE_ACCEPT || line.RuneAt(index) != ':' {
			return false
		}
		index = SkipLeadingSpace(line, index+1)
		if index == length {
			isParseDestination = false
			isParseTitle = false
		}
	}
	var destination *UTF8String = nil
	if isParseDestination {
		state, destination, index = parseLinkDestination(line, index)
		if state != STATE_ACCEPT {
			return false
		}
		index = SkipLeadingSpace(line, index)
		if index == length {
			isParseTitle = false
		}
	}
	var title *UTF8String = nil
	if isParseTitle {
		state, title, index = parseLinkTitle(line, index)
		if state != STATE_ACCEPT {
			return false
		}
		index = SkipLeadingSpace(line, index)
		if index != length {
			return false
		}
	}
	elem := NewElementLeafLinkReferenceDefination(label, destination, title)
	doc.AddElement(elem)
	if isParseLabel {
		doc.AddLinkReferenceDefinations(elem)
	}
	return true
}
