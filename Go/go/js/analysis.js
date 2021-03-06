var index = 0;
var canvasWidth;
var canvasHeight;
var mouseX = 0;
var mouseY = 0;
var nan = NaN;
var inf = 1 / 0;

var displayConfig = {
    displayType: "line-chart",
    showP: true,
    showR: true,
    showLambda: true,
    showMu: true,
    isScienceNum: false,
    tableType: "horizon",
    showName: Object(),
};

function numToString(num) {
    num = parseFloat(num.toFixed(10));
    if (displayConfig.isScienceNum) {
        return num.toExponential();
    }
    return num;
}

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

function getShowName(name) {
    if (name[0] == "'") {
        return name[1] + "'" + "<sub>" + name.substr(2) + "</sub>";
    }
    return name[0] + "<sub>" + name.substr(1) + "</sub>";
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
    if (displayConfig.showP) {
        context.fillStyle = 'rgb(0, 139, 0)';
        context.fillText("可用度", shiftX - 10, shiftY - chartHeight);
    } else if (displayConfig.showR) {
        context.fillStyle = 'rgb(139, 0, 0)';
        context.fillText("不可用度", shiftX - 10, shiftY - chartHeight);
    } else if (displayConfig.showLambda) {
        context.fillStyle = 'rgb(0, 0, 139)';
        context.fillText("故障率", shiftX - 10, shiftY - chartHeight);
    } else if (displayConfig.showMu) {
        context.fillStyle = 'rgb(170, 170, 0)';
        context.fillText("维修率", shiftX - 10, shiftY - chartHeight);
    }
    if (displayConfig.showP) {
        var minP = 1.0;
        var maxP = 0.0;
        for (var i = 0; i < data.ps[index].length; ++i) {
            var value = data.ps[index][i];
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
        for (var i = 0; i < data.ps[index].length; ++i) {
            var value = data.ps[index][i];
            context.lineTo(shiftX + chartWidth * i / data.ps[index].length,
                           shiftY - chartHeight * (value - minP) / (maxP - minP));
        }
        context.stroke();
    }
    if (displayConfig.showR) {
        var minP = 1.0;
        var maxP = 0.0;
        for (var i = 0; i < data.ps[index].length; ++i) {
            var value = 1.0 - data.ps[index][i];
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
        for (var i = 0; i < data.ps[index].length; ++i) {
            var value = 1.0 - data.ps[index][i];
            context.lineTo(shiftX + chartWidth * i / data.ps[index].length,
                           shiftY - (value - minP) / (maxP - minP) * chartHeight);
        }
        context.stroke();
    }
    if (displayConfig.showLambda) {
        var minP = 1e100;
        var maxP = 0;
        for (var i = 0; i < data.lambdas[index].length; ++i) {
            var value = data.lambdas[index][i];
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
        for (var i = 0; i < data.lambdas[index].length; ++i) {
            var value = data.lambdas[index][i];
            context.lineTo(shiftX + chartWidth * i / data.lambdas[index].length,
                           shiftY - (value - minP) / (maxP - minP) * chartHeight);
        }
        context.stroke();
    }
    if (displayConfig.showMu) {
        var minP = 1e100;
        var maxP = 0;
        for (var i = 0; i < data.lambdas[index].length; ++i) {
            var value = data.lambdas[index][i] * data.ps[index][i] / (1 - data.ps[index][i]);
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
        context.strokeStyle = 'rgb(220, 119, 0)';
        context.lineWidth = 2.0;
        for (var i = 0; i < data.lambdas[index].length; ++i) {
            var value = data.lambdas[index][i] * data.ps[index][i] / (1 - data.ps[index][i]);
            context.lineTo(shiftX + chartWidth * i / data.lambdas[index].length,
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
                context.fillText("时间：" + data.times[time], 10, 0);
                context.fillText("可用度：" + numToString(data.ps[index][time]), 10, 20);
                context.fillText("不可用度：" + numToString(1.0 - data.ps[index][time]), 200, 20);
                context.fillText("故障率：" + numToString(data.lambdas[index][time]), 10, 40);
                context.fillText("维修率：" + numToString(data.lambdas[index][time] * data.ps[index][time] / (1.0 - data.ps[index][time])), 200, 40);
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
    
    var nameDiv = document.createElement("span");
    
    var pName = document.createElement("span");
    pName.innerText = "选择操作符：";
    nameDiv.appendChild(pName);
    
    var selectName = document.createElement("select");
    selectName.id = "select_name";
    for (var i = 0; i < data.names.length; ++i) {
        if ((-1 == index && 0 == i) || i == index) {
            selectName.innerHTML += "<option selected='selected'>" + getShowName(data.names[i]) + "</option>";
        } else {
            selectName.innerHTML += "<option>" + getShowName(data.names[i]) + "</option>";
        }
    }
    selectName.onchange = function() {
        var select = document.getElementById("select_name");
        if (index != select.selectedIndex) {
            index = select.selectedIndex;
            updateLineChart();
        }
        return event.preventDefault();
    };
    nameDiv.appendChild(selectName);
    
    configDiv.appendChild(nameDiv);
}

function addParameterList() {
    var configDiv = document.getElementById("div_config");
    configDiv.innerHTML += "<br>";
  
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = displayConfig.showP;
    show.onclick = function() {
        displayConfig.showP = !displayConfig.showP;
        updateDisplay();
    };
    configDiv.appendChild(show);
    var show = document.createElement("span");
    show.innerText = "可用度";
    show.className = "green_block";
    configDiv.appendChild(show);
    
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = displayConfig.showR;
    show.onclick = function() {
        displayConfig.showR = !displayConfig.showR;
        updateDisplay();
    };
    configDiv.appendChild(show);
    var show = document.createElement("span");
    show.innerText = "不可用度";
    show.className = "red_block";
    configDiv.appendChild(show);
    
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = displayConfig.showLambda;
    show.onclick = function() {
        displayConfig.showLambda = !displayConfig.showLambda;
        updateDisplay();
    };
    configDiv.appendChild(show);
    var show = document.createElement("span");
    show.innerText = "故障率";
    show.className = "blue_block";
    configDiv.appendChild(show);
    
    var show = document.createElement("input");
    show.type = "checkbox";
    show.checked = displayConfig.showMu;
    show.onclick = function() {
        displayConfig.showMu = !displayConfig.showMu;
        updateDisplay();
    };
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
    };
    displayDiv.appendChild(canvas);
    window.onscroll = function() {};
    window.onresize = function() {
        canvasWidth = document.documentElement.clientWidth * 0.9;
        canvasHeight = canvasWidth / 4 * 3;
        canvas.width = canvasWidth;
        canvas.height = canvasHeight;
        updateLineChart();
    };
    updateLineChart();
}

function addTableType() {
    var configDiv = document.getElementById("div_config");
    configDiv.innerHTML = "";
    var nameDiv = document.createElement("span");
    
    var pIndex = document.createElement("span");
    pIndex.innerText = "排列方式：";
    nameDiv.appendChild(pIndex);
    
    var selectIndex = document.createElement("select");
    if (displayConfig.tableType == "horizon") {
        selectIndex.innerHTML += "<option value='horizon' selected='selected'>水平排列</option>";
        selectIndex.innerHTML += "<option value='verticle'>竖直排列</option>";
    } else {
        selectIndex.innerHTML += "<option value='horizon'>水平排列</option>";
        selectIndex.innerHTML += "<option value='verticle' selected='selected'>竖直排列</option>";
    }
    
    selectIndex.onclick = function() {
        if (displayConfig.tableType != selectIndex[selectIndex.selectedIndex].value) {
            displayConfig.tableType = selectIndex[selectIndex.selectedIndex].value;
            updateDisplay();
        }
    };
    selectIndex.click();
    nameDiv.appendChild(selectIndex);
    
    configDiv.appendChild(nameDiv);
}

function addNameList() {
    var configDiv = document.getElementById("div_config");
    var nameDiv = document.createElement("div");
    for (var i = 0; i < data.names.length; ++i) {
        var checkbox = document.createElement("input");
        checkbox.type = "checkbox";
        checkbox.checked = displayConfig.showName[data.names[i]];
        checkbox.id = "checkbox_" + data.names[i];
        checkbox.onchange = function(item) {
            for (var j = 0; j < data.names.length; ++j) {
                var checkbox = document.getElementById("checkbox_" + data.names[j]);
                displayConfig.showName[data.names[j]] = checkbox.checked;
            }
            updateDisplay();
        };
        nameDiv.appendChild(checkbox);
        var p = document.createElement("span");
        p.innerHTML = getShowName(data.names[i]);
        nameDiv.appendChild(p);
    }
    configDiv.appendChild(nameDiv);
}

function displayTable() {
    var configDiv = document.getElementById("div_config");
    configDiv.innerHTML = "";
    var displayDiv = document.getElementById("div_display");
    displayDiv.innerHTML = "";
    window.onresize = function() {};
    window.onscroll = function() {
        var spacing = document.getElementById("div_spacing");
        var head = document.getElementById("div_head");
        var rect = spacing.getBoundingClientRect();
        if (rect.top < 0) {
            head.className = "absoluteHead";
            head.style.left = document.body.getBoundingClientRect().left;
        } else {
            head.className = "relativeHead";
            head.style.left = 0;
        }
    };
    addTableType();
    addParameterList();
    addNameList();
    var showCount = displayConfig.showP + displayConfig.showR + displayConfig.showLambda + displayConfig.showMu;
    if (showCount == 0) {
        return;
    }
    var table = "";
    if (displayConfig.tableType == 'horizon') {
        table += "<div id='div_spacing'>";
        table += "<table>";
        for (var i = 0; i < 2; ++i) {
            table += "<tr><td>-</td></tr>";
        }
        table += "</table>";
        table += "<div id='div_head'>";
        table += "<table>";
        table += "<tr>";
        table += "<th>时间</th>";
        for (var i = 0; i < data.names.length; ++i) {
            if (!displayConfig.showName[data.names[i]]) {
                continue;
            }
            table += "<th>" + getShowName(data.names[i]) + "</th>";
            for (var j = 1; j < showCount; ++j) {
                table += "<th></th>";
            }
        }
        table += "</tr>";
        table += "<tr>";
        table += "<td></td>";
        for (var i = 0; i < data.names.length; ++i) {
            if (!displayConfig.showName[data.names[i]]) {
                continue;
            }
            if (displayConfig.showP) {
                table += "<td class='green_block'>可用度</td>";
            }
            if (displayConfig.showR) {
                table += "<td class='red_block'>不可用度</td>";
            }
            if (displayConfig.showLambda) {
                table += "<td class='blue_block'>故障率</td>";
            }
            if (displayConfig.showMu) {
                table += "<td class='yellow_block'>维修率</td>";
            }
        }
        table += "</tr>";
        table += "</table>";
        table += "</div>";
        table += "</div>";
        table += "<table>";
        for (var i = 0; i < data.times.length; ++i) {
            table += "<tr>";
            table += "<td>" + data.times[i] + "</td>";
            for (var j = 0; j < data.names.length; ++j) {
                if (!displayConfig.showName[data.names[j]]) {
                    continue;
                }
                if (displayConfig.showP) {
                    table += "<td>" + numToString(data.ps[j][i]) + "</td>";
                }
                if (displayConfig.showR) {
                    table += "<td>" + numToString(1.0 - data.ps[j][i]) + "</td>";
                }
                if (displayConfig.showLambda) {
                    table += "<td>" + numToString(data.lambdas[j][i]) + "</td>";
                }
                if (displayConfig.showMu) {
                    table += "<td>" + numToString(data.lambdas[j][i] * data.ps[j][i] / (1.0 - data.ps[j][i])) + "</td>";
                }
            }
            table += "</tr>";
        }
        table += "</table>";
    } else {
        table += "<div id='div_spacing'>";
        table += "<table>";
        table += "<tr><td>-</td></tr>";
        table += "</table>";
        table += "<div id='div_head'>";
        table += "<table>";
        table += "<tr>";
        table += "<th>时间</th>";
        table += "<th>类型</th>";
        for (var i = 0; i < data.names.length; ++i) {
            if (!displayConfig.showName[data.names[i]]) {
                continue;
            }
            table += "<th>" + getShowName(data.names[i]) + "</th>";
        }
        table += "</tr>";
        table += "</table>";
        table += "</div>";
        table += "</div>";
        table += "<table>";
        for (var i = 0; i < data.times.length; ++i) {
            var firstShow = true;
            if (displayConfig.showP) {
                table += "<tr>";
                if (firstShow) {
                    firstShow = false;
                    table += "<td>" + data.times[i] + "</td>";
                } else {
                    table += "<td></td>";
                }
                table += "<td>可用度</td>";
                for (var j = 0; j < data.names.length; ++j) {
                    if (!displayConfig.showName[data.names[j]]) {
                        continue;
                    }
                    table += "<td>" + numToString(data.ps[j][i]) + "</td>";
                }
                table += "</tr>";
            }
            if (displayConfig.showR) {
                table += "<tr>";
                if (firstShow) {
                    firstShow = false;
                    table += "<td>" + data.times[i] + "</td>";
                } else {
                    table += "<td></td>";
                }
                table += "<td>不可用度</td>";
                for (var j = 0; j < data.names.length; ++j) {
                    if (!displayConfig.showName[data.names[j]]) {
                        continue;
                    }
                    table += "<td>" + numToString(1.0 - data.ps[j][i]) + "</td>";
                }
                table += "</tr>";
            }
            if (displayConfig.showLambda) {
                table += "<tr>";
                if (firstShow) {
                    firstShow = false;
                    table += "<td>" + data.times[i] + "</td>";
                } else {
                    table += "<td></td>";
                }
                table += "<td>故障率</td>";
                for (var j = 0; j < data.names.length; ++j) {
                    if (!displayConfig.showName[data.names[j]]) {
                        continue;
                    }
                    table += "<td>" + numToString(data.lambdas[j][i]) + "</td>";
                }
                table += "</tr>";
            }
            if (displayConfig.showMu) {
                table += "<tr>";
                if (firstShow) {
                    firstShow = false;
                    table += "<td>" + data.times[i] + "</td>";
                } else {
                    table += "<td></td>";
                }
                table += "<td>维修率</td>";
                for (var j = 0; j < data.names.length; ++j) {
                    if (!displayConfig.showName[data.names[j]]) {
                        continue;
                    }
                    table += "<td>" + numToString(data.lambdas[j][i] * (data.ps[j][i]) / (1.0 - data.ps[j][i])) + "</td>";
                }
                table += "</tr>";
            }
        }
        table += "</table>";
    }
    displayDiv.innerHTML = table;
    window.onscroll();
}

function updateDisplay() {
    switch (displayConfig.displayType) {
    case "line-chart":
        displayLineChart();
        break;
    case "table":
        displayTable();
        break;
    }
}

function updateDisplayType(type) {
    displayConfig.displayType = type.options[type.selectedIndex].value;
    updateDisplay();
}

function updateNumberDisplayType(type) {
    switch (type.options[type.selectedIndex].value) {
    case "float":
        displayConfig.isScienceNum = false;
        break;
    case "science":
        displayConfig.isScienceNum = true;
        break;
    }
    updateDisplay();
}

window.onload = function() {
    for (var i = 0; i < data.names.length; ++i) {
        displayConfig.showName[data.names[i]] = true;
    }
    updateDisplay();
};