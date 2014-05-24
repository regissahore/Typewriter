// Generated by CoffeeScript 1.7.1
(function() {
  var Environment, ImageData, module, standardColor,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  module = function(x, mod) {
    if (x >= mod) {
      return x % mod;
    }
    if (x < 0) {
      return (x % mod + mod) % mod;
    }
    return x;
  };

  standardColor = function(index) {
    switch (module(index, 16)) {
      case 0:
        return [0, 0, 0];
      case 1:
        return [255, 255, 255];
      case 2:
        return [136, 0, 21];
      case 3:
        return [0, 162, 232];
      case 4:
        return [163, 73, 164];
      case 5:
        return [34, 177, 76];
      case 6:
        return [63, 72, 204];
      case 7:
        return [255, 201, 14];
      case 8:
        return [255, 127, 39];
      case 9:
        return [136, 0, 21];
      case 10:
        return [255, 174, 201];
      case 11:
        return [64, 64, 64];
      case 12:
        return [127, 127, 127];
      case 13:
        return [181, 230, 29];
      case 14:
        return [153, 217, 234];
      case 15:
        return [191, 191, 191];
    }
  };

  ImageData = (function() {
    function ImageData(width, height) {
      this.width = width;
      this.height = height;
      this.drawLine = __bind(this.drawLine, this);
      this.draw = __bind(this.draw, this);
      this.getPixel = __bind(this.getPixel, this);
      this.setPixel = __bind(this.setPixel, this);
      this.clear = __bind(this.clear, this);
      this.clear();
    }

    ImageData.prototype.clear = function() {
      var size;
      size = this.width * this.height * 4;
      return this.data = new Uint8ClampedArray(size);
    };

    ImageData.prototype.setPixel = function(x, y, color) {
      var i, index, _i, _ref;
      index = (y * this.width + x) * 4;
      for (i = _i = 0, _ref = color.length - 1; 0 <= _ref ? _i <= _ref : _i >= _ref; i = 0 <= _ref ? ++_i : --_i) {
        this.data[index + i] = color[i];
      }
      if (color.length < 4) {
        return this.data[index + 3] = 255;
      }
    };

    ImageData.prototype.getPixel = function(x, y) {
      var color, i, index, _i;
      index = (y * this.width + x) * 4;
      color = [];
      for (i = _i = 0; _i <= 3; i = ++_i) {
        color.push(this.data[index + i]);
      }
      return color;
    };

    ImageData.prototype.draw = function(context) {
      var i, imageData, j, _i, _j, _ref;
      imageData = context.getImageData(0, 0, this.width, this.height);
      for (i = _i = 0, _ref = this.data.length - 1; _i <= _ref; i = _i += 4) {
        if (this.data[i + 3] !== 0) {
          for (j = _j = 0; _j <= 2; j = ++_j) {
            imageData.data[i + j] = this.data[i + j];
          }
        }
      }
      return context.putImageData(imageData, 0, 0);
    };

    ImageData.prototype.drawLine = function(x, y, dx, dy, color) {
      var eps, ex, ey, ux, uy, _results, _results1;
      ex = module(x + dx, this.width);
      ey = module(y + dy, this.height);
      ux = dx > 0 ? 1 : -1;
      uy = dy > 0 ? 1 : -1;
      dx = Math.abs(dx);
      dy = Math.abs(dy);
      eps = 0;
      if (dx > dy) {
        _results = [];
        while (x !== ex) {
          this.setPixel(x, y, color);
          eps += dy;
          if ((eps << 1) >= dx) {
            y = module(y + uy, this.height);
            eps -= dx;
          }
          _results.push(x = module(x + ux, this.width));
        }
        return _results;
      } else {
        _results1 = [];
        while (y !== ey) {
          this.setPixel(x, y, color);
          eps += dx;
          if ((eps << 1) >= dy) {
            x = module(x + ux, this.width);
            eps -= dy;
          }
          _results1.push(y = module(y + uy, this.height));
        }
        return _results1;
      }
    };

    return ImageData;

  })();

  Environment = (function() {
    var Layer;

    Layer = (function() {
      function Layer() {
        this.get_function = __bind(this.get_function, this);
        this.get_variable = __bind(this.get_variable, this);
        this.if_function_exist = __bind(this.if_function_exist, this);
        this.is_variable_exist = __bind(this.is_variable_exist, this);
        this.variables = {};
        this.functions = {};
      }

      Layer.prototype.is_variable_exist = function(name) {
        return name in this.variables;
      };

      Layer.prototype.if_function_exist = function(name) {
        return name in this.functions;
      };

      Layer.prototype.get_variable = function(name) {
        return this.variables[name];
      };

      Layer.prototype.get_function = function(name) {
        return this.functions[name];
      };

      return Layer;

    })();

    function Environment() {
      this.get_function = __bind(this.get_function, this);
      this.get_variable = __bind(this.get_variable, this);
      this.is_function_exist = __bind(this.is_function_exist, this);
      this.is_variable_exist = __bind(this.is_variable_exist, this);
      this.fill_layer = __bind(this.fill_layer, this);
      var layers;
      layers = [new Layer];
    }

    Environment.prototype.fill_layer = function(layer) {
      var _results;
      _results = [];
      while (layers.length < layer) {
        _results.push(layers.push(new Layer));
      }
      return _results;
    };

    Environment.prototype.is_variable_exist = function(name, layer) {
      var i, _i;
      fill_layer(layer);
      for (i = _i = layer; layer <= 0 ? _i <= 0 : _i >= 0; i = layer <= 0 ? ++_i : --_i) {
        if (layers[i].is_variable_exist(name)) {
          return true;
        }
      }
      return false;
    };

    Environment.prototype.is_function_exist = function(name, layer) {
      var i, _i;
      fill_layer(layer);
      for (i = _i = layer; layer <= 0 ? _i <= 0 : _i >= 0; i = layer <= 0 ? ++_i : --_i) {
        if (layers[i].is_function_exist(name)) {
          return true;
        }
      }
      return true;
    };

    Environment.prototype.get_variable = function(name, layer) {
      var i, _i;
      fill_layer(layer);
      for (i = _i = layer; layer <= 0 ? _i <= 0 : _i >= 0; i = layer <= 0 ? ++_i : --_i) {
        if (layers[i].is_variable_exist(name)) {
          return layers[i].get_variable(name);
        }
      }
    };

    Environment.prototype.get_function = function(name, layer) {
      var i, _i;
      fill_layer(layer);
      for (i = _i = layer; layer <= 0 ? _i <= 0 : _i >= 0; i = layer <= 0 ? ++_i : --_i) {
        if (layers[i].is_function_exist(name)) {
          return layers[i].get_function(name);
        }
      }
    };

    return Environment;

  })();

  window.Executer = (function() {
    function Executer(canvas) {
      this.canvas = canvas;
      this.execute = __bind(this.execute, this);
      this.update = __bind(this.update, this);
      this.drawTurtle = __bind(this.drawTurtle, this);
      this.toRgb = __bind(this.toRgb, this);
      this.context = this.canvas.getContext('2d');
      this.environment = [];
      this.width = this.canvas.width;
      this.height = this.canvas.height;
      this.x = Math.round(this.width * 0.5);
      this.y = Math.round(this.height * 0.5);
      this.angle = 90;
      this.background = [0, 0, 0];
      this.pen = {
        color: [255, 255, 255],
        down: true,
        show: true
      };
      this.imageData = new ImageData(this.width, this.height);
      this.turtle = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0], [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0], [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0]];
      this.update();
    }

    Executer.prototype.toRgb = function(data) {
      return 'rgb(' + data[0] + ',' + data[1] + ',' + data[2] + ')';
    };

    Executer.prototype.drawTurtle = function() {
      var angle, cx, cy, data, height, i, j, k, rx, ry, sx, sy, tx, ty, width, _i, _ref, _results;
      if (this.pen.show) {
        width = this.turtle[0].length;
        height = this.turtle.length;
        cx = width >> 1;
        cy = height >> 1;
        angle = this.angle * Math.PI / 180.0;
        _results = [];
        for (i = _i = 0, _ref = width - 1; 0 <= _ref ? _i <= _ref : _i >= _ref; i = 0 <= _ref ? ++_i : --_i) {
          _results.push((function() {
            var _j, _k, _ref1, _results1;
            _results1 = [];
            for (j = _j = 0, _ref1 = height - 1; 0 <= _ref1 ? _j <= _ref1 : _j >= _ref1; j = 0 <= _ref1 ? ++_j : --_j) {
              if (this.turtle[j][i] === 1) {
                data = this.context.createImageData(1, 1);
                for (k = _k = 0; _k <= 2; k = ++_k) {
                  data.data[k] = this.pen.color[k];
                }
                data.data[3] = 255;
                sx = i - cx;
                sy = j - cy;
                rx = Math.round(sx * Math.cos(angle) - sy * Math.sin(angle));
                ry = Math.round(sx * Math.sin(angle) + sy * Math.cos(angle));
                tx = module(this.x + rx, this.width);
                ty = module(this.y - ry, this.height);
                _results1.push(this.context.putImageData(data, tx, ty));
              } else {
                _results1.push(void 0);
              }
            }
            return _results1;
          }).call(this));
        }
        return _results;
      }
    };

    Executer.prototype.update = function() {
      this.context.beginPath;
      this.context.fillStyle = this.toRgb(this.background);
      this.context.strokeStyle = this.toRgb(this.background);
      this.context.fillRect(0, 0, this.width, this.height);
      this.context.endPath;
      this.imageData.draw(this.context);
      return this.drawTurtle();
    };

    Executer.prototype.execute = function(instructions, depth) {
      var dx, dy, i, instruction, length, repeat, rotate, _i, _j, _len;
      for (_i = 0, _len = instructions.length; _i < _len; _i++) {
        instruction = instructions[_i];
        switch (instruction.keyword) {
          case 'FORWARD':
          case 'FD':
            length = parseInt(instruction.parameter[0]);
            dx = Math.round(length * Math.cos(this.angle * Math.PI / 180.0));
            dy = -Math.round(length * Math.sin(this.angle * Math.PI / 180.0));
            if (this.pen.down) {
              this.imageData.drawLine(this.x, this.y, dx, dy, this.pen.color);
            }
            this.x = module(this.x + dx, this.width);
            this.y = module(this.y + dy, this.height);
            break;
          case 'BACK':
          case 'BK':
            length = parseInt(instruction.parameter[0]);
            dx = -Math.round(length * Math.cos(this.angle * Math.PI / 180.0));
            dy = Math.round(length * Math.sin(this.angle * Math.PI / 180.0));
            if (this.pen.down) {
              this.imageData.drawLine(this.x, this.y, dx, dy, this.pen.color);
            }
            this.x = module(this.x + dx, this.width);
            this.y = module(this.y + dy, this.height);
            break;
          case 'LEFT':
          case 'LT':
            rotate = parseInt(instruction.parameter[0]);
            this.angle = module(this.angle + rotate, 360);
            break;
          case 'RIGHT':
          case 'RT':
            rotate = parseInt(instruction.parameter[0]);
            this.angle = module(this.angle - rotate, 360);
            break;
          case 'SHOWTURTLE':
          case 'ST':
            this.pen.show = true;
            break;
          case 'HIDETURTLE':
          case 'HT':
            this.pen.show = false;
            break;
          case 'REPEAT':
            repeat = parseInt(instruction.parameter[0]);
            for (i = _j = 1; 1 <= repeat ? _j <= repeat : _j >= repeat; i = 1 <= repeat ? ++_j : --_j) {
              this.execute(instruction.parameter[1], depth + 1);
            }
            break;
          case 'HOME':
            this.x = Math.round(this.width * 0.5);
            this.y = Math.round(this.height * 0.5);
            this.angle = 90;
            break;
          case 'CLEARSCREEN':
          case 'CS':
            this.imageData.clear();
            break;
          case 'DRAW':
            this.imageData.clear();
            this.x = Math.round(this.width * 0.5);
            this.y = Math.round(this.height * 0.5);
            this.angle = 90;
            break;
          case 'PENDOWN':
          case 'PD':
            this.pen.down = true;
            break;
          case 'PENUP':
          case 'PU':
            this.pen.down = false;
            break;
          case 'SETHEADING':
          case 'SETH':
            this.angle = module(parseInt(instruction.parameter[0]), 360);
            break;
          case 'SETX':
            this.x = module(parseInt(instruction.parameter[0]), this.width);
            break;
          case 'SETY':
            this.y = module(parseInt(instruction.parameter[0]), this.height);
            break;
          case 'SETXY':
            this.x = module(parseInt(instruction.parameter[0]), this.width);
            this.y = module(parseInt(instruction.parameter[0]), this.height);
            break;
          case 'BACKGROUND':
          case 'BG':
            this.background = standardColor(parseInt(instruction.parameter[0]));
            break;
          case 'PENCOLOR':
          case 'PC':
            this.pen.color = standardColor(parseInt(instruction.parameter[0]));
        }
      }
      if (depth === 0) {
        return this.update();
      }
    };

    return Executer;

  })();

}).call(this);
