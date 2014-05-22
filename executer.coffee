module = (x, mod) ->
    if x >= mod
        return x % mod
    if x < 0
        return (x % mod + mod) % mod
    return x

class ImageData
    constructor: (@width, @height) ->
        @clear()
    clear: =>
        size = @width * @height * 4
        @data = new Uint8ClampedArray size
    setPixel: (x, y, color) =>
        index = (y * @width + x) * 4
        for i in [0..(color.length - 1)]
            @data[index + i] = color[i]
        if color.length < 4
            @data[index + 3] = 255
    getPixel: (x, y) =>
        index = (y * @width + x) * 4
        color = []
        for i in [0..3]
            color.push @data[index + i]
        color
    draw: (context) =>
        imageData = context.getImageData 0, 0, @width, @height
        for i in [0..(@data.length - 1)] by 4
            if @data[i + 3] != 0
                for j in [0..2]
                    imageData.data[i + j] = @data[i + j]
        context.putImageData imageData, 0, 0
    drawLine: (x, y, dx, dy, color) =>
        ex = module x + dx, @width
        ey = module y + dy, @height
        ux = if dx > 0 then 1 else -1
        uy = if dy > 0 then 1 else -1
        dx = Math.abs dx
        dy = Math.abs dy
        eps = 0
        if dx > dy
            while x != ex
                @setPixel x, y, color
                eps += dy
                if (eps << 1) >= dx
                    y = module y + uy, @height
                    eps -= dx
                x = module x + ux, @width
        else
            while y != ey
                @setPixel x, y, color
                eps += dx
                if (eps << 1) >= dy
                    x = module x + ux, @width
                    eps -= dy
                y = module y + uy, @height
        

class window.Executer
    constructor: (@canvas) ->
        @context = @canvas.getContext '2d'
        @width = @canvas.width
        @height = @canvas.height
        @x = Math.round(@width * 0.5)
        @y = Math.round(@height * 0.5)
        @angle = 90
        @background = [0, 0, 0]
        @pen = 
            color: [255, 255, 255]
            down: true
            show: true
        @imageData = new ImageData @width, @height
        @turtle = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0], 
                   [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0], 
                   [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 
                   [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 
                   [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0], 
                   [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0], 
                   [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], 
                   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0]]
        @update()
    toRgb: (data) =>
        return 'rgb(' + data[0] + ',' + data[1] + ',' + data[2] + ')'
    drawTurtle: =>
        if @pen.show
            width = @turtle[0].length
            height = @turtle.length
            cx = width >> 1
            cy = height >> 1
            angle = @angle * Math.PI / 180.0
            for i in [0..(width - 1)]
                for j in [0..(height - 1)]
                    if @turtle[j][i] == 1
                        data = @context.createImageData(1, 1)
                        for k in [0..2]
                            data.data[k] = @pen.color[k]
                        sx = i - cx
                        sy = j - cy
                        rx = Math.round sx * Math.cos(angle) - sy * Math.sin(angle)
                        ry = Math.round sx * Math.sin(angle) + sy * Math.cos(angle)
                        tx = module @x + rx, @width
                        ty = module @y - ry, @height
                        @context.putImageData data, tx, ty
    update: =>
        @context.beginPath
        @context.fillStyle = @toRgb @background
        @context.strokeStyle = @toRgb @background
        @context.fillRect 0, 0, @width, @height
        @context.endPath
        @imageData.draw @context
        @drawTurtle()
    execute: (instructions, depth) =>
        for instruction in instructions
            switch instruction.keyword
                when 'FORWARD', 'FD'
                    length = parseInt instruction.parameter[0]
                    dx = Math.round length * Math.cos @angle * Math.PI / 180.0
                    dy = -Math.round length * Math.sin @angle * Math.PI / 180.0
                    if @pen.down
                        @imageData.drawLine @x, @y, dx, dy, @pen.color
                    @x = module @x + dx, @width
                    @y = module @y + dy, @height
                when 'BACK', 'BK'
                    length = parseInt instruction.parameter[0]
                    dx = -Math.round length * Math.cos @angle * Math.PI / 180.0
                    dy = Math.round length * Math.sin @angle * Math.PI / 180.0
                    if @pen.down
                        @imageData.drawLine @x, @y, dx, dy, @pen.color
                    @x = module @x + dx, @width
                    @y = module @y + dy, @height
                when 'LEFT', 'LT'
                    rotate = parseInt instruction.parameter[0]
                    @angle = module @angle + rotate, 360
                when 'RIGHT', 'RT'
                    rotate = parseInt instruction.parameter[0]
                    @angle = module @angle - rotate, 360
                when 'SHOWTURTLE', 'ST'
                    @pen.show = true
                when 'HIDETURTLE', 'HT'
                    @pen.show = false
                when 'REPEAT'
                    repeat = parseInt instruction.parameter[0]
                    for i in [1..repeat]
                        @execute instruction.parameter[1], depth + 1
                when 'HOME'
                    @x = Math.round(@width * 0.5)
                    @y = Math.round(@height * 0.5)
                    @angle = 90
                when 'CLEARSCREEN', 'CS'
                    @imageData.clear()
                when 'DRAW'
                    @imageData.clear()
                    @x = Math.round(@width * 0.5)
                    @y = Math.round(@height * 0.5)
                    @angle = 90
                when 'PENDOWN', 'PD'
                    @pen.draw = true
                when 'PENUP', 'PU'
                    @pen.draw = false
                when 'SETHEADING', 'SETH'
                    @angle = module parseInt(instruction.parameter[0]), 360
                when 'SETX'
                    @x = module parseInt(instruction.parameter[0]), @width
                when 'SETY'
                    @y = module parseInt(instruction.parameter[0]), @height
                when 'SETXY'
                    @x = module parseInt(instruction.parameter[0]), @width
                    @y = module parseInt(instruction.parameter[0]), @height
        if depth == 0
            @update()
                    