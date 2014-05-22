// Generated by CoffeeScript 1.7.1
(function() {
  var __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };

  window.Consoler = (function() {
    function Consoler(consoleDiv, lineNumber, commandCallback) {
      var i, _i, _ref;
      this.consoleDiv = consoleDiv;
      this.lineNumber = lineNumber;
      this.commandCallback = commandCallback;
      this.onkeyup = __bind(this.onkeyup, this);
      this.shift = __bind(this.shift, this);
      this.update = __bind(this.update, this);
      this.lines = [];
      for (i = _i = 0, _ref = this.lineNumber - 3; 0 <= _ref ? _i <= _ref : _i >= _ref; i = 0 <= _ref ? ++_i : --_i) {
        this.lines.push('');
      }
      this.lines.push('Welcome to use LogoJS!');
      this.lines.push('> ');
      this.active = '';
      this.update();
    }

    Consoler.prototype.update = function() {
      return this.consoleDiv.innerHTML = this.lines.join('<br>') + this.active + '_';
    };

    Consoler.prototype.shift = function() {
      var i, _i, _ref;
      this.lines[this.lineNumber - 1] += this.active;
      for (i = _i = 0, _ref = this.lineNumber - 2; 0 <= _ref ? _i <= _ref : _i >= _ref; i = 0 <= _ref ? ++_i : --_i) {
        this.lines[i] = this.lines[i + 1];
      }
      this.lines[this.lineNumber - 1] = '> ';
      return this.active = '';
    };

    Consoler.prototype.onkeyup = function(event) {
      event = event || window.event;
      switch (event.keyCode) {
        case 8:
          if (this.active.length > 0) {
            this.active = this.active.substr(0, this.active.length - 1);
          }
          break;
        case 13:
          this.commandCallback(this.active);
          this.shift();
          break;
        default:
          if ((event.keyCode >= 48 && event.keyCode <= 57) || (event.keyCode >= 65 && event.keyCode <= 90) || (event.keyCode >= 96 && event.keyCode <= 105) || event.keyCode === 32) {
            this.active += String.fromCharCode(event.keyCode);
          }
          switch (event.keyCode) {
            case 219:
              this.active += '[';
              break;
            case 221:
              this.active += ']';
          }
      }
      return this.update();
    };

    return Consoler;

  })();

}).call(this);
