/**
 * Splay, POJ2761
 * @author ZHG <CyberZHG@gmail.com>
 */
 
var SPLAY_INF = 100000;

function TreeNode() {
    var treeNode = {
        clone: function() {
            var newNode = TreeNode();
            newNode.id = this.id;
            newNode.data = this.data;
            newNode.leftNum = this.leftNum;
            newNode.rightNum = this.rightNum;
            newNode.highLight = this.highLight;
            if (typeof(this.left) != 'undefined') {
                newNode.left = this.left.clone();
            }
            if (typeof(this.right) != 'undefined') {
                newNode.right = this.right.clone();
            }
            return newNode;
        },
        paint: function(context, cx, cy) {
            context.fillStyle = '#000000';
            if (this.highLight) {
                context.fillStyle = '#FF0000';
            }
            context.beginPath();
            context.arc(cx, cy, 20, 0, Math.PI * 2, true);
            context.closePath();
            context.fill();
            context.fillStyle = '#FFFFFF';
            context.textAlign = 'center';
            context.textBaseline = 'middle';
            context.font = "18px Consolas";
            if (this.data == SPLAY_INF) {
                context.fillText("+∞", cx, cy);
            } else if (this.data == -SPLAY_INF) {
                context.fillText("-∞", cx, cy);
            } else {
                context.fillText("" + this.data, cx, cy);
            }
            context.fillStyle = '#0000FF';
            context.fillText("Left: " + this.leftNum, cx, cy + 30);
            context.fillText("Right: " + this.rightNum, cx, cy + 50);
        },
    };
    return treeNode;
}

function Tree() {
    var tree = {
        clone: function() {
            var newTree = Tree();
            if (typeof(this.head) != 'undefined') {
                newTree.head = this.head.clone();
            }
            return newTree;
        },
        index: 0,
        update: function(node) {
            if (typeof(node) != 'undefined') {
                node.leftNum = 0;
                if (typeof(node.left) != 'undefined') {
                    node.leftNum += node.left.leftNum + node.left.rightNum + 1;
                }
                node.rightNum = 0;
                if (typeof(node.right) != 'undefined') {
                    node.rightNum += node.right.leftNum + node.right.rightNum + 1;
                }
            }
        },
        insert: function(data) {
            data = parseInt(data);
            var newNode = TreeNode();
            newNode.id = this.index++;
            newNode.data = data;
            newNode.leftNum = 0;
            newNode.rightNum = 0;
            newNode.highLight = false;
            if (typeof(this.head) == 'undefined') {
                this.head = newNode;
                return;
            }
            update = this.update;
            function addRec(node) {
                if (data < node.data) {
                    if (typeof(node.left) == 'undefined') {
                        node.left = newNode;
                        ++node.leftNum;
                        newNode.parent = node;
                    } else {
                        addRec(node.left);
                    }
                } else if (data > node.data) {
                    if (typeof(node.right) == 'undefined') {
                        node.right = newNode;
                        ++node.rightNum;
                        newNode.parent = node;
                    } else {
                        addRec(node.right);
                    }
                }
                update(node);
            }
            addRec(this.head);
        },
        query: function(data) {
            function queryRec(node, pos) {
                if (typeof(node) == 'undefined') {
                    return;
                }
                node.highLight = true;
                if (node.leftNum == pos) {
                    return;
                } else if (node.leftNum > pos) {
                    queryRec(node.left, pos);
                } else {
                    queryRec(node.right, pos - node.leftNum - 1);
                }
            }
            queryRec(this.head, parseInt(data));
        },
        find: function(node, data) {
            if (typeof(node) == 'undefined') {
                return;
            }
            if (node.data == data) {
                return node;
            }
            if (node.data < data) {
                return this.find(node.right, data);
            }
            return this.find(node.left, data);
        },
        rotateLeft: function(data) {
            var node = this.find(this.head, parseInt(data));
            var pNode = node.parent;
            var ppNode = pNode.parent;
            node.parent = pNode.parent;
            if (typeof(ppNode.left) != 'undefined') {
                if (ppNode.left == pNode) {
                    ppNode.left = node;
                }
            }
            if (typeof(ppNode.right) != 'undefined') {
                if (ppNode.right == pNode) {
                    ppNode.right = node;
                }
            }
            pNode.parent = node;
            pNode.right = node.left;
            if (typeof(node.left) != 'undefined') {
                node.left.parent = pNode;
            }
            node.left = pNode;
            this.update(pNode);
            this.update(node);
            this.update(ppNode);
        },
        rotateRight: function(data) {
            var node = this.find(this.head, parseInt(data));
            var pNode = node.parent;
            var ppNode = pNode.parent;
            node.parent = ppNode;
            if (typeof(ppNode.left) != 'undefined') {
                if (ppNode.left == pNode) {
                    ppNode.left = node;
                }
            }
            if (typeof(ppNode.right) != 'undefined') {
                if (ppNode.right == pNode) {
                    ppNode.right = node;
                }
            }
            pNode.parent = node;
            pNode.left = node.right;
            if (typeof(node.right) != 'undefined') {
                node.right.parent = pNode;
            }
            node.right = pNode;
            this.update(pNode);
            this.update(node);
            this.update(ppNode);
        },
        remove: function(data) {
            delete this.head.right.left;
            this.head.rightNum -= 1;
            this.head.right.leftNum = 0;
        },
        operate: function(type, data) {
            function removeHighLight(node) {
                if (typeof(node) == 'undefined') {
                    return;
                }
                node.highLight = false;
                removeHighLight(node.left);
                removeHighLight(node.right);
            }
            removeHighLight(this.head);
            switch (type) {
            case 'insert':
                this.insert(data);
                break;
            case 'query':
                this.query(data);
                break;
            case 'left':
                this.rotateLeft(data);
                break;
            case 'right':
                this.rotateRight(data);
                break;
            case 'remove':
                this.remove(data);
                break;
            default: 
                console.log('Undefined operation: ' + type);
            }
        },
    };
    tree.insert(-SPLAY_INF + " " + 0);
    tree.insert(SPLAY_INF + " " + 0);
    return tree;
}

var tree = new Tree();
var scripts = [
    "insert 1",
    "insert 5",
    "insert 2",
    "insert 6",
    "insert 3",
    "query 3",
    "query 0",
    "query 2",
    "right 2",
    "left 2",
    "right 2",
    "remove",
    "insert 7",
    "insert 4",
    "query 1"
];