package parser

const (
	STATE_START             = iota
	STATE_LABEL             = iota
	STATE_DESTINATION       = iota
	STATE_DESTINATION_ANGLE = iota
	STATE_TITLE             = iota
	STATE_ESCAPE            = iota
	STATE_ESCAPE_ANGLE      = iota
	STATE_ERROR             = iota
	STATE_ACCEPT            = iota
)

// Link label starts with '[' and ends with ']'.
// There should be no unescaped '[' and ']' appeared in link label.
// The maximum size of the label is 999 characters.
// The consecutive internal whitespaces will be collapsed to a single space.
// The label will be transformed to lower-case.
/* FSM:
             +------+
             |Escape|
             +^-----+
             \|   |Any
+-----+  [  +-----v-+     +------+
|Start|---->| Label |---->|Accept|
+-----+     +-------+  ]  +------+
               [|
             +--v--+
             |Error|
             +-----+
*/
func parseLinkLabel(source *UTF8String, offset int) (state int, label *UTF8String, index int) {
	index = offset
	length := source.Length()
	state = STATE_START
	label = NewUTF8StringEmpty()
	for state != STATE_ERROR && state != STATE_ACCEPT && index < length {
		r := source.RuneAt(index)
		index++
		switch state {
		case STATE_START:
			if r == '[' {
				state = STATE_LABEL
			} else {
				state = STATE_ERROR
			}
		case STATE_LABEL:
			if r == '\\' {
				state = STATE_ESCAPE
			} else if r == '[' {
				state = STATE_ERROR
			} else if r == ']' {
				state = STATE_ACCEPT
			} else {
				label.AppendRune(r)
			}
		case STATE_ESCAPE:
			label.AppendRune(r)
			state = STATE_LABEL
		}
		if label.Length() > 999 {
			state = STATE_ERROR
		}
	}
	if state == STATE_ACCEPT {
		label = label.Collapse().Lower()
	}
	return
}

// Link destination
// 1. Opens with '<' and ends with '>', contains no line break or unescaped '<' or '>';
// 2. Nonempty string with no space and contains '(' and ')' only if they are escaped or balanced.
/* FSM:
                   +------+
                   |Escape|
                   |Angle |
                   +-^----+
                    \|  |Any
          <      +------v----+       >
   +------------>|Destination|---------------+
   |             |   Angle   |               |
   |             +-----+-----+               |
   |                  <|                     v
+-----+     )       +--v--+              +------+
|Start|------------>|Error|              |Accept|
+-----+             +-----+              +------+
   |                                         ^
   |             +-----------+               |
   +------------>|Destination|---------------+
      Other      +-------^---+     Space
                     \|  |Any
                    +-v----+
                    |Escape|
                    +------+
*/
func parseLinkDestination(source *UTF8String, offset int) (state int, destination *UTF8String, index int) {
	index = offset
	length := source.Length()
	state = STATE_START
	destination = NewUTF8StringEmpty()
	bracketStack := 0
	for state != STATE_ERROR && state != STATE_ACCEPT && index < length {
		r := source.RuneAt(index)
		index++
		switch state {
		case STATE_START:
			if r == '<' {
				state = STATE_DESTINATION_ANGLE
			} else if r == ')' {
				state = STATE_ERROR
			} else {
				state = STATE_DESTINATION
				destination.AppendRune(r)
				if r == '(' {
					bracketStack++
				}
			}
		case STATE_DESTINATION_ANGLE:
			if r == '\\' {
				state = STATE_ESCAPE_ANGLE
			} else if r == '<' {
				state = STATE_ERROR
			} else if r == '>' {
				state = STATE_ACCEPT
			} else {
				destination.AppendRune(r)
			}
		case STATE_ESCAPE_ANGLE:
			destination.AppendRune(r)
			state = STATE_DESTINATION_ANGLE
		case STATE_DESTINATION:
			if r == '\\' {
				state = STATE_ESCAPE
			} else if IsWhitespace(r) {
				if bracketStack == 0 {
					state = STATE_ACCEPT
				} else {
					state = STATE_ERROR
				}
			} else {
				destination.AppendRune(r)
				if r == '(' {
					bracketStack++
				} else if r == ')' {
					bracketStack--
					if bracketStack < 0 {
						state = STATE_ERROR
					}
				}
			}
		case STATE_ESCAPE:
			destination.AppendRune(r)
			state = STATE_DESTINATION
		}
	}
	return
}

// Link title
// 1. Opens with '"' and ends with '"'.
// 2. Opens with '\'' and ends with '\''.
// 3. Opens with '(' and ends with ')'.
/* FSM:
                +------+
                |Escape|
                +------+
                  ^ |Any
                 \| v
+-----+  " ' (  +-----+         +------+
|Start|-------->|Title|-------->|Accept|
+-----+         +-----+  " ' )  +------+
*/
func parseLinkTitle(source *UTF8String, offset int) (state int, title *UTF8String, index int) {
	index = offset
	length := source.Length()
	state = STATE_START
	title = NewUTF8StringEmpty()
	var closeRune rune
	for state != STATE_ERROR && state != STATE_ACCEPT && index < length {
		r := source.RuneAt(index)
		index++
		switch state {
		case STATE_START:
			if r == '"' {
				closeRune = '"'
				state = STATE_TITLE
			} else if r == '\'' {
				closeRune = '\''
				state = STATE_TITLE
			} else if r == '(' {
				closeRune = ')'
				state = STATE_TITLE
			} else {
				state = STATE_ERROR
			}
		case STATE_TITLE:
			if r == '\\' {
				state = STATE_ESCAPE
			} else if r == closeRune {
				state = STATE_ACCEPT
			} else {
				title.AppendRune(r)
			}
		case STATE_ESCAPE:
			title.AppendRune(r)
			state = STATE_TITLE
		}
	}
	return
}
