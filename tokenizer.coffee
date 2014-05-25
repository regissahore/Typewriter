class Tokenizer
    # Token contains number, text, identifier, variable, operator and delimiter.
    class Token
        constructor: (@token, @type) ->
    class Error
        constructor: (@line, @error) ->
    constructor: ->
        @clear()
    clear: =>
        @token_index = 0
        @tokens = []
        @errors = []
        @line = 1
    has_next_token: =>
        @index < @tokens.length
    get_next_token: =>
        @tokens[@index++]
    has_error: =>
        @errors.length > 0
    is_alphabet: (char) ->
        (char >= 'a' and char <= 'z') or (char >= 'A' and char <= 'Z')
    is_digit: (char) ->
        char >= '0' and char <= '9'
    is_identifier_character: (char) ->
        @is_alphabet(char) or @is_digit(char) or char == '_'
    is_delimiter_character: (char) ->
        char in [' ', '\t', '\n', '\r', '[', ']']
    is_operator_character: (char) ->
        char in ['+', '-', '*', '/', '%', '(', ')']
    parse: (code) =>
        index = 0
        while index < code.length
            switch code[index]
                when '[', ']'
                    @tokens.push new Token code[index++], 'delimiter'
                when '+', '-', '*', '/', '%', '(', ')'
                    @tokens.push new Token code[index++], 'operator'
                when "'"
                    token = code[index++]
                    closed = false
                    escape = false
                    while index < code.length
                        token += code[index]
                        if escape
                            escape = false
                        else
                            if code[index] == '\\'
                                escape = true
                            else if code[index] == "'"
                                closed = true
                        index += 1
                        if closed
                            break
                    if not closed
                        @errors.push new Error @line, 'String is not closed.'
                    @tokens.push new Token token, 'text'
                when '"', ':'
                    token = code[index++]
                    while index < code.length
                        if @is_identifier_character code[index]
                            token += code[index++]
                        else if @is_delimiter_character(code[index]) or @is_operator_character(code[index])
                            break
                        else
                            @errors.push new Error @line, 'The character is not valid in variable.'
                            break
                    @tokens.push new Token token, 'variable'
                when ' ', '\t', '\r'
                    index += 1
                when '\n'
                    index += 1
                    @line += 1
                else
                    if @is_digit code[index]
                        token = code[index++]
                        is_scientific = false
                        is_float = false
                        while index < code.length
                            if @is_digit code[index]
                                token += code[index]
                            else if code[index] in ['e', 'E']
                                if is_scientific
                                    @errors.push new Error @line 'The format of number is invalid.'
                                    break
                                is_scientific = true
                                token += code[index]
                            else if code[index] == '.'
                                if is_scientific
                                    @errors.push new Error @line 'The format of number is invalid.'
                                    break
                                if is_float
                                    @errors.push new Error @line 'The format of number is invalid.'
                                    break
                                is_float = true
                                token += code[index]
                            else if @is_delimiter_character(code[index]) or @is_operator_character(code[index])
                                break
                            else
                                @errors.push new Error @line, 'The character is not valid in number.'
                                break
                            index += 1
                        @tokens.push new Token token, 'number'
                    else if @is_identifier_character code[index]
                        token = code[index++]
                        while index < code.length
                            if @is_identifier_character code[index]
                                token += code[index]
                            else if @is_delimiter_character code[index]
                                break
                            else
                                @errors.push new Error @line, 'The character is not valid in identifier.'
                            index += 1
                        @tokens.push new Token token, 'identifier'
                    else
                        @errors.push new Error @line, 'Invalid character: ' + code[index]
                    