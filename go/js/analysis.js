var index = -1;
var vectorIndex = 0;
var canvasWidth;
var canvasHeight;
var mouseX = 0;
var mouseY = 0;

var lineChartConfig = {
    showP: true,
    showR: true,
    showLambda: true,
    showMu: true,
};

function getMousePos(event) {
    var canvas = document.getElementById("line_chart_canvas");
    var obj = canvas;
    var top = 0;
    var left = 0;
    while (obj && obj.tagName != 'BODY') {
        top += obj.offsetTop;
        left += obj.offsetLeft;
        obj = obj.offsetParent;
    }
    mouseX = event.clientX - left + window.pageXOffset;
    mouseY = event.clientY - top + window.pageYOffset;
}

function updateLineChart() {
    if (-1 == index) {
        return;
    }
    var canvas = document.getElementById("line_chart_canvas");
    if (canvas == null) {
        return;
    }
    var context = canvas.getContext('2d');
    var chartWidth = canvasWidth * 0.8;
    var chartHeight = canvasHeight * 0.8;
    var shiftX = (canvasWidth - chartWidth) / 2;
    var shiftY = canvasHeight - (canvasHeight - chartHeight) / 2;
    context.fillStyle = '#FFFFFF';
    context.beginPath();
    context.fillRect(0, 0, canvasWidth, canvasHeight);
    context.fillStyle = '#000000';
    context.strokeStyle = '#000000';
    context.beginPath();
    context.moveTo(shiftX, shiftY);
    context.lineTo(shiftX + chartWidth, shiftY);
    context.stroke();
    context.beginPath();
    context.moveTo(shiftX, shiftY);
    context.lineTo(shiftX, shiftY - chartHeight);
    context.stroke();
    var arrowLength = 20;
    context.beginPath();
    context.moveTo(shiftX + chartWidth, shiftY);
    context.lineTo(shiftX + chartWidth - arrowLength, shiftY - arrowLength / 4);
    context.lineTo(shiftX + chartWidth - arrowLength, shiftY + arrowLength / 4);
    context.closePath();
    context.fill();
    context.beginPath();
    context.moveTo(shiftX, shiftY - chartHeight);
    context.lineTo(shiftX - arrowLength / 4, shiftY - chartHeight + arrowLength);
    context.lineTo(shiftX + arrowLength / 4, shiftY - chartHeight + arrowLength);
    context.closePath();
    context.fill();
    context.font = "18px 微软雅黑";
    context.beginPath();
    context.textAlign = 'right';
    context.textBaseline = 'top';
    context.fillText("时间", shiftX + chartWidth, shiftY + 10);
    context.beginPath();
    if (lineChartConfig.showP) {
        context.fillStyle = 'rgb(0, 139, 0)';
        context.fillText("可用度", shiftX - 10, shiftY - chartHeight);
    } else if (lineChartConfig.showR) {
        context.fillStyle = 'rgb(139, 0, 0)';
        context.fillText("不可用度", shiftX - 10, shiftY - chartHeight);
    } else if (lineChartConfig.showLambda) {
        context.fillStyle = 'rgb(0, 0, 139)';
        context.fillText("故障率", shiftX - 10, shiftY - chartHeight);
    } else if (lineChartConfig.showMu) {
        context.fillStyle = 'rgb(170, 170, 0)';
        context.fillText("维修率", shiftX - 10, shiftY - chartHeight);
    }
    if (lineChartConfig.showP) {
        var minP = 1.0;
        var maxP = 0.0;
        for (var i = 0; i < data.ps[index][vectorIndex].length; ++i) {
            var value = data.ps[index][vectorIndex][i];
            if (value < minP) {
                minP = value;
            }
            if (value > maxP) {
                maxP = value;
            }
        }
        if (maxP - minP < 1e-8) {
            minP = 0.0;
            maxP = 1.0;
        } else {
            maxP *= 1.01;
        }
        context.beginPath();
        context.strokeStyle = 'rgb(0, 139, 0)';
        context.lineWidth = 2.0;
        for (var i = 0; i < data.ps[index][vectorIndex].length; ++i) {
            var value = data.ps[index][vectorIndex][i];
            context.lineTo(shiftX + chartWidth * i / data.ps[index][vectorIndex].length,
                           shiftY - chartHeight * (value - minP) / (maxP - minP));
        }
        context.stroke();
    }
    if (lineChartConfig.showR) {
        var minP = 1.0;
        var maxP = 0.0;
        for (var i = 0; i < data.ps[index][vectorIndex].length; ++i) {
            var value = 1.0 - data.ps[index][vectorIndex][i];
            if (value < minP) {
                minP = value;
            }
            if (value > maxP) {
                maxP = value;
            }
        }
        if (maxP - minP < 1e-8) {
            minP = 0.0;
            maxP = 1.0;
        } else {
            maxP *= 1.01;
        }
        context.beginPath();
        context.strokeStyle = 'rgb(139, 0, 0)';
        context.lineWidth = 2.0;
        for (var i = 0; i < data.ps[index][vectorIndex].length; ++i) {
            var value = 1.0 - data.ps[index][vectorIndex][i];
            context.lineTo(shiftX + chartWidth * i / data.ps[index][vectorIndex].length,
                           shiftY - (value - minP) / (maxP - minP) * chartHeight);
        }
        context.stroke();
    }
    if (lineChartConfig.showLambda) {
        var minP = 1e100;
        var maxP = 0;
        for (var i = 0; i < data.lambdas[index][vectorIndex].length; ++i) {
            var value = data.lambdas[index][vectorIndex][i];
            if (value < minP) {
                minP = value;
            }
            if (value > maxP) {
                maxP = value;
            }
        }
        if (maxP - minP < 1e-8) {
            minP = 0.0;
            maxP = 1.0;
        } else {
            maxP *= 1.01;
        }
        context.beginPath();
        context.strokeStyle = 'rgb(0, 0, 139)';
        context.lineWidth = 2.0;
        for (var i = 0; i < data.lambdas[index][vectorIndex].length; ++i) {
            var value = data.lambdas[index][vectorIndex][i];
            context.lineTo(shiftX + chartWidth * i / data.lambdas[index][vectorIndex].length,
                           shiftY - (value - minP) / (maxP - minP) * chartHeight);
        }
        context.stroke();
    }
    if (lineChartConfig.showMu) {
        var minP = 1e100;
        var maxP = 0;
        for (var i = 0; i < data.lambdas[index][vectorIndex].length; ++i) {
            var value = data.lambdas[index][vectorIndex][i] * (data.ps[index][vectorIndex][i]) / (1 - data.ps[index][vectorIndex][i]);
            if (value > 1e100) {
                continue;
            }
            if (value < minP) {
                minP = value;
            }
            if (value > maxP) {
                maxP = value;
            }
        }
        if (maxP - minP < 1e-8) {
            minP = 0.0;
            maxP = 1.0;
        } else {
            maxP *= 1.01;
        }
        context.beginPath();
        context.strokeStyle = 'rgb(170, 170, 0)';
        context.lineWidth = 2.0;
        for (var i = 0; i < data.lambdas[index][vectorIndex].length; ++i) {
            var value = data.lambdas[index][vectorIndex][i] * (data.ps[index][vectorIndex][i]) / (1 - data.ps[index][vectorIndex][i]);
            context.lineTo(shiftX + chartWidth * i / data.lambdas[index][vectorIndex].length,
                           shiftY - (value - minP) / (maxP - minP) * chartHeight);
        }
        context.stroke();
    }
    if (mouseX >= shiftX && mouseX <= shiftX + chartWidth + 10) {
        if (mouseY >= shiftY - chartHeight && mouseY <= shiftY + 10) {
            var time = Math.floor((mouseX - shiftX) / (chartWidth / data.times.length));
            if (time >= 0 && time < data.times.length) {
                context.fillStyle = '#000000';
                context.textAlign = 'left';
                context.textBaseline = 'top';
                context.font = "16px 微软雅黑";
                context.fillText("时间：" + data.times[time].toFixed(10), 10, 0);
                context.fillText("可用度：" + data.ps[index][vectorIndex][time].toFixed(10), 10, 20);
                context.fillText("不可用度：" + (1.0 - data.ps[index][vectorIndex][time]).toFixed(10), 200, 20);
                context.fillText("故障率：" + data.lambdas[index][vectorIndex][time].toFixed(10), 10, 40);
                context.fillText("维修率：" + (data.lambdas[index][vectorIndex][time] * data.ps[index][vectorIndex][time] / (1.0 - data.ps[index][vectorIndex][time])).toFixed(10), 200, 40);
            }
            context.beginPath();
            context.strokeStyle = '#000000';
            context.globalAlpha = 0.5;
            context.moveTo(mouseX, shiftY - chartHeight);
            context.lineTo(mouseX, shiftY);
            context.stroke();
        }
    }
}

