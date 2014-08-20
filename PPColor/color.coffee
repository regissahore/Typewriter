canvas = document.getElementById 'game_canvas'
width = canvas.width
height = canvas.height
context = canvas.getContext '2d'
WOOD_WIDTH = width / 8.0 + 0.9
WOOD_HEIGHT = 8
SPEED = 2.5

board = []

class Ball
    constructor: ->
        @moving = false
        @dead = false
    setLocation: (@x, @y) =>
    setVelocity: (@vx, @vy) =>
    setColor: (@r, @g, @b) =>
    move: (wood) =>
        if not @moving
            return
        if @x >= 0 and @x < width and @y >= 0 and @y < height
            balls = board[Math.floor @x][Math.floor @y]
            for i in [(balls.length - 1) .. 0]
                if balls[i] == @
                    balls.splice i, 1
                    if balls.length == 0
                        context.fillStyle = '#FFFFFF'
                        context.fillRect Math.floor(@x), Math.floor(@y), 1, 1
                    break
        @x += @vx
        @y += @vy
        @vy += if @vy > 0 then 0.02 else 0.001
        if @x >= 0 and @x < width and @y >= 0 and @y < height
            board[Math.floor @x][Math.floor @y].push @
            context.fillStyle = 'rgb(' + @r + ',' + @g + ',' + @b + ')'
            context.fillRect Math.floor(@x), Math.floor(@y), 1, 1
        @vx = Math.abs @vx if @x < 0.0
        @vx = - Math.abs @vx if @x > width
        @vy = Math.abs @vy if @y < 0.0
        if @y >= height - WOOD_HEIGHT and @y < height
            if @x >= wood.x and @x <= wood.x + WOOD_WIDTH
                bias = (wood.x + WOOD_WIDTH / 2 - @x) / WOOD_WIDTH * 2
                angle = Math.PI / 2 + bias * Math.PI * 0.35
                speed = SPEED * (1.0 + Math.abs bias)
                @vx = speed * Math.cos angle
                @vy = - speed * Math.sin angle
        @dead = true if @y > height
        if @x >= 0 and @x < width and @y >= 0 and @y < height
            for ball in board[Math.floor @x][Math.floor @y]
                if not ball.moving
                    ball.moving = true
                    ball.setVelocity @vx * 0.81, Math.abs @vy
                    @setVelocity @vx * 0.8, Math.abs @vy
        
class Wood
    setLocation: (@x) =>
        @x = 0 if x < 0
        @x = width - WOOD_WIDTH if @x + WOOD_WIDTH >= width
    draw: =>
        context.fillStyle = '#FFFFFF'
        context.fillRect 0, height - WOOD_HEIGHT, width, WOOD_HEIGHT
        context.fillStyle = '#777777'
        context.fillRect @x, height - WOOD_HEIGHT, WOOD_WIDTH, WOOD_HEIGHT
   
wood = new Wood  
wood.setLocation width / 2 - WOOD_WIDTH / 2
 
balls = []
for x in [0 .. (width - 1)]
    board.push []
    for y in [0 .. (height - 1)]
        board[x].push []
    for y in [0 .. (width - 1)]
        h = x * 360 / width
        s = 1
        v = 1
        hi = Math.floor h / 60
        f = h / 60 - hi
        p = Math.floor 55 * v * (1 - s)
        q = Math.floor 255 * v * (1 - f * s)
        t = Math.floor 255 * v * (1 - (1 - f) * s)
        v = Math.floor 255 * v
        ball = new Ball
        ball.setLocation x, y
        ball.setVelocity 0.0, 0.0
        switch hi
            when 0 then ball.setColor v, t, p
            when 1 then ball.setColor q, v, p
            when 2 then ball.setColor p, v, t
            when 3 then ball.setColor p, q, v
            when 4 then ball.setColor t, p, v
            when 5 then ball.setColor v, p, q
        ball.r = Math.floor ball.r * (width - y) / width
        ball.g = Math.floor ball.g * (width - y) / width
        ball.b = Math.floor ball.b * (width - y) / width
        context.fillStyle = 'rgb(' + ball.r + ',' + ball.g + ',' + ball.b + ')'
        context.fillRect Math.floor(x), Math.floor(y), 1, 1
        balls.push ball
        board[x][y].push ball

drawBoard = ->
    wood.draw()
    if Math.random() < 0.7
        SPEED += 0.0005
        ball = new Ball
        ball.setLocation wood.x + (if Math.random() > 0.5 then WOOD_WIDTH  else 0.0), height - WOOD_HEIGHT
        ball.setVelocity (Math.random() - 0.5), -SPEED
        ball.setColor 0, 0, 0
        ball.moving = true
        balls.push ball
    for ball in balls
        ball.move wood
    for i in [(balls.length - 1) .. 0]
        balls.splice i, 1 if balls[i].dead
        
canvas.onmousemove = (event) ->
    x = event.pageX
    y = event.pageY
    box = canvas.getBoundingClientRect()
    x -= box.left * (canvas.width / box.width)
    y -= box.top * (canvas.height / box.height)
    wood.setLocation x - WOOD_WIDTH / 2

setInterval drawBoard, 50