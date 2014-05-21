canvas = document.getElementById 'Canvas_Logo'
consoleDiv = document.getElementById 'Div_Console'
parser = new Parser
executer = new Executer canvas
commandCallback = (source) ->
    instructions = parser.parse source
    executer.execute instructions
consoler = new Consoler consoleDiv, 5, commandCallback
document.onkeyup = consoler.onkeyup