function addOperatorList() {
    var configDiv = document.getElementById("div_config");
    
    var nameDiv = document.createElement("div");
    
    var pName = document.createElement("span");
    pName.innerText = "选择操作符：";
    nameDiv.appendChild(pName);
    
    var selectName = document.createElement("select");
    for (var i = 0; i < data.names.length; ++i) {
        if ((-1 == index && 0 == i) || i == index) {
            selectName.innerHTML += "<option selected='selected'>" + data.names[i] + "</option>";
        } else {
            selectName.innerHTML += "<option>" + data.names[i] + "</option>";
        }
    }
    selectName.onclick = function() {
        if (index != selectName.selectedIndex) {
            index = selectName.selectedIndex;
            updateLineChart();
        }
    };
    selectName.click();
    nameDiv.appendChild(selectName);
    
    var pIndex = document.createElement("span");
    pIndex.innerText = "向量索引：";
    nameDiv.appendChild(pIndex);
    
    var selectIndex = document.createElement("select");
    selectIndex.innerHTML += "<option selected='selected'>" + 1 + "</option>";
    for (var i = 1; i < data.ps[index].length; ++i) {
        selectIndex.innerHTML += "<option >" + (i + 1) + "</option>";
    }
    selectIndex.onclick = function() {
        if (vectorIndex != selectIndex.selectedIndex) {
            vectorIndex = selectIndex.selectedIndex;
            updateLineChart();
        }
    }
    vectorIndex = 0;
    nameDiv.appendChild(selectIndex);
    
    configDiv.appendChild(nameDiv);
}

