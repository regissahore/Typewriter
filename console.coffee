class window.Consoler
    constructor: (@consoleDiv, @lineNumber, @commandCallback) ->
        @lines = []
        for i in [0..(@lineNumber - 3)]
            @lines.push('')
        @lines.push('Welcome to use LogoJS!')
        @lines.push('> ')
        @active = ''
        @update()
    update: =>
        @consoleDiv.innerHTML = @lines.join('<br>') + @active
    shift: =>
        @lines[@lineNumber - 1] += @active
        for i in [0..(@lineNumber - 2)]
            @lines[i] = @lines[i + 1]
        @lines[@lineNumber - 1] = '> '
        @active = ''
    onkeyup: (event) =>
        event = event || window.event
        switch event.keyCode
            when 8      # Backspace
                if @active.length > 0
                    @active = @active.substr 0, @active.length - 1
            when 13     # Enter
                @commandCallback @active
                @shift()
            else
                if (event.keyCode >= 48 and event.keyCode <= 57) or 
                   (event.keyCode >= 65 and event.keyCode <= 90) or 
                   event.keyCode == 32
                    @active += String.fromCharCode event.keyCode
        @update()