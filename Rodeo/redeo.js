(function() {
  var Game, game, gameDiv,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  Game = (function() {
    function Game(gameDiv) {
      this.gameDiv = gameDiv;
      this.doLose = __bind(this.doLose, this);
      this.doWin = __bind(this.doWin, this);
      this.highLight = __bind(this.highLight, this);
      this.highLightRegion = __bind(this.highLightRegion, this);
      this.click = __bind(this.click, this);
      this.minSearch = __bind(this.minSearch, this);
      this.maxSearch = __bind(this.maxSearch, this);
      this.getScore = __bind(this.getScore, this);
      this.getRegionScore = __bind(this.getRegionScore, this);
      this.updateStyle = __bind(this.updateStyle, this);
      this.setHighLight = __bind(this.setHighLight, this);
      this.setBelong = __bind(this.setBelong, this);
      this.setNum = __bind(this.setNum, this);
      this.updateDisplay = __bind(this.updateDisplay, this);
      this.initGame = __bind(this.initGame, this);
      this.initBoard = __bind(this.initBoard, this);
      this.initDisplay = __bind(this.initDisplay, this);
      this.init = __bind(this.init, this);
      this.stepx = [0, 1, 0, -1];
      this.stepy = [1, 0, -1, 0];
    }

    Game.prototype.init = function() {
      this.gameDiv.innerHTML = '';
      this.depth = 1;
      this.scores = [];
      this.total = 0;
      this.initDisplay();
      this.initBoard();
      this.initGame();
      return this.updateDisplay();
    };

    Game.prototype.initDisplay = function() {
      var div;
      this.display = {};
      div = document.createElement('div');
      div.className = 'game_display';
      this.display.depth = document.createElement('div');
      this.display.depth.className = 'game_display_text';
      div.appendChild(this.display.depth);
      this.display.score = document.createElement('div');
      this.display.score.className = 'game_display_text';
      div.appendChild(this.display.score);
      this.display.scores = document.createElement('div');
      this.display.scores.className = 'game_display_text';
      div.appendChild(this.display.scores);
      this.display.total = document.createElement('div');
      this.display.total.className = 'game_display_text';
      div.appendChild(this.display.total);
      return this.gameDiv.appendChild(div);
    };

    Game.prototype.initBoard = function() {
      var gameBoard, gamePiece, gameRow, i, j, _i, _j;
      gameBoard = document.createElement('div');
      gameBoard.className = 'game_board';
      this.board = [];
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
        gameBoard.appendChild(gameRow);
      }
      return this.gameDiv.appendChild(gameBoard);
    };

    Game.prototype.initGame = function() {
      var i, j, num, x, y, _i, _j, _k, _results;
      this.turn = 1;
      this.step = 0;
      this.win = false;
      this.lose = false;
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
            num = j === 0 ? 1 : j;
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

    Game.prototype.updateDisplay = function() {
      this.display.depth.innerText = 'Depth: ' + this.depth;
      this.display.score.innerText = 'Score: ' + this.getScore();
      this.display.scores.innerText = 'History: ' + this.scores;
      return this.display.total.innerText = 'Total score: ' + this.total;
    };

    Game.prototype.setNum = function(x, y, num) {
      this.board[x][y].num = num;
      return this.updateStyle(x, y);
    };

    Game.prototype.setBelong = function(x, y, belong) {
      this.board[x][y].belong = belong;
      return this.updateStyle(x, y);
    };

    Game.prototype.setHighLight = function(x, y, highLight) {
      this.board[x][y].highLight = highLight;
      return this.updateStyle(x, y);
    };

    Game.prototype.updateStyle = function(x, y) {
      var className, text;
      switch (this.board[x][y].num) {
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
      this.board[x][y].div.innerText = text;
      switch (this.board[x][y].belong) {
        case 0:
          className = 'game_piece';
          break;
        case 1:
          className = 'game_piece' + (this.board[x][y].highLight ? ' region1' : ' belong1');
          break;
        case 2:
          className = 'game_piece' + (this.board[x][y].highLight ? ' region2' : ' belong2');
      }
      return this.board[x][y].div.className = className;
    };

    Game.prototype.getRegionScore = function(x, y) {
      var k, score, tx, ty, _i;
      score = this.board[x][y].num;
      this.board[x][y].visit = true;
      for (k = _i = 0; _i <= 3; k = ++_i) {
        tx = x + this.stepx[k];
        ty = y + this.stepy[k];
        if (tx >= 0 && tx <= 4) {
          if (ty >= 0 && ty <= 4) {
            if (!this.board[tx][ty].visit) {
              if (this.board[tx][ty].belong === this.board[x][y].belong) {
                score += this.getRegionScore(tx, ty);
              }
            }
          }
        }
      }
      return score;
    };

    Game.prototype.getScore = function() {
      var i, j, score, score1, score2, _i, _j, _k, _l;
      for (i = _i = 0; _i <= 4; i = ++_i) {
        for (j = _j = 0; _j <= 4; j = ++_j) {
          this.board[i][j].visit = false;
        }
      }
      score1 = 0;
      score2 = 0;
      for (i = _k = 0; _k <= 4; i = ++_k) {
        for (j = _l = 0; _l <= 4; j = ++_l) {
          if (!this.board[i][j].visit) {
            score = this.getRegionScore(i, j);
            if (this.board[i][j].belong === 1) {
              if (score > score1) {
                score1 = score;
              }
            } else if (this.board[i][j].belong === 2) {
              if (score > score2) {
                score2 = score;
              }
            }
          }
        }
      }
      return score1 - score2;
    };

    Game.prototype.maxSearch = function(beta, depth, num) {
      var alpha, score, x, y, _i, _j;
      if (depth === 0 || num === 25) {
        return this.getScore();
      }
      alpha = -1e10;
      for (x = _i = 0; _i <= 4; x = ++_i) {
        for (y = _j = 0; _j <= 4; y = ++_j) {
          if (this.board[x][y].belong === 0) {
            this.board[x][y].belong = 1;
            score = this.minSearch(alpha, depth - 1, num + 1);
            this.board[x][y].belong = 0;
            if (score > alpha) {
              alpha = score;
            }
            if (alpha >= beta) {
              return alpha;
            }
          }
        }
      }
      return alpha;
    };

    Game.prototype.minSearch = function(alpha, depth, num) {
      var beta, score, x, y, _i, _j;
      if (depth === 0 || num === 25) {
        return this.getScore();
      }
      beta = 1e10;
      for (x = _i = 0; _i <= 4; x = ++_i) {
        for (y = _j = 0; _j <= 4; y = ++_j) {
          if (this.board[x][y].belong === 0) {
            this.board[x][y].belong = 2;
            score = this.maxSearch(alpha, depth - 1, num + 1);
            this.board[x][y].belong = 0;
            if (score < beta) {
              beta = score;
              if (num === this.step) {
                this.nextx = x;
                this.nexty = y;
              }
            }
            if (alpha >= beta) {
              return beta;
            }
          }
        }
      }
      return beta;
    };

    Game.prototype.click = function(x, y) {
      if (!this.win && !this.lose) {
        if (this.board[x][y].belong === 0) {
          this.setBelong(x, y, 1);
          this.board[x][y].belong = 1;
          this.step += 1;
          if (this.step === 25) {
            if (this.getScore() > 0) {
              this.doWin();
            } else {
              this.doLose();
            }
          } else {
            this.minSearch(-1e10, this.depth, this.step);
            this.setBelong(this.nextx, this.nexty, 2);
            this.step += 1;
          }
          this.highLight();
          return this.updateDisplay();
        }
      }
    };

    Game.prototype.highLightRegion = function(x, y) {
      var k, tx, ty, _i, _results;
      this.board[x][y].highLight = true;
      _results = [];
      for (k = _i = 0; _i <= 3; k = ++_i) {
        tx = x + this.stepx[k];
        ty = y + this.stepy[k];
        if (tx >= 0 && tx <= 4) {
          if (ty >= 0 && ty <= 4) {
            if (!this.board[tx][ty].highLight) {
              if (this.board[tx][ty].belong === this.board[x][y].belong) {
                _results.push(this.highLightRegion(tx, ty));
              } else {
                _results.push(void 0);
              }
            } else {
              _results.push(void 0);
            }
          } else {
            _results.push(void 0);
          }
        } else {
          _results.push(void 0);
        }
      }
      return _results;
    };

    Game.prototype.highLight = function() {
      var i, j, score, score1, score2, x1, x2, y1, y2, _i, _j, _k, _l, _m, _results;
      for (i = _i = 0; _i <= 4; i = ++_i) {
        for (j = _j = 0; _j <= 4; j = ++_j) {
          this.board[i][j].visit = false;
          this.setHighLight(i, j, false);
        }
      }
      if (this.step === 0) {
        return;
      }
      score1 = 0;
      score2 = 0;
      for (i = _k = 0; _k <= 4; i = ++_k) {
        for (j = _l = 0; _l <= 4; j = ++_l) {
          if (!this.board[i][j].visit) {
            score = this.getRegionScore(i, j);
            if (this.board[i][j].belong === 1) {
              if (score > score1) {
                score1 = score;
                x1 = i;
                y1 = j;
              }
            } else if (this.board[i][j].belong === 2) {
              if (score > score2) {
                x2 = i;
                y2 = j;
                score2 = score;
              }
            }
          }
        }
      }
      this.highLightRegion(x1, y1);
      this.highLightRegion(x2, y2);
      _results = [];
      for (i = _m = 0; _m <= 4; i = ++_m) {
        _results.push((function() {
          var _n, _results1;
          _results1 = [];
          for (j = _n = 0; _n <= 4; j = ++_n) {
            _results1.push(this.updateStyle(i, j));
          }
          return _results1;
        }).call(this));
      }
      return _results;
    };

    Game.prototype.doWin = function() {
      var score;
      console.log('win');
      this.win = true;
      this.depth += 1;
      score = this.getScore();
      this.scores.push(score);
      this.total += score;
      this.initGame();
      return this.updateDisplay();
    };

    Game.prototype.doLose = function() {
      console.log('lose');
      this.lose = true;
      this.initGame();
      return this.updateDisplay();
    };

    return Game;

  })();

  gameDiv = document.getElementById('game_div');

  game = new Game(gameDiv);

  game.init();

}).call(this);
