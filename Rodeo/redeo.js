(function() {
  var Game, game, gameDiv,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  Game = (function() {
    function Game(gameDiv) {
      this.gameDiv = gameDiv;
      this.click = __bind(this.click, this);
      this.setBelong = __bind(this.setBelong, this);
      this.setNum = __bind(this.setNum, this);
      this.initGame = __bind(this.initGame, this);
      this.initBoard = __bind(this.initBoard, this);
      this.init = __bind(this.init, this);
    }

    Game.prototype.init = function() {
      this.depth = 0;
      this.score = [];
      this.total = 0;
      this.initBoard();
      return this.initGame();
    };

    Game.prototype.initBoard = function() {
      var gamePiece, gameRow, i, j, _i, _j, _results;
      this.gameDiv.innerHTML = '';
      this.board = [];
      _results = [];
      for (i = _i = 0; _i <= 4; i = ++_i) {
        this.board.push([]);
        gameRow = document.createElement('div');
        for (j = _j = 0; _j <= 4; j = ++_j) {
          this.board[i].push({});
          gamePiece = document.createElement('div');
          gamePiece.className = 'game_piece';
          gameRow.appendChild(gamePiece);
          this.board[i][j].div = gamePiece;
          this.board[i][j].div.onclick = (function(_this) {
            return function(i, j) {
              return function() {
                return _this.click(i, j);
              };
            };
          })(this)(i, j);
        }
        _results.push(this.gameDiv.appendChild(gameRow));
      }
      return _results;
    };

    Game.prototype.initGame = function() {
      var i, j, num, x, y, _i, _j, _k, _results;
      for (i = _i = 0; _i <= 4; i = ++_i) {
        for (j = _j = 0; _j <= 4; j = ++_j) {
          this.setNum(i, j, 0);
          this.setBelong(i, j, 0);
        }
      }
      _results = [];
      for (i = _k = 0; _k <= 4; i = ++_k) {
        _results.push((function() {
          var _l, _results1;
          _results1 = [];
          for (j = _l = -1; _l <= 2; j = ++_l) {
            num = j;
            if (j === 0) {
              num = 1;
            }
            _results1.push((function() {
              var _results2;
              _results2 = [];
              while (true) {
                x = Math.floor(Math.random() * 5);
                y = Math.floor(Math.random() * 5);
                if (this.board[x][y].num === 0) {
                  this.setNum(x, y, num);
                  break;
                } else {
                  _results2.push(void 0);
                }
              }
              return _results2;
            }).call(this));
          }
          return _results1;
        }).call(this));
      }
      return _results;
    };

    Game.prototype.setNum = function(x, y, num) {
      var text;
      this.board[x][y].num = num;
      switch (num) {
        case -1:
          text = '-';
          break;
        case 0:
          text = '';
          break;
        case 1:
          text = '+';
          break;
        case 2:
          text = '++';
      }
      return this.board[x][y].div.innerText = text;
    };

    Game.prototype.setBelong = function(x, y, belong) {
      return this.board[x][y].belong = belong;
    };

    Game.prototype.click = function(x, y) {
      return console.log(x, y);
    };

    return Game;

  })();

  gameDiv = document.getElementById('game_div');

  game = new Game(gameDiv);

  game.init();

}).call(this);
