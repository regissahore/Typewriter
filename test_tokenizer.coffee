print_tokens = (tokens) ->
    document.write '<table>'
    document.write '<tr><th>Token</th><th>Type</th></tr>'
    for token in tokens
        document.write '<tr><td>' + token.token + '</td><td>' + token.type + '</td></tr>'
    document.write '</table>'

print_errors = (errors) ->
    document.write '<table>'
    document.write '<tr><th>Line</th><th>Error</th></tr>'
    for error in errors
        document.write '<tr><td>' + error.line + '</td><td>' + error.error + '</td></tr>'
    document.write '</table>'
    
code = 'FD 100 LT 100.0 BK 1e2 RT 2.9e8\n' + 
       'PRINT \'Hello world!\'\n' + 
       'MAKE "variable\n' + 
       'REPEAT 4 [FD 100 RT 90]\n' + 
       'forward :variable * (:variable - 1.0)\n' + 
       'TO func :a :b\n' + 
       '    FD :a + :b RT :a / :b\n' +
       'END\n' +
       'func 50 60\n'
tokenizer = new Tokenizer
tokenizer.parse code
document.write code.split('\n').join('<br>') + '<hr>'
print_tokens tokenizer.tokens
print_errors tokenizer.errors
