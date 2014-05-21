class Instruction
    constructor: ->
        @keyword = ''
        @parameter = []
        
class window.Parser
    constructor: -> 
        @source = ''
        @instructions = []
    read: (terms, index) =>
        instruction = new Instruction
        switch terms[index].toUpperCase()
            when 'FORWARD', 'FD', 'BACK', 'BK', 'LEFT', 'LT', 'RIGHT', 'RT'
                instruction.keyword = terms[index].toUpperCase()
                instruction.parameter.push terms[index + 1]
                @instructions.push instruction
                index += 2
            else
                return
        if index < terms.length
            @read terms, index
    parse: (@source) =>
        @instructions = []
        terms = @source.split /[\s\n\t]+/
        @read terms, 0
        @instructions
        
        