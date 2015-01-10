package parser

type UTF8String struct {
	Text []rune
}

func NewUTF8String(str string) *UTF8String {
	return &UTF8String{[]rune(str)}
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
	return r == 0x0020 || r == 0x0009 || r == 0x000D || r == 0x000A
}
