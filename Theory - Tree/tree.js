/**
 * The drawing and animation of tree.
 * @author ZHG <CyberZHG@gmail.com>
 */

function BasicTreeNode() {
    var treeNode = {
        id: null,
        left: null,
        right: null,
        data: null,
        clone: function() {},
        paint: function(context, cx, cy) {},
    };
    return treeNode;
}

function BasicTree() {
    var tree = {
        head: null,
        clone: function() {},
        operate: function(type, data) {},
    };
    return tree;
}

var TREE_MARGIN_X = 100;
var TREE_MARGIN_Y = 100;
var TREE_ANIMATION = 10;

var treeCanvas = new Object();
var treeContext = null;
var treeList = new Array();
var treeScripts = new Array();
var treeIndex = 0;
var treeLastIndex = 0;
var treeMaxDepth = 0;
var treeIsAnimation = false;
var treeAnimation = 0;
var treePosition = new Array();
var treeLines = new Array();

function drawScripts() {
    treeContext.textAlign = 'left';
    treeContext.textBaseline = 'middle';
    var index = treeIndex;
    if (treeIsAnimation) {
        index = treeLastIndex + treeAnimation / TREE_ANIMATION * (treeIndex - treeLastIndex);
    }
    for (var i = 0; i < treeScripts.length; ++i) {
        var alpha = 1.0 - 0.25 * Math.abs(i - index);
        if (alpha < 0.2) {
            alpha = 0.2;
        }
        var x = 22 - 12 * Math.abs(i - index);
        if (x < 10) {
            x = 10;
        }
        var y = treeCanvas.height / 2 + (i - index) * 20;
        treeContext.globalAlpha = alpha;
        treeContext.fillStyle = '#000000';
        treeContext.font = "16px Consolas";
        treeContext.fillText(treeScripts[i], x, y);
    }
    treeContext.globalAlpha = 1.0;
}

function drawLines() {
    treeContext.lineWidth = 2.0;
    if (treeIsAnimation) {
        treeContext.globalAlpha = treeAnimation / TREE_ANIMATION;
        for (var i in treeLines[treeIndex]) {
            if (typeof(treeLines[treeLastIndex][i]) == 'undefined') {
                var x1 = treeLines[treeIndex][i].x1;
                var y1 = treeLines[treeIndex][i].y1;
                var x2 = treeLines[treeIndex][i].x2;
                var y2 = treeLines[treeIndex][i].y2;
                treeContext.moveTo(x1, y1);
                treeContext.lineTo(x2, y2);
                treeContext.stroke();
            }
        }
        treeContext.globalAlpha = (TREE_ANIMATION - treeAnimation) / TREE_ANIMATION;
        for (var i in treeLines[treeLastIndex]) {
            if (typeof(treeLines[treeIndex][i]) == 'undefined') {
                var x1 = treeLines[treeLastIndex][i].x1;
                var y1 = treeLines[treeLastIndex][i].y1;
                var x2 = treeLines[treeLastIndex][i].x2;
                var y2 = treeLines[treeLastIndex][i].y2;
                treeContext.moveTo(x1, y1);
                treeContext.lineTo(x2, y2);
                treeContext.stroke();
            }
        }
        treeContext.globalAlpha = 1.0;
        for (var i in treeLines[treeIndex]) {
            if (typeof(treeLines[treeLastIndex][i]) != 'undefined') {
                var sx1 = treeLines[treeLastIndex][i].x1;
                var sy1 = treeLines[treeLastIndex][i].y1;
                var sx2 = treeLines[treeLastIndex][i].x2;
                var sy2 = treeLines[treeLastIndex][i].y2;
                var ex1 = treeLines[treeIndex][i].x1;
                var ey1 = treeLines[treeIndex][i].y1;
                var ex2 = treeLines[treeIndex][i].x2;
                var ey2 = treeLines[treeIndex][i].y2;
                var x1 = sx1 + (ex1 - sx1) * treeAnimation / TREE_ANIMATION;
                var y1 = sy1 + (ey1 - sy1) * treeAnimation / TREE_ANIMATION;
                var x2 = sx2 + (ex2 - sx2) * treeAnimation / TREE_ANIMATION;
                var y2 = sy2 + (ey2 - sy2) * treeAnimation / TREE_ANIMATION;
                treeContext.moveTo(x1, y1);
                treeContext.lineTo(x2, y2);
                treeContext.stroke();
            }
        }
    } else {
        for (var i in treeLines[treeIndex]) {
            var x1 = treeLines[treeIndex][i].x1;
            var y1 = treeLines[treeIndex][i].y1;
            var x2 = treeLines[treeIndex][i].x2;
            var y2 = treeLines[treeIndex][i].y2;
            treeContext.moveTo(x1, y1);
            treeContext.lineTo(x2, y2);
            treeContext.stroke();
        }
    }
}

