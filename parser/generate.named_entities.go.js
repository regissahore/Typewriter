/**
 * Read the data from "entities.json" and generate the code of "named_entities.go".
 */
var fs = require('fs')
 
var entities = require('./entities.json');
fd = fs.openSync('named_entities.go', 'w');
fs.writeSync(fd, 'package parser\n');
fs.writeSync(fd, '\n');
fs.writeSync(fd, 'var namedEntitiesTrie *Trie\n');
fs.writeSync(fd, '\n');
fs.writeSync(fd, 'func GetNamedEntitiesTrie() *Trie {\n');
fs.writeSync(fd, '\tif namedEntitiesTrie == nil {\n');
fs.writeSync(fd, '\t\tnamedEntitiesTrie = NewTrie()\n');
for (var key in entities) {
  var shortKey = key.substring(1, key.length - 1);
  var codepoints = entities[key].codepoints;
  fs.writeSync(fd, '\t\tnamedEntitiesTrie.AddWord(NewUTF8String("');
  fs.writeSync(fd, shortKey);
  fs.writeSync(fd, '"), 0, ');
  fs.writeSync(fd, 'NewUTF8StringWithRunes([]rune{');
  for (var i = 0; i < codepoints.length; ++i) {
    if (i > 0) {
      fs.writeSync(fd, ', ');
    }
    fs.writeSync(fd, '' + codepoints[i]);
  }
  fs.writeSync(fd, '}))\n');
}
fs.writeSync(fd, '\t}\n');
fs.writeSync(fd, '\treturn namedEntitiesTrie\n');
fs.writeSync(fd, '}\n');
fs.closeSync(fd);