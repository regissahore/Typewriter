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
var TREE_ANIMATION = 5;

var treeCanvas = new Object();
var treeList = new Array();
var treeScripts = new Array();
var treeIndex = 0;
var treeLastIndex = 0;
var treeMaxDepth = 0;
var treeIsAnimation = false;
var treeAnimation = 0;
var treePosition = new Array();

function drawScripts() {
    var context = treeCanvas.getContext('2d');
    context.textAlign = 'left';
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
        context.globalAlpha = alpha;
        context.fillStyle = '#000000';
        context.font = "16px Consolas";
        context.fillText(treeScripts[i], x, 20 + 20 * i);
    }
    context.globalAlpha = 1.0;
}

function drawLines() {
    var context = treeCanvas.getContext('2d');
    function drawLineRec(node) {
        if (typeof(node) == "undefined") {
            return;
        }
        if (typeof(node.left) != "undefined") {
            context.moveTo(treePosition[treeIndex][node.id].x, treePosition[treeIndex][node.id].y);
            context.lineTo(treePosition[treeIndex][node.left.id].x, treePosition[treeIndex][node.left.id].y);
            context.stroke();
            drawLineRec(node.left);
        }
        if (typeof(node.right) != "undefined") {
            context.moveTo(treePosition[treeIndex][node.id].x, treePosition[treeIndex][node.id].y);
            context.lineTo(treePosition[treeIndex][node.right.id].x, treePosition[treeIndex][node.right.id].y);
            context.stroke();
            drawLineRec(node.right);
        }
    }
    drawLineRec(treeList[treeIndex].head);
}

function drawNodes() {
    var context = treeCanvas.getContext('2d');
    function drawNodeRec(node) {
        if (typeof(node) == 'undefined') {
            return;
        }
        node.paint(context, treePosition[treeIndex][node.id].x, treePosition[treeIndex][node.id].y);
        drawNodeRec(node.left);
        drawNodeRec(node.right);
    }
    drawNodeRec(treeList[treeIndex].head);
}

function paintTree() {
    var context = treeCanvas.getContext('2d');
    context.clearRect(0, 0, treeCanvas.width, treeCanvas.height);
    if (++treeAnimation >= TREE_ANIMATION) {
        treeIsAnimation = false;
    }
    drawScripts();
    drawLines();
    drawNodes();
}

function initTreePosition() {
    treePosition = new Array();
    function initRec(head, width, x, y, res) {
        if (typeof(head) == 'undefined') {
            return;
        }
        pos[head.id] = {x: x, y: y};
        initRec(head.left, width / 2, x - width / 2, y + TREE_MARGIN_Y, pos);
        initRec(head.right, width / 2, x + width / 2, y + TREE_MARGIN_Y, pos);
    }
    for (var i = 0; i < treeList.length; ++i) {
        var pos = new Object();
        initRec(treeList[i].head, TREE_MARGIN_X * treeMaxDepth, treeCanvas.width / 2, 50, pos);
        treePosition.push(pos);
    }
}

function initTreeCanvas(canvasId) {
    treeCanvas = document.getElementById(canvasId);
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