function drawNodes() {
    if (treeIsAnimation) {
        treeContext.globalAlpha = treeAnimation / TREE_ANIMATION;
        for (var i in treePosition[treeIndex]) {
            if (typeof(treePosition[treeLastIndex][i]) == 'undefined') {
                var x = treePosition[treeIndex][i].x;
                var y = treePosition[treeIndex][i].y;
                var node = treePosition[treeIndex][i].node;
                node.paint(treeContext, x, y);
            }
        }
        treeContext.globalAlpha = (TREE_ANIMATION - treeAnimation) / TREE_ANIMATION;
        for (var i in treePosition[treeLastIndex]) {
            if (typeof(treePosition[treeIndex][i]) == 'undefined') {
                var x = treePosition[treeLastIndex][i].x;
                var y = treePosition[treeLastIndex][i].y;
                var node = treePosition[treeLastIndex][i].node;
                node.paint(treeContext, x, y);
            }
        }
        treeContext.globalAlpha = 1.0;
        for (var i in treePosition[treeIndex]) {
            if (typeof(treePosition[treeLastIndex][i]) != 'undefined') {
                var sx = treePosition[treeLastIndex][i].x;
                var sy = treePosition[treeLastIndex][i].y;
                var ex = treePosition[treeIndex][i].x;
                var ey = treePosition[treeIndex][i].y;
                var x = sx + (ex - sx) * treeAnimation / TREE_ANIMATION;
                var y = sy + (ey - sy) * treeAnimation / TREE_ANIMATION;
                var node = treePosition[treeIndex][i].node;
                node.paint(treeContext, x, y);
            }
        }
    } else {
        for (var i in treePosition[treeIndex]) {
            var x = treePosition[treeIndex][i].x;
            var y = treePosition[treeIndex][i].y;
            var node = treePosition[treeIndex][i].node;
            node.paint(treeContext, x, y);
        }
    }
}

function paintTree() {
    treeContext.clearRect(0, 0, treeCanvas.width, treeCanvas.height);
    if (++treeAnimation >= TREE_ANIMATION) {
        treeIsAnimation = false;
    }
    drawScripts();
    drawLines();
    drawNodes();
    treeContext.beginPath();
    treeContext.arc(0, 0, 0, 0, 0, true);
    treeContext.closePath();
}

function initTreePosition() {
    treePosition = new Array();
    treeLines = new Array();
    TREE_MARGIN_Y = (treeCanvas.height - 100) / treeMaxDepth;
    function initRec(head, width, x, y, pos, line) {
        if (typeof(head) == 'undefined') {
            return;
        }
        pos[head.id] = {x: x, y: y, node: head};
        if (typeof(head.left) != 'undefined') {
            line[head.id + "-" + head.left.id] = {x1: x, y1: y, x2: x - width / 2, y2: y + TREE_MARGIN_Y};
            initRec(head.left, width / 2, x - width / 2, y + TREE_MARGIN_Y, pos, line);
        }
        if (typeof(head.right) != 'undefined') {
            line[head.id + "-" + head.right.id] = {x1: x, y1: y, x2: x + width / 2, y2: y + TREE_MARGIN_Y};
            initRec(head.right, width / 2, x + width / 2, y + TREE_MARGIN_Y, pos, line);
        }
    }
    for (var i = 0; i < treeList.length; ++i) {
        var pos = new Object();
        var line = new Object();
        initRec(treeList[i].head, (treeCanvas.width - 200) / 2, treeCanvas.width / 2, 50, pos, line);
        treePosition.push(pos);
        treeLines.push(line);
    }
}

function initTreeCanvas(canvasId) {
    treeCanvas = document.getElementById(canvasId);
    treeContext = treeCanvas.getContext('2d');
    function resizeTreeCanvas() {
        treeCanvas.width = document.documentElement.clientWidth;
        treeCanvas.height = document.documentElement.clientHeight;
        initTreePosition();
    }
    window.onresize = resizeTreeCanvas;
    resizeTreeCanvas();
}

function getTreeDepth(treeNode) {
    if (treeNode == null) {
        return 0;
    }
    return Math.max(getTreeDepth(treeNode.left) + 1, getTreeDepth(treeNode.right) + 1);
}

function getMaxTreeNode() {
    treeMaxDepth = 0;
    for (var i = 0; i < treeList.length; ++i) {
        treeMaxDepth = Math.max(treeMaxDepth, getTreeDepth(treeList[i].head));
    }
}

function setTreeScript(tree, scripts) {
    treeScripts = ['Init'];
    treeScripts = treeScripts.concat(scripts);
    treeList = new Array();
    treeList.push(tree.clone());
    for (var i = 0; i < scripts.length; ++i) {
        var type = scripts[i].split(' ')[0];
        var data = scripts[i].substr(type.length + 1);
        tree.operate(type, data);
        treeList.push(tree.clone());
    }
    treeIndex = 0;
    getMaxTreeNode();
    initTreePosition();
    window.setInterval(paintTree, 50);
    document.onkeyup = function(event) {
        if (treeIsAnimation) {
            return;
        }
        if (event.keyCode == 87) {
            if (treeIndex > 0) {
                treeLastIndex = treeIndex--;
                treeIsAnimation = true;
                treeAnimation = 0;
            }
        } else if (event.keyCode == 83) {
            if (treeIndex < treeList.length - 1) {
                treeLastIndex = treeIndex++;
                treeIsAnimation = true;
                treeAnimation = 0;
            }
        }
    }
}
