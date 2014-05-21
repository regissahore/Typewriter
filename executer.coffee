class window.Executer
    constructor: (@canvas) ->
        @context = @canvas.getContext '2d'
        @width = @canvas.width
        @height = @canvas.height
        @x = @width * 0.5
        @y = @height * 0.5
        @angle = Math.PI * 0.5
        @background = [0, 0, 0]
        @pen = 
            colour: [255, 255, 255]
            width: 1
            down: true
        @applyBackground()
        @applyPen()
    toRgb: (data) =>
        return 'rgb(' + data[0] + ',' + data[1] + ',' + data[2] + ')'
    applyBackground: =>
        @context.beginPath
        @context.fillStyle = @toRgb @background
        @context.strokeStyle = @toRgb @background
        @context.fillRect 0, 0, @width, @height
        @context.endPath
    applyPen: =>
        @context.strokeStyle = @toRgb @pen.colour
        @context.strokeWidth = @pen.width
    execute: (instructions) =>
        for instruction in instructions
            switch instruction.keyword
                when 'FORWARD', 'FD'
                    if @pen.down
                        @context.moveTo @x, @y
                    length = parseFloat instruction.parameter[0]
                    @x += length * Math.cos @angle
                    @y -= length * Math.sin @angle
                    if @pen.down
                        @context.lineTo @x, @y
                        @context.stroke()
                when 'BACK', 'BK'
                    if @pen.down
                        @context.moveTo @x, @y
                    length = parseFloat instruction.parameter[0]
                    @x -= length * Math.cos @angle
                    @y += length * Math.sin @angle
                    if @pen.down
                        @context.lineTo @x, @y
                        @context.stroke()
                when 'LEFT', 'LT'
                    rotate = parseFloat instruction.parameter[0]
                    @angle += rotate * Math.PI / 180.0
                when 'RIGHT', 'RT'
                    rotate = parseFloat instruction.parameter[0]
                    @angle -= rotate * Math.PI / 180.0
                    