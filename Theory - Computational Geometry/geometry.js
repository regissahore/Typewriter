var slideIndex = 0;
var slideTotal = 0;
var canvasLength = 800;
var arrowLength = 15;
var textShift = 2;

var descList;
var showList;
var codeList;

function Point() {
    var point = {
        x: 0.0,
        y: 0.0,
    };
    return point;
}

function Segment() {
    var segment = {
        u: Point(),
        v: Point(),
    };
    return segment;
}

function Line() {
    var line = {
        a: 0.0,
        b: 0.0,
        c: 0.0,
    };
    return line;
}

function Rectangle() {
    var rectangle = {
        x: 0.0,
        y: 0.0,
        width: 0.0,
        height: 0.0,
    };
    return rectangle;
}

function Polygon() {
    var polygon = {
        vertex: [],
    };
    return polygon;
}

function Circle() {
    var circle = {
        x: 0.0,
        y: 0.0,
        radius: 0.0,
    };
    return circle;
}

function drawAxis(context) {
    context.clearRect(0, 0, canvasLength, canvasLength);
    context.strokeStyle = '#cccccc';
    for (var i = -10; i <= 10; ++i) {
        context.beginPath();
        context.moveTo((i + 10) * canvasLength / 20, 0);
        context.lineTo((i + 10) * canvasLength / 20, canvasLength);
        context.stroke();
        context.beginPath();
        context.moveTo(0, (i + 10) * canvasLength / 20);
        context.lineTo(canvasLength, (i + 10) * canvasLength / 20);
        context.stroke();
    }
    context.fillStyle = '#000000';
    context.strokeStyle = '#000000';
    context.beginPath();
    context.moveTo(0, canvasLength / 2);
    context.lineTo(canvasLength, canvasLength / 2);
    context.stroke();
    context.beginPath();
    context.moveTo(canvasLength, canvasLength / 2);
    context.lineTo(canvasLength - arrowLength, canvasLength / 2 + arrowLength / 3);
    context.lineTo(canvasLength - arrowLength, canvasLength / 2 - arrowLength / 3);
    context.closePath();
    context.fill();
    context.stroke();
    context.beginPath();
    context.moveTo(canvasLength / 2, 0);
    context.lineTo(canvasLength / 2, canvasLength);
    context.stroke();
    context.beginPath();
    context.moveTo(canvasLength / 2, 0);
    context.lineTo(canvasLength / 2 + arrowLength / 3, arrowLength);
    context.lineTo(canvasLength / 2 - arrowLength / 3, arrowLength);
    context.closePath();
    context.fill();
    context.stroke();
    context.font = "16px Consolas";
    context.fillStyle = '#aaaaaa';
    for (var i = -9; i <= 9; ++i) {
        if (i == 0) {
            context.textAlign = 'right';
            context.textBaseline = 'top';
            context.fillText(i, canvasLength / 2 - textShift, canvasLength / 2 + textShift);
        } else {
            context.textAlign = 'center';
            context.textBaseline = 'top';
            context.fillText(i, (i + 10) * canvasLength / 20, canvasLength / 2 + textShift);
            context.textAlign = 'right';
            context.textBaseline = 'middle';
            context.fillText(-i, canvasLength / 2 - textShift, (i + 10) * canvasLength / 20);
        }
    }
    context.textAlign = 'center';
    context.textBaseline = 'top';
    context.fillText("x", canvasLength - textShift, canvasLength / 2 + textShift);
    context.textAlign = 'right';
    context.textBaseline = 'middle';
    context.fillText("y", canvasLength / 2 - textShift, textShift);
}

function getX(x) {
    return (x + 10) / 20 * canvasLength;
}

function getY(y) {
    return (10 - y) / 20 * canvasLength;
}

function getPointX(point) {
    return (point.x + 10) / 20 * canvasLength;
}

function getPointY(point) {
    return (10 - point.y) / 20 * canvasLength;
}

function drawPoint(context, point) {
    context.beginPath();
    context.fillStyle = "#0000FF";
    context.arc(getPointX(point), getPointY(point), 4, 0, Math.PI * 2, true);
    context.closePath();
    context.fill();
}

function drawPoints(context, points) {
    for (var point in points) {
        drawPoint(context, point);
    }
}

