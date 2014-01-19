/**
 * Binary search tree.
 * @author ZHG <CyberZHG@gmail.com>
 */

function TreeNode() {
    var treeNode = {
        clone: function() {
            var newNode = TreeNode();
            newNode.id = this.id;
            newNode.data = this.data;
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
            context.fillText("" + this.data, cx, cy);
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
        add: function(data) {
            data = parseInt(data);
            var newNode = TreeNode();
            newNode.id = this.index++;
            newNode.data = data;
            if (typeof(this.head) == 'undefined') {
                this.head = newNode;
                return;
            }
            function addRec(node) {
                if (data < node.data) {
                    if (typeof(node.left) == 'undefined') {
                        node.left = newNode;
                    } else {
                        addRec(node.left);
                    }
                } else if (data > node.data) {
                    if (typeof(node.right) == 'undefined') {
                        node.right = newNode;
                    } else {
                        addRec(node.right);
                    }
                }
            }
            addRec(this.head);
        },
        operate: function(type, data) {
            switch (type) {
            case 'add':
                this.add(data);
                break;
            default: 
                console.log('Undefined operation: ' + type);
            }
        },
    };
    return tree;
}

var tree = new Tree();
var scripts = [
     "add 3",
     "add 4",
     "add 2",
     "add 1",
     "add 5"
];