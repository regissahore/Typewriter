/**
 * Read the data from "entities.json" and generate the code of "named_entities.go".
 * Note that the code point of "&nbsp;" is changed to 32 from 160.
 */
var fs = require('fs')
 
var entities = require('./entities.json');
fd = fs.openSync('named_entities.go', 'w');
fs.writeSync(fd, 'package parser\n');
fs.writeSync(fd, '\n');
fs.writeSync(fd, 'var _namedEntityMap map[string]*UTF8String\n');
fs.writeSync(fd, '\n');
fs.writeSync(fd, 'func GetNamedEntityMap() map[string]*UTF8String {\n');
fs.writeSync(fd, '\tif _namedEntityMap == nil {\n');
fs.writeSync(fd, '\t\tlength := len(_namedEntityNames)\n');
fs.writeSync(fd, '\t\t_namedEntityMap = make(map[string]*UTF8String)\n');
fs.writeSync(fd, '\t\tfor i := 0; i < length; i++ {\n');
fs.writeSync(fd, '\t\t\t_namedEntityMap[_namedEntityNames[i]] = NewUTF8StringWithRunes(_namedEntityValues[i])\n');
fs.writeSync(fd, '\t\t}\n');
fs.writeSync(fd, '\t}\n');
fs.writeSync(fd, '\treturn _namedEntityMap\n');
fs.writeSync(fd, '}\n');
fs.writeSync(fd, '\n');
fs.writeSync(fd, 'var _namedEntityNames = [...]string {\n');
for (var key in entities) {
  if (key[0] != '&' || key[key.length - 1] != ';') {
    continue;
  }
  var shortKey = key.substring(1, key.length - 1);
  fs.writeSync(fd, '\t"');
  fs.writeSync(fd, shortKey);
  fs.writeSync(fd, '",\n');
}
fs.writeSync(fd, '}\n');
fs.writeSync(fd, '\n');
fs.writeSync(fd, 'var _namedEntityValues = [...][]rune {\n');
for (var key in entities) {
  if (key[0] != '&' || key[key.length - 1] != ';') {
    continue;
  }
  var codepoints = entities[key].codepoints;
  fs.writeSync(fd, '\t');
  fs.writeSync(fd, '[]rune{');
  for (var i = 0; i < codepoints.length; ++i) {
    if (i > 0) {
      fs.writeSync(fd, ', ');
    }
    fs.writeSync(fd, '' + codepoints[i]);
  }
  fs.writeSync(fd, '},\n');
}
fs.writeSync(fd, '}\n');
fs.closeSync(fd);