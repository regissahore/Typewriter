class Game
    constructor: (@gameDiv) ->
        @stepX = [0, 1, 0, -1]
        @stepY = [1, 0, -1, 0]
        
    init: =>
        @gameDiv.innerHTML = ''
        @depth = 1
        @scores = []
        @total = 0
        @initDisplay()
        @initBoard()
        @initGame()
        @updateDisplay()
        
    initDisplay: =>
        @display = {}
        div = document.createElement 'div'
        div.className = 'game_display'
        @display.depth = document.createElement 'div'
        @display.depth.className = 'game_display_text'
        div.appendChild @display.depth
        @display.score = document.createElement 'div'
        @display.score.className = 'game_display_text'
        div.appendChild @display.score
        @display.scores = document.createElement 'div'
        @display.scores.className = 'game_display_text'
        div.appendChild @display.scores
        @display.total = document.createElement 'div'
        @display.total.className = 'game_display_text'
        div.appendChild @display.total
        @gameDiv.appendChild div
        
    initBoard: =>
        gameBoard = document.createElement 'div'
        gameBoard.className = 'game_board'
        @board = []
        for i in [0..3]
            @board.push []
            gameRow = document.createElement 'div'
            for j in [0..3]
                @board[i].push {}
                gamePiece = document.createElement 'div'
                gamePiece.className = 'game_piece'
                gameRow.appendChild gamePiece
                @board[i][j].div = gamePiece
                @board[i][j].div.onclick = do (i, j) =>
                    => @click i, j
            gameBoard.appendChild gameRow
        @gameDiv.appendChild gameBoard
            
    initGame: =>
        @turn = 1
        @step = 0
        @win = false
        @lose = false
        for i in [0..3]
            for j in [0..3]
                @setNum i, j, 0
                @setBelong i, j, 0
        for i in [0..3]
            for j in [0..2]
                num = if j == 0 then 1 else j 
                while true
                    x = Math.floor Math.random() * 4
                    y = Math.floor Math.random() * 4
                    if @board[x][y].num == 0
                        @setNum x, y, num
                        break
                        
    updateDisplay: =>
        @display.depth.innerText = 'Depth: ' + @depth
        @display.score.innerText = 'Score: ' + @getScore()
        @display.scores.innerText = 'History: ' + @scores
        @display.total.innerText = 'Total score: ' + @total
                        
    setNum: (x, y, num) =>
        @board[x][y].num = num
        @updateStyle x, y
        
    setBelong: (x, y, belong) =>
        @board[x][y].belong = belong
        @updateStyle x, y
        
    setHighLight: (x, y, highLight) =>
        @board[x][y].highLight = highLight
        @updateStyle x, y
        
    updateStyle: (x, y) =>
        switch @board[x][y].num
            when -1 then text = '-'
            when 0 then text = ''
            when 1 then text = '+'
            when 2 then text = '++'
        @board[x][y].div.innerText = text
        switch @board[x][y].belong
            when 0 then className = 'game_piece'
            when 1 then className = 'game_piece' + (if @board[x][y].highLight then ' region1' else ' belong1')
            when 2 then className = 'game_piece' + (if @board[x][y].highLight then ' region2' else ' belong2')
        @board[x][y].div.className = className
        
    getRegionScore: (x, y) =>
        score = @board[x][y].num
        @board[x][y].visit = true
        for k in [0..3]
            tx = x + @stepX[k]
            ty = y + @stepY[k]
            if tx >= 0 and tx <= 3
                if ty >= 0 and ty <= 3
                    if not @board[tx][ty].visit
                        if @board[tx][ty].belong == @board[x][y].belong
                            score += @getRegionScore tx, ty
        return score
        
    getScore: =>
        for i in [0..3]
            for j in [0..3]
                @board[i][j].visit = false
        score1 = 0
        score2 = 0
        for i in [0..3]
            for j in [0..3]
                if not @board[i][j].visit
                    score = @getRegionScore i, j
                    if @board[i][j].belong == 1
                        score1 = score if score > score1
                    else if @board[i][j].belong == 2
                        score2 = score if score > score2
        score1 - score2
        
    maxSearch: (beta, depth, num) =>
        if depth == 0 or num == 16
            return @getScore()
        alpha = -1e10
        for x in [0..3]
            for y in [0..3]
                if @board[x][y].belong == 0
                    @board[x][y].belong = 1
                    score = @minSearch alpha, depth - 1, num + 1
                    @board[x][y].belong = 0
                    if score > alpha
                        alpha = score
                        if num == @step
                            @nextX = x
                            @nextY = y
                    return alpha if alpha >= beta
        return alpha
        
    minSearch: (alpha, depth, num) =>
        if depth == 0 or num == 16
            return @getScore()
        beta = 1e10
        for x in [0..3]
            for y in [0..3]
                if @board[x][y].belong == 0
                    @board[x][y].belong = 2
                    score = @maxSearch beta, depth - 1, num + 1
                    @board[x][y].belong = 0
                    if score < beta
                        beta = score 
                        if num == @step
                            @nextX = x
                            @nextY = y
                    return beta if alpha >= beta
        return beta
        
    click: (x, y) =>
        if not @win and not @lose
            if @board[x][y].belong == 0
                @setBelong x, y, 1
                @step += 1
                if @step != 16
                    @minSearch -1e10, @depth, @step
                    @setBelong @nextX, @nextY, 2
                    @step += 1
                @highLight()
                @updateDisplay()
                if @step == 16
                    if @getScore() > 0 then @showWin() else @showLose()
        else
            if @win then @doWin() else @doLose()
                
    highLightRegion: (x, y) =>
        @board[x][y].highLight = true
        for k in [0..3]
            tx = x + @stepX[k]
            ty = y + @stepY[k]
            if tx >= 0 and tx <= 3
                if ty >= 0 and ty <= 3
                    if not @board[tx][ty].highLight
                        if @board[tx][ty].belong == @board[x][y].belong
                            @highLightRegion tx, ty 
                
    highLight: () =>
        for i in [0..3]
            for j in [0..3]
                @board[i][j].visit = false
                @setHighLight i, j, false
        return if @step == 0
        score1 = 0
        score2 = 0
        for i in [0..3]
            for j in [0..3]
                if not @board[i][j].visit
                    score = @getRegionScore i, j
                    if @board[i][j].belong == 1
                        if score > score1
                            score1 = score
                            x1 = i
                            y1 = j
                    else if @board[i][j].belong == 2
                        if score > score2
                            x2 = i
                            y2 = j
                            score2 = score
        @highLightRegion x1, y1
        @highLightRegion x2, y2
        for i in [0..3]
            for j in [0..3]
                @updateStyle i, j
                
    showWords: (words, belong) =>
        for word in words
            while true
                x = Math.floor Math.random() * 4
                y = Math.floor Math.random() * 4
                if @board[x][y].div.innerText in ['+', '-', '++', ''] and @board[x][y].belong == belong
                    @board[x][y].div.className += ' text'
                    @board[x][y].div.innerText += word
                    break

    showWin: =>
        @win = true
        @showWords ['you', 'win', 'press', 'any', 'grid', 'to', 'continue'], 1
    
    showLose: =>
        @lose = true
        @showWords ['you', 'lose', 'press', 'any', 'grid', 'to', 'retry'], 2
                    
    doWin: =>
        @depth += 1
        score = @getScore()
        @scores.push score
        @total += score
        @initGame()
        @updateDisplay()
        
    doLose: =>
        @initGame()
        @updateDisplay()
    
    
gameDiv = document.getElementById 'game_div'
game = new Game gameDiv
game.init()
query = window.location.search.substring 1
values = query.split '&'
for v in values
    [key, val] = v.split '='
    if key == 'auto' and val == 'true'
        setInterval =>
            if not game.win and not game.lose
                game.maxSearch 1e10, game.depth, game.step
                game.click game.nextX, game.nextY
            else
                game.click 0, 0
        , 200