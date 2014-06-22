class Game
    constructor: (@gameDiv) ->
        @stepx = [0, 1, 0, -1]
        @stepy = [1, 0, -1, 0]
        
    init: =>
        @depth = 1
        @scores = []
        @total = 0
        @initBoard()
        @initGame()
        
    initBoard: =>
        @gameDiv.innerHTML = ''
        @board = []
        for i in [0..4]
            @board.push []
            gameRow = document.createElement 'div'
            for j in [0..4]
                @board[i].push {}
                gamePiece = document.createElement 'div'
                gamePiece.className = 'game_piece'
                gameRow.appendChild gamePiece
                @board[i][j].div = gamePiece
                @board[i][j].div.onclick = do (i, j) =>
                    => @click i, j
            @gameDiv.appendChild gameRow
            
    initGame: =>
        @turn = 1
        @step = 0
        @win = false
        @lose = false
        for i in [0..4]
            for j in [0..4]
                @setNum i, j, 0
                @setBelong i, j, 0
        for i in [0..4]
            for j in [-1..2]
                num = if j == 0 then 1 else j 
                while true
                    x = Math.floor Math.random() * 5
                    y = Math.floor Math.random() * 5
                    if @board[x][y].num == 0
                        @setNum x, y, num
                        break
                        
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
            tx = x + @stepx[k]
            ty = y + @stepy[k]
            if tx >= 0 and tx <= 4
                if ty >= 0 and ty <= 4
                    if not @board[tx][ty].visit
                        if @board[tx][ty].belong == @board[x][y].belong
                            score += @getRegionScore tx, ty
        return score
        
    getScore: =>
        for i in [0..4]
            for j in [0..4]
                @board[i][j].visit = false
        score1 = 0
        score2 = 0
        for i in [0..4]
            for j in [0..4]
                if not @board[i][j].visit
                    score = @getRegionScore i, j
                    if @board[i][j].belong == 1
                        score1 = score if score > score1
                    else if @board[i][j].belong == 2
                        score2 = score if score > score2
        score1 - score2
        
    maxSearch: (beta, depth, num) =>
        if depth == 0 or num == 25
            return @getScore()
        alpha = -1e10
        for x in [0..4]
            for y in [0..4]
                if @board[x][y].belong == 0
                    @board[x][y].belong = 1
                    score = @minSearch alpha, depth - 1, num + 1
                    @board[x][y].belong = 0
                    alpha = score if score > alpha
                    return alpha if alpha >= beta
        return alpha
        
    minSearch: (alpha, depth, num) =>
        if depth == 0 or num == 25
            return @getScore()
        beta = 1e10
        for x in [0..4]
            for y in [0..4]
                if @board[x][y].belong == 0
                    @board[x][y].belong = 2
                    score = @maxSearch alpha, depth - 1, num + 1
                    @board[x][y].belong = 0
                    if score < beta
                        beta = score 
                        if num == @step
                            @nextx = x
                            @nexty = y
                    return beta if alpha >= beta
        return beta
        
    click: (x, y) =>
        if not @win and not @lose
            if @board[x][y].belong == 0
                @setBelong x, y, 1
                @board[x][y].belong = 1
                @step += 1
                if @step == 25
                    if @getScore() > 0 then @doWin() else @doLose()
                else
                    @minSearch -1e10, @depth, @step
                    @setBelong @nextx, @nexty, 2
                    @step += 1
                @highLight()
                
    highLightRegion: (x, y) =>
        @board[x][y].highLight = true
        for k in [0..3]
            tx = x + @stepx[k]
            ty = y + @stepy[k]
            if tx >= 0 and tx <= 4
                if ty >= 0 and ty <= 4
                    if not @board[tx][ty].highLight
                        if @board[tx][ty].belong == @board[x][y].belong
                            @highLightRegion tx, ty 
                
    highLight: () =>
        for i in [0..4]
            for j in [0..4]
                @board[i][j].visit = false
                @setHighLight i, j, false
        return if @step == 0
        score1 = 0
        score2 = 0
        for i in [0..4]
            for j in [0..4]
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
        for i in [0..4]
            for j in [0..4]
                @updateStyle i, j
                    
    doWin: =>
        @win = true
        @depth += 1
        score = @getScore()
        @scores.push score
        @total += score
        @initGame()
    doLose: =>
        @lose = true
        @initGame()
    
    
gameDiv = document.getElementById 'game_div'
game = new Game gameDiv
game.init()