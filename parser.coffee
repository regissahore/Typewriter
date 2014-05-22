class Instruction
    constructor: ->
        @keyword = ''
        @parameter = []
        
class window.Parser
    constructor: -> 
        @source = ''
        @error = ''
        @index = 0
    read: (terms) =>
        instructions = []
        while @index < terms.length
            instruction = new Instruction
            switch terms[@index].toUpperCase()
                when 'FORWARD', 'FD', 'BACK', 'BK', 'LEFT', 'LT', 'RIGHT', 'RT'
                    instruction.keyword = terms[@index].toUpperCase()
                    instruction.parameter.push terms[@index + 1]
                    @index += 2
                when 'SHOWTURTLE', 'ST', 'HIDETURTLE', 'HT'
                    instruction.keyword = terms[@index].toUpperCase()
                    @index += 1
                when 'REPEAT'
                    instruction.keyword = terms[@index].toUpperCase()
                    instruction.parameter.push terms[@index + 1]
                    if terms[@index + 2] != '['
                        @error = 'No "[" after REPEAT.'
                        return
                    @index += 3
                    instruction.parameter.push @read terms
                when ']'
                    @index += 1
                    return instructions
                when 'HOME', 'CLEARSCREEN', 'CS', 'DRAW'
                    instruction.keyword = terms[@index].toUpperCase()
                    @index += 1
                when 'PENDOWN', 'PD', 'PENUP', 'PU'
                    instruction.keyword = terms[@index].toUpperCase()
                    @index += 1
                when 'SETHEADING', 'SETH', 'SETX', 'SETY'
                    instruction.keyword = terms[@index].toUpperCase()
                    instruction.parameter.push terms[@index + 1]
                    @index += 2
                when 'SETXY'
                    instruction.keyword = terms[@index].toUpperCase()
                    instruction.parameter.push terms[@index + 1]
                    instruction.parameter.push terms[@index + 2]
                    @index += 3
                when 'BACKGROUND', 'BG', 'PENCOLOR', 'PC'
                    instruction.keyword = terms[@index].toUpperCase()
                    instruction.parameter.push terms[@index + 1]
                    @index += 2
                else
                    @error = '"' + terms[@index] + '" is not defined.'
                    return
            instructions.push instruction
        instructions
    parse: (@source) =>
        raw_terms = @source.split /[\s\n\t]+/
        terms = []
        for raw_term in raw_terms
            if '[' in raw_term
                terms.push '['
                raw_term = raw_term.substr 1
            if ']' in raw_term
                raw_term = raw_term.substr 0, raw_term.length - 1
                if raw_term.length > 0
                    terms.push raw_term
                terms.push ']'
            else
                if raw_term.length > 0
                    terms.push raw_term
        @error = ''
        @index = 0
        @read terms
        
        