function addParameterList() {
    var configDiv = document.getElementById("div_config");
  
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = lineChartConfig.showP;
    show.onclick = function() {
        lineChartConfig.showP = !lineChartConfig.showP;
        updateLineChart();
    }
    configDiv.appendChild(show);
    var show = document.createElement("span");
    show.innerText = "可用度";
    show.className = "green_block";
    configDiv.appendChild(show);
    
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = lineChartConfig.showR;
    show.onclick = function() {
        lineChartConfig.showR = !lineChartConfig.showR;
        updateLineChart();
    }
    configDiv.appendChild(show);
    var show = document.createElement("span");
    show.innerText = "不可用度";
    show.className = "red_block";
    configDiv.appendChild(show);
    
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = lineChartConfig.showLambda;
    show.onclick = function() {
        lineChartConfig.showLambda = !lineChartConfig.showLambda;
        updateLineChart();
    }
    configDiv.appendChild(show);
    var show = document.createElement("span");
    show.innerText = "故障率";
    show.className = "blue_block";
    configDiv.appendChild(show);
    
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = lineChartConfig.showMu;
    show.onclick = function() {
        lineChartConfig.showMu = !lineChartConfig.showMu;
        updateLineChart();
    }
    configDiv.appendChild(show);
    var show = document.createElement("span");
    show.innerText = "维修率";
    show.className = "yellow_block";
    configDiv.appendChild(show);
}

function displayLineChart() {
    var configDiv = document.getElementById("div_config");
    configDiv.innerHTML = "";
    var displayDiv = document.getElementById("div_display");
    displayDiv.innerHTML = "";
    addOperatorList();
    addParameterList();
    var canvas = document.createElement("canvas");
    canvasWidth = document.documentElement.clientWidth * 0.9;
    canvasHeight = canvasWidth / 4 * 3;
    canvas.width = canvasWidth;
    canvas.height = canvasHeight;
    canvas.id = "line_chart_canvas";
    canvas.onmousemove = function(event) {
        getMousePos(event);
        updateLineChart();
    }
    displayDiv.appendChild(canvas);
    window.onresize = function() {
        canvasWidth = document.documentElement.clientWidth * 0.9;
        canvasHeight = canvasWidth / 4 * 3;
        canvas.width = canvasWidth;
        canvas.height = canvasHeight;
        updateLineChart();
    }
    updateLineChart();
}

function displayTable() {
    var configDiv = document.getElementById("div_config");
    configDiv.innerHTML = "";
    var displayDiv = document.getElementById("div_display");
    displayDiv.innerHTML = "";
}

function updateDisplayType(type) {
    switch (type.options[type.selectedIndex].value) {
    case "line-chart":
        displayLineChart();
        break;
    case "table":
        displayTable();
        break;
    }
}

window.onload = function() {
    displayLineChart();
}