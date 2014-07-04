(function() {
  var Ball, SPEED, WOOD_HEIGHT, WOOD_WIDTH, Wood, ball, balls, block, board, canvas, context, drawBoard, f, h, height, hi, p, q, s, t, v, width, wood, x, y, _i, _j, _k, _l, _len, _m, _ref, _ref1, _ref2, _ref3,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  canvas = document.getElementById('game_canvas');

  width = canvas.width;

  height = canvas.height;

  context = canvas.getContext('2d');

  WOOD_WIDTH = width / 4.0;

  WOOD_HEIGHT = 8;

  SPEED = 2.5;

  block = Math.random() < 0.05 ? true : false;

  if (block) {
    WOOD_WIDTH = width * 0.9;
  }

  board = [];

  for (x = _i = 0, _ref = width - 1; 0 <= _ref ? _i <= _ref : _i >= _ref; x = 0 <= _ref ? ++_i : --_i) {
    board.push([]);
    for (y = _j = 0, _ref1 = height - 1; 0 <= _ref1 ? _j <= _ref1 : _j >= _ref1; y = 0 <= _ref1 ? ++_j : --_j) {
      board[x].push([]);
    }
  }

  Ball = (function() {
    function Ball() {
      this.move = __bind(this.move, this);
      this.draw = __bind(this.draw, this);
      this.setColor = __bind(this.setColor, this);
      this.setVelocity = __bind(this.setVelocity, this);
      this.setLocation = __bind(this.setLocation, this);
      this.moving = false;
      this.dead = false;
    }

    Ball.prototype.setLocation = function(x, y) {
      this.x = x;
      this.y = y;
    };

    Ball.prototype.setVelocity = function(vx, vy) {
      this.vx = vx;
      this.vy = vy;
      this.vx += (Math.random() - 0.5) * 0.1;
      return this.vy += (Math.random() - 0.5) * 0.1;
    };

    Ball.prototype.setColor = function(r, g, b) {
      this.r = r;
      this.g = g;
      this.b = b;
    };

    Ball.prototype.draw = function(context) {
      context.fillStyle = 'rgb(' + this.r + ',' + this.g + ',' + this.b + ')';
      return context.fillRect(Math.floor(this.x), Math.floor(this.y), 1, 1);
    };

    Ball.prototype.move = function(wood) {
      var angle, ball, bias, _k, _len, _ref2, _results;
      this.x += this.vx;
      this.y += this.vy;
      if (this.x < 0.0) {
        this.vx = Math.abs(this.vx);
      }
      if (this.x > width) {
        this.vx = -Math.abs(this.vx);
      }
      if (this.y < 0.0) {
        this.vy = Math.abs(this.vy);
      }
      if (this.y >= height - WOOD_HEIGHT && this.y < height) {
        if (this.x >= wood.x && this.x <= wood.x + WOOD_WIDTH) {
          bias = wood.x + WOOD_WIDTH / 2 - this.x;
          angle = Math.PI / 2 + bias / WOOD_WIDTH * Math.PI * 0.9;
          this.vx = SPEED * Math.cos(angle);
          this.vy = -SPEED * Math.sin(angle);
          this.x += this.vx;
          this.y += this.vy;
        }
      }
      if (this.y > height) {
        this.dead = true;
      }
      if (this.x >= 0 && this.x < width && this.y >= 0 && this.y < height) {
        _ref2 = board[Math.floor(this.x)][Math.floor(this.y)];
        _results = [];
        for (_k = 0, _len = _ref2.length; _k < _len; _k++) {
          ball = _ref2[_k];
          ball.moving = true;
          ball.setVelocity(0.0, SPEED);
          board[Math.floor(this.x)][Math.floor(this.y)] = [];
          _results.push(this.setVelocity(-this.vx, Math.abs(this.vy)));
        }
        return _results;
      }
    };

    return Ball;

  })();

  Wood = (function() {
    function Wood() {
      this.draw = __bind(this.draw, this);
      this.setLocation = __bind(this.setLocation, this);
    }

    Wood.prototype.setLocation = function(x) {
      this.x = x;
      if (x < 0) {
        this.x = 0;
      }
      if (this.x + WOOD_WIDTH >= width) {
        return this.x = width - WOOD_WIDTH;
      }
    };

    Wood.prototype.draw = function(context) {
      context.fillStyle = '#777777';
      return context.fillRect(this.x, height - WOOD_HEIGHT, WOOD_WIDTH, WOOD_HEIGHT);
    };

    return Wood;

  })();

  wood = new Wood;

  wood.setLocation(width / 2 - WOOD_WIDTH / 2);

  balls = [];

  for (x = _k = 0, _ref2 = width - 1; 0 <= _ref2 ? _k <= _ref2 : _k >= _ref2; x = 0 <= _ref2 ? ++_k : --_k) {
    for (y = _l = 0, _ref3 = width - 1; 0 <= _ref3 ? _l <= _ref3 : _l >= _ref3; y = 0 <= _ref3 ? ++_l : --_l) {
      h = x * 360 / width;
      s = 1;
      v = 1;
      hi = Math.floor(h / 60);
      f = h / 60 - hi;
      p = Math.floor(55 * v * (1 - s));
      q = Math.floor(255 * v * (1 - f * s));
      t = Math.floor(255 * v * (1 - (1 - f) * s));
      v = Math.floor(255 * v);
      ball = new Ball;
      ball.setLocation(x, y);
      ball.setVelocity(0.0, 0.0);
      switch (hi) {
        case 0:
          ball.setColor(v, t, p);
          break;
        case 1:
          ball.setColor(q, v, p);
          break;
        case 2:
          ball.setColor(p, v, t);
          break;
        case 3:
          ball.setColor(p, q, v);
          break;
        case 4:
          ball.setColor(t, p, v);
          break;
        case 5:
          ball.setColor(v, p, q);
      }
      if (!block) {
        ball.r = Math.floor(ball.r * (width - y) / width);
        ball.g = Math.floor(ball.g * (width - y) / width);
        ball.b = Math.floor(ball.b * (width - y) / width);
      }
      balls.push(ball);
    }
  }

  ball = new Ball;

  ball.setLocation(width / 2, height - WOOD_HEIGHT);

  ball.setVelocity(Math.random() - 0.5, -SPEED);

  ball.setColor(0, 0, 0);

  if (block) {
    ball.setColor(255, 255, 255);
  }

  ball.moving = true;

  balls.push(ball);

  for (_m = 0, _len = balls.length; _m < _len; _m++) {
    ball = balls[_m];
    if (!ball.moving) {
      board[ball.x][ball.y].push(ball);
    }
  }

  drawBoard = function() {
    var i, _len1, _n, _o, _ref4, _results;
    context.fillStyle = block ? '#000000' : '#FFFFFF';
    context.fillRect(0, 0, width, height);
    wood.draw(context);
    for (_n = 0, _len1 = balls.length; _n < _len1; _n++) {
      ball = balls[_n];
      if (ball.moving) {
        ball.move(wood);
      }
      ball.draw(context);
    }
    _results = [];
    for (i = _o = _ref4 = balls.length - 1; _ref4 <= 0 ? _o <= 0 : _o >= 0; i = _ref4 <= 0 ? ++_o : --_o) {
      if (balls[i].dead) {
        _results.push(balls.splice(i, 1));
      } else {
        _results.push(void 0);
      }
    }
    return _results;
  };

  canvas.onmousemove = function(event) {
    var box;
    x = event.pageX;
    y = event.pageY;
    box = canvas.getBoundingClientRect();
    x -= box.left * (canvas.width / box.width);
    y -= box.top * (canvas.height / box.height);
    return wood.setLocation(x - WOOD_WIDTH / 2);
  };

  setInterval(drawBoard, 50);

}).call(this);
