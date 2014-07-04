(function() {
  var Ball, SPEED, WOOD_HEIGHT, WOOD_WIDTH, Wood, ball, balls, board, canvas, context, drawBoard, f, h, height, hi, p, q, s, t, v, width, wood, x, y, _i, _j, _k, _ref, _ref1, _ref2,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  canvas = document.getElementById('game_canvas');

  width = canvas.width;

  height = canvas.height;

  context = canvas.getContext('2d');

  WOOD_WIDTH = width / 8.0 + 0.9;

  WOOD_HEIGHT = 8;

  SPEED = 2.5;

  board = [];

  Ball = (function() {
    function Ball() {
      this.move = __bind(this.move, this);
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
    };

    Ball.prototype.setColor = function(r, g, b) {
      this.r = r;
      this.g = g;
      this.b = b;
    };

    Ball.prototype.move = function(wood) {
      var angle, ball, balls, bias, i, speed, _i, _j, _len, _ref, _ref1, _results;
      if (!this.moving) {
        return;
      }
      if (this.x >= 0 && this.x < width && this.y >= 0 && this.y < height) {
        balls = board[Math.floor(this.x)][Math.floor(this.y)];
        for (i = _i = _ref = balls.length - 1; _ref <= 0 ? _i <= 0 : _i >= 0; i = _ref <= 0 ? ++_i : --_i) {
          if (balls[i] === this) {
            balls.splice(i, 1);
            if (balls.length === 0) {
              context.fillStyle = '#FFFFFF';
              context.fillRect(Math.floor(this.x), Math.floor(this.y), 1, 1);
            }
            break;
          }
        }
      }
      this.x += this.vx;
      this.y += this.vy;
      this.vy += 0.001;
      if (this.x >= 0 && this.x < width && this.y >= 0 && this.y < height) {
        board[Math.floor(this.x)][Math.floor(this.y)].push(this);
        context.fillStyle = 'rgb(' + this.r + ',' + this.g + ',' + this.b + ')';
        context.fillRect(Math.floor(this.x), Math.floor(this.y), 1, 1);
      }
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
          bias = (wood.x + WOOD_WIDTH / 2 - this.x) / WOOD_WIDTH * 2;
          angle = Math.PI / 2 + bias * Math.PI * 0.45;
          speed = SPEED * (1.0 + Math.abs(bias));
          this.vx = speed * Math.cos(angle);
          this.vy = -speed * Math.sin(angle);
        }
      }
      if (this.y > height) {
        this.dead = true;
      }
      if (this.x >= 0 && this.x < width && this.y >= 0 && this.y < height) {
        _ref1 = board[Math.floor(this.x)][Math.floor(this.y)];
        _results = [];
        for (_j = 0, _len = _ref1.length; _j < _len; _j++) {
          ball = _ref1[_j];
          if (!ball.moving) {
            ball.moving = true;
            ball.setVelocity(this.vx * 0.81, Math.abs(this.vy));
            _results.push(this.setVelocity(this.vx * 0.8, Math.abs(this.vy)));
          } else {
            _results.push(void 0);
          }
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

    Wood.prototype.draw = function() {
      context.fillStyle = '#FFFFFF';
      context.fillRect(0, height - WOOD_HEIGHT, width, WOOD_HEIGHT);
      context.fillStyle = '#777777';
      return context.fillRect(this.x, height - WOOD_HEIGHT, WOOD_WIDTH, WOOD_HEIGHT);
    };

    return Wood;

  })();

  wood = new Wood;

  wood.setLocation(width / 2 - WOOD_WIDTH / 2);

  balls = [];

  for (x = _i = 0, _ref = width - 1; 0 <= _ref ? _i <= _ref : _i >= _ref; x = 0 <= _ref ? ++_i : --_i) {
    board.push([]);
    for (y = _j = 0, _ref1 = height - 1; 0 <= _ref1 ? _j <= _ref1 : _j >= _ref1; y = 0 <= _ref1 ? ++_j : --_j) {
      board[x].push([]);
    }
    for (y = _k = 0, _ref2 = width - 1; 0 <= _ref2 ? _k <= _ref2 : _k >= _ref2; y = 0 <= _ref2 ? ++_k : --_k) {
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
      ball.r = Math.floor(ball.r * (width - y) / width);
      ball.g = Math.floor(ball.g * (width - y) / width);
      ball.b = Math.floor(ball.b * (width - y) / width);
      context.fillStyle = 'rgb(' + ball.r + ',' + ball.g + ',' + ball.b + ')';
      context.fillRect(Math.floor(x), Math.floor(y), 1, 1);
      balls.push(ball);
      board[x][y].push(ball);
    }
  }

  drawBoard = function() {
    var i, _l, _len, _m, _ref3, _results;
    wood.draw();
    if (Math.random() < 0.1) {
      ball = new Ball;
      ball.setLocation(wood.x + WOOD_WIDTH / 2 + (Math.random() - 0.5) * 10, height - WOOD_HEIGHT);
      ball.setVelocity(Math.random() - 0.5, -SPEED);
      ball.setColor(0, 0, 0);
      ball.moving = true;
      balls.push(ball);
    }
    for (_l = 0, _len = balls.length; _l < _len; _l++) {
      ball = balls[_l];
      ball.move(wood);
    }
    _results = [];
    for (i = _m = _ref3 = balls.length - 1; _ref3 <= 0 ? _m <= 0 : _m >= 0; i = _ref3 <= 0 ? ++_m : --_m) {
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
