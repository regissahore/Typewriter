# Introduction

[LogoJS](http://cyberzhg.github.io/LogoJS/) is a online drawing tool based on Logo language.

# Commands

## Movement

* __FORWARD/FD length__, move forward, draw a line if the pen is down.
* __BACK/BK length__, move backward, draw a line if the pen is down.
* __LEFT/LT angle__, rotate left, the angle is 0-360.
* __RIGHT/RT angle__, rotate right, the angle is 0-360.
* __HOME__, return home and face top.
* __CLEARSCREEN/CS__, clear the screen.
* __DRAW__, clear the screen and return home, equivalent to __CS__ + __HOME__.
* __SETHEADING/SETH angle__, set the angle of the turtle head.
* __SETX x__, set x position.
* __SETY y__, set y position.
* __SETXY x y__, set the position of the turtle.

## Color Setting

* __SHOWTURTLE/ST__, show the turtle.
* __HIDETURTLE/HT__, hide the turtle.
* __BACKGROUN/BG index__, set the background color.
* __PENCOLOR/PC index__, set the pen color.
* __PENUP/PU__, move without drawing.
* __PENDOWN/PD__, move with drawing.

## Loop Control

* __REPEAT times [instructions]__, repeat the instructions in bracket.
