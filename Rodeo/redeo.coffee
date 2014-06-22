class Game
    constructor: (@gameDiv) ->
    init: =>
        @depth = 0
        @score = []
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
        for i in [0..4]
            for j in [0..4]
                @setNum i, j, 0
                @setBelong i, j, 0
        for i in [0..4]
            for j in [-1..2]
                num = j
                if j == 0
                    num = 1
                while true
                    x = Math.floor Math.random() * 5
                    y = Math.floor Math.random() * 5
                    if @board[x][y].num == 0
                        @setNum x, y, num
                        break
    setNum: (x, y, num) =>
        @board[x][y].num = num
        switch num
            when -1 then text = '-'
            when 0 then text = ''
            when 1 then text = '+'
            when 2 then text = '++'
        @board[x][y].div.innerText = text
    setBelong: (x, y, belong) =>
        @board[x][y].belong = belong
    click: (x, y) =>
        console.log x, y
    
gameDiv = document.getElementById 'game_div'
game = new Game gameDiv
game.init()