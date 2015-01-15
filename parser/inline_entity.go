package parser

import (
	"unicode/utf8"
)

type ElementInlineEntity struct {
	Base       *Element
	Translated *UTF8String
}

func NewElementInlineEntity(translated *UTF8String) *ElementInlineEntity {
	elem := &ElementInlineEntity{}
	elem.Base = &Element{
		Structure: ELEMENT_TYPE_INLINE,
		Function:  ELEMENT_TYPE_INLINE_ENTITY,
		Open:      false,
		Children:  make([]IElement, 0),
		Inlines:   nil,
	}
	elem.Translated = translated
	return elem
}

func (elem *ElementInlineEntity) GetBase() *Element {
	return elem.Base
}

func (elem *ElementInlineEntity) Translate(output chan<- string) {
	output <- elem.Translated.TranslateHTML()
}

func (elem *ElementInlineEntity) TryAppend(last IElement) bool {
	return false
}

func (elem *ElementInlineEntity) TryClose(last IElement) bool {
	return true
}

func ParseInlineEntity(doc *Document, line *UTF8String, offset int) (bool, int) {
	if line.RuneAt(offset) != '&' {
		return false, 0
	}
	length := line.Length()
	if offset+2 >= length {
		return false, 0
	}
	if line.RuneAt(offset+1) == '#' {
		if line.RuneAt(offset+2) == 'x' || line.RuneAt(offset+2) == 'X' {
			// Try to find hexadecimal entity.
			dexLength := 0
			semicolon := false
			for i := offset + 3; i < length; i++ {
				r := line.RuneAt(i)
				if IsDex(r) {
					dexLength++
				} else if r == ';' {
					semicolon = true
					break
				} else {
					break
				}
			}
			if semicolon && 1 <= dexLength && dexLength <= 8 {
				hex := 0
				for i := offset + 3; i < offset+3+dexLength; i++ {
					hex = (hex << 4) | Dex2Int(line.RuneAt(i))
				}
				transRune := rune(hex)
				trans := string(transRune)
				if !utf8.ValidRune(transRune) {
					trans = string("\uFFFD")
				}
				doc.AddElement(NewElementInlineEntity(NewUTF8String(trans)))
				return true, dexLength + 4
			}
		} else {
			// Try to find decimal entity.
			decLength := 0
			semicolon := false
			for i := offset + 2; i < length; i++ {
				r := line.RuneAt(i)
				if IsDigit(r) {
					decLength++
				} else if r == ';' {
					semicolon = true
					break
				} else {
					break
				}
			}
			if semicolon && 1 <= decLength && decLength <= 8 {
				dec := 0
				for i := offset + 2; i < offset+2+decLength; i++ {
					dec = dec*10 + Dec2Int(line.RuneAt(i))
				}
				transRune := rune(dec)
				trans := string(transRune)
				if !utf8.ValidRune(transRune) {
					trans = string("\uFFFD")
				}
				doc.AddElement(NewElementInlineEntity(NewUTF8String(trans)))
				return true, decLength + 3
			}
		}
	} else {
		// Try to find named entity.
		nameLength := 0
		semicolon := false
		for i := offset + 1; i < length; i++ {
			r := line.RuneAt(i)
			if IsAlphaOrDigit(r) {
				nameLength++
			} else if r == ';' {
				semicolon = true
				break
			} else {
				break
			}
		}
		if semicolon {
			name := line.Substring(offset+1, nameLength)
			value, exist := GetNamedEntityMap()[name.String()]
			if exist {
				doc.AddElement(NewElementInlineEntity(value))
				return true, nameLength + 2
			}
		}
	}
	return false, 0
}
