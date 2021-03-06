package parser

import (
	"unicode"
)

type UTF8String struct {
	Text []rune
}

func NewUTF8String(str string) *UTF8String {
	return &UTF8String{[]rune(str)}
}

func NewUTF8StringExpanded(str string) *UTF8String {
	raw := NewUTF8String(str)
	expanded := NewUTF8StringEmpty()
	pos := 0
	length := raw.Length()
	for i := 0; i < length; i++ {
		r := raw.RuneAt(i)
		if r == '\t' {
			spaceNum := 4 - pos%4
			for j := 0; j < spaceNum; j++ {
				expanded.AppendRune(' ')
			}
			pos += spaceNum
		} else {
			expanded.AppendRune(r)
			pos++
		}
	}
	return expanded
}

func NewUTF8StringEmpty() *UTF8String {
	return &UTF8String{make([]rune, 0)}
}

func NewUTF8StringWithRunes(text []rune) *UTF8String {
	return &UTF8String{text}
}

func (str *UTF8String) Length() int {
	return len(str.Text)
}

func (str *UTF8String) String() string {
	return string(str.Text)
}

func (str *UTF8String) Substring(start, length int) *UTF8String {
	if start < 0 || start >= str.Length() {
		return &UTF8String{make([]rune, 0)}
	}
	if start+length > str.Length() {
		length = str.Length() - start
	}
	return &UTF8String{str.Text[start:(start + length)]}
}

func (str *UTF8String) Left(length int) *UTF8String {
	return &UTF8String{str.Text[:length]}
}

func (str *UTF8String) Right(start int) *UTF8String {
	return &UTF8String{str.Text[start:]}
}

func (str *UTF8String) Append(tail *UTF8String) *UTF8String {
	return &UTF8String{append(str.Text, tail.Text...)}
}

func (str *UTF8String) AppendRune(r rune) {
	str.Text = append(str.Text, r)
}

func (str *UTF8String) LeadingSpaceNum() int {
	length := str.Length()
	for i := 0; i < length; i++ {
		if !IsWhitespace(str.RuneAt(i)) {
			return i
		}
	}
	return length
}

func (str *UTF8String) Trim() *UTF8String {
	length := str.Length()
	begin := str.LeadingSpaceNum()
	if begin == length {
		return NewUTF8String("")
	}
	end := 0
	for i := length - 1; i >= begin; i-- {
		if !IsWhitespace(str.RuneAt(i)) {
			end = i + 1
			break
		}
	}
	return str.Substring(begin, end-begin)
}

func (str *UTF8String) Collapse() *UTF8String {
	collapsed := NewUTF8StringEmpty()
	length := str.Length()
	lastIsSpace := false
	for i := 0; i < length; i++ {
		r := str.RuneAt(i)
		if IsWhitespace(r) {
			if !lastIsSpace {
				collapsed.AppendRune(' ')
				lastIsSpace = true
			}
		} else {
			collapsed.AppendRune(r)
			lastIsSpace = false
		}
	}
	return collapsed
}

func (str *UTF8String) Lower() *UTF8String {
	lower := NewUTF8StringEmpty()
	length := str.Length()
	for i := 0; i < length; i++ {
		lower.AppendRune(unicode.ToLower(str.RuneAt(i)))
	}
	return lower
}

func (str *UTF8String) Upper() *UTF8String {
	upper := NewUTF8StringEmpty()
	length := str.Length()
	for i := 0; i < length; i++ {
		upper.AppendRune(unicode.ToUpper(str.RuneAt(i)))
	}
	return upper
}

func (str *UTF8String) First() rune {
	if str.Length() == 0 {
		return 0
	}
	return str.Text[0]
}

func (str *UTF8String) Last() rune {
	if str.Length() == 0 {
		return 0
	}
	return str.Text[str.Length()-1]
}

func (str *UTF8String) RuneAt(index int) rune {
	return str.Text[index]
}

func IsWhitespace(r rune) bool {
	return unicode.IsSpace(r)
}

func IsAlpha(r rune) bool {
	return ('a' <= r && r <= 'z') || ('A' <= r && r <= 'Z')
}

func IsDigit(r rune) bool {
	return '0' <= r && r <= '9'
}

func IsDex(r rune) bool {
	return IsDigit(r) || ('a' <= r && r <= 'f') || ('A' <= r && r <= 'F')
}

func Dex2Int(r rune) int {
	if '0' <= r && r <= '9' {
		return int(r - '0')
	}
	if 'a' <= r && r <= 'f' {
		return int(r - 'a' + 10)
	}
	return int(r - 'A' + 10)
}

func Dec2Int(r rune) int {
	return int(r - '0')
}

func IsPunctuation(r rune) bool {
	switch r {
	case '!':
		fallthrough
	case '"':
		fallthrough
	case '#':
		fallthrough
	case '$':
		fallthrough
	case '%':
		fallthrough
	case '&':
		fallthrough
	case '\'':
		fallthrough
	case '(':
		fallthrough
	case ')':
		fallthrough
	case '*':
		fallthrough
	case '+':
		fallthrough
	case ',':
		fallthrough
	case '-':
		fallthrough
	case '.':
		fallthrough
	case '/':
		fallthrough
	case ':':
		fallthrough
	case ';':
		fallthrough
	case '<':
		fallthrough
	case '=':
		fallthrough
	case '>':
		fallthrough
	case '?':
		fallthrough
	case '@':
		fallthrough
	case '[':
		fallthrough
	case '\\':
		fallthrough
	case ']':
		fallthrough
	case '^':
		fallthrough
	case '_':
		fallthrough
	case '`':
		fallthrough
	case '{':
		fallthrough
	case '|':
		fallthrough
	case '}':
		fallthrough
	case '~':
		return true
	}
	return false
}

func IsAlphaOrDigit(r rune) bool {
	return IsAlpha(r) || IsDigit(r)
}

func (str *UTF8String) TranslateHTML() string {
	html := ""
	length := str.Length()
	for i := 0; i < length; i++ {
		r := str.RuneAt(i)
		switch r {
		case '"':
			html += "&quot;"
		case '&':
			html += "&amp;"
		case '<':
			html += "&lt;"
		case '>':
			html += "&gt;"
		default:
			html += string(r)
		}
	}
	return html
}

func SkipLeadingSpace(line *UTF8String, offset int) int {
	length := line.Length()
	for i := offset; i < length; i++ {
		r := line.RuneAt(i)
		if !IsWhitespace(r) {
			return i
		}
	}
	return length
}
