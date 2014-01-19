/**
 * Splay.
 * @author ZHG <CyberZHG@gmail.com>
 */
 
var SPLAY_INF = 100000;

function TreeNode() {
    var treeNode = {
        clone: function() {
            var newNode = TreeNode();
            newNode.id = this.id;
            newNode.data = this.data;
            newNode.pos = this.pos;
            newNode.sum = this.sum;
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
            context.beginPath();
            context.arc(cx, cy, 20, 0, Math.PI * 2, true);
            context.closePath();
            context.fill();
            context.fillStyle = '#FFFFFF';
            context.textAlign = 'center';
            context.textBaseline = 'middle';
            context.font = "18px Consolas";
            if (this.pos == SPLAY_INF) {
                context.fillText("+∞", cx, cy);
            } else if (this.pos == -SPLAY_INF) {
                context.fillText("-∞", cx, cy);
            } else {
                context.fillText("" + this.pos, cx, cy);
            }
            context.fillStyle = '#0000FF';
            context.fillText("Sum: " + this.sum, cx, cy + 30);
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
        insert: function(data) {
            pos = parseInt(data.split(' ')[0]);
            val = parseInt(data.split(' ')[1]);
            var newNode = TreeNode();
            newNode.id = this.index++;
            newNode.pos = pos;
            newNode.data = val;
            newNode.sum = val;
            if (typeof(this.head) == 'undefined') {
                this.head = newNode;
                return;
            }
            function addRec(node) {
                if (pos < node.pos) {
                    if (typeof(node.left) == 'undefined') {
                        node.left = newNode;
                        newNode.parent = node.left;
                    } else {
                        addRec(node.left);
                    }
                } else if (pos > node.pos) {
                    if (typeof(node.right) == 'undefined') {
                        node.right = newNode;
                        newNode.parent = node.right;
                    } else {
                        addRec(node.right);
                    }
                }
                node.sum = node.data;
                if (typeof(node.left) != 'undefined') {
                    node.sum += node.left.sum;
                }
                if (typeof(node.right) != 'undefined') {
                    node.sum += node.right.sum;
                }
            }
            addRec(this.head);
        },
        operate: function(type, data) {
            switch (type) {
            case 'insert':
                this.insert(data);
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
    "insert 10 4",
    "insert 5 9",
    "insert 15 2",
    "insert 2 45",
    "insert 12 8",
    "insert 8 32"
];