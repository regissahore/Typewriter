canvas = document.getElementById 'Canvas_Logo'
parser = new Parser
executer = new Executer canvas
consoler = new Consoler
instructions = parser.parse 'FD 100 RT 90 FD 100 RT 90 FD 100 RT 90 FD 100'
console.log instructions
executer.execute instructions