function drawSegment(context, segment) {
    context.beginPath();
    context.lineWidth = 2;
    context.strokeStyle = '#00CF00';
    context.moveTo(getPointX(segment.u), getPointY(segment.u));
    context.lineTo(getPointX(segment.v), getPointY(segment.v));
    context.stroke();
}

function drawSegments(context, segments) {
    for (var segment in segments) {
        drawSegment(context, segment);
    }
}

function drawLine(context, line) {
    context.lineWidth = 2;
    context.strokeStyle = '#007F7F';
    if (Math.abs(line.b) > 1e-8) {
        context.beginPath();
        for (var i = -10; i <= 10; i += 20 / canvasLength) {
            var point = Point();
            point.x = i;
            point.y = -(line.a * i + line.c) / line.b;
            context.lineTo(getPointX(point), getPointY(point));
        }
        context.stroke();
    }
    if (Math.abs(line.a) > 1e-8) {
        context.beginPath();
        for (var i = -10; i <= 10; i += 20 / canvasLength) {
            var point = Point();
            point.x = -(line.b * i + line.c) / line.a;
            point.y = i;
            context.lineTo(getPointX(point), getPointY(point));
        }
        context.stroke();
    }
}

function drawLines(context, lines) {
    for (var line in lines) {
        drawLine(context, line);
    }
}

function drawPolygon(context, polygon) {
    context.beginPath();
    context.lineWidth = 2;
    context.strokeStyle = '#FF7F00';
    for (var i = 0; i < polygon.vertex.length; ++i) {
        context.lineTo(getPointX(polygon.vertex[i]), getPointY(polygon.vertex[i]));
    }
    context.closePath();
    context.stroke();
}

function drawPolygons(context, polygons) {
    for (var polygon in polygons) {
        drawPolygon(context, polygon);
    }
}

function drawRectangle(context, rectangle) {
    context.lineWidth = 2;
    context.strokeStyle = '#CF0000';
    context.strokeRect(getX(rectangle.x), getY(rectangle.y), rectangle.width / 20 * canvasLength, rectangle.height / 20 * canvasLength);
}

function drawRectangles(context, rectangles) {
    for (var rectangle in rectangles) {
        drawRectangle(context, rectangle);
    }
}

function drawCircle(context, circle) {
    context.lineWidth = 2;
    context.fillStyle = '#FF00CF';
    context.strokeStyle = '#FF00CF';
    context.beginPath();
    context.arc(getX(circle.x), getY(circle.y), circle.radius / 20 * canvasLength, 0, Math.PI * 2, true);
    context.stroke();
    context.beginPath();
    context.arc(getX(circle.x), getY(circle.y), 2, 0, Math.PI * 2, true);
    context.fill();
}

function drawCircles(context, circles) {
    for (var circle in circles) {
        drawCircle(context, circle);
    }
}

function header(text) {
    var div = document.getElementById("div_desc");
    div.innerHTML = "";
    var header = document.createElement("div");
    header.className = "header";
    header.innerText = (slideIndex + 1) + "/" + slideTotal + " " + text;
    div.appendChild(header);
}

function content(text) {
    var div = document.getElementById("div_desc");
    var conent = document.createElement("div");
    conent.innerHTML = text + "<br/><br/>";
    div.appendChild(conent);
}

function slide() {
    descList[slideIndex]();
    var canvas = document.getElementById("canvas_show");
    canvas.width = canvasLength;
    canvas.height = canvasLength;
    var context = canvas.getContext('2d');
    showList[slideIndex](context);
    var div = document.getElementById("div_code");
    div.innerHTML = printScript(codeList[slideIndex]) + "<br/><br/>";
}

function prev() {
    if (slideIndex > 0) {
        --slideIndex;
    }
    slide();
}

function next() {
    if (slideIndex < slideTotal) {
        ++slideIndex;
    }
    slide();
}

function setContent(desc, show, code) {
    descList = desc;
    showList = show;
    codeList = code;
    slideIndex = 0;
    slideTotal = descList.length;
    slide();
}

document.onkeyup = function(event) {
    if (event.keyCode == 87) {
        prev();
    } else if (event.keyCode == 83) {
        next();
    }
}