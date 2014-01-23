var slideIndex = 0;
var slideTotal = 0;
var canvasLength = 400;

var descList;
var showList;
var codeList;

function drawAxis(context) {
    context.clearRect(0, 0, canvasLength, canvasLength);
    context.strokeStyle = '#fefefe';
    for (var i = -10; i <= 10; ++i) {
        context.moveTo((i + 10) * canvasLength / 20, 0);
        context.lineTo((i + 10) * canvasLength / 20, canvasLength);
        context.stroke();
    }
    context.strokeStyle = '#222222';
    context.moveTo(0, canvasLength / 2);
    context.lineTo(canvasLength, canvasLength / 2);
    context.stroke();
    context.moveTo(canvasLength / 2, 0);
    context.lineTo(canvasLength / 2, canvasLength);
    context.stroke();
}

function header(text) {
    var div = document.getElementById("div_desc");
    div.innerHTML = "";
    var header = document.createElement("div");
    header.className = "header";
    header.innerText = text;
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