/**
 * A basic concept of binary tree.
 * @author ZHG <CyberZHG@gmail.com>
 */

function TreeNode() {
    var treeNode = {
        id: -1,
        parent: null,
        left: null,
        right: null,
        data: {},
    };
    return treeNode;
}

function Tree() {
    var tree = {
        node: [],
        add: function(data) {},
        remove: function(data) {},
        query: function(data) {},
        traversal: function(pos) {},
    };
    return tree;
}

var randomTree = Tree();
randomTree.add = function(data) {
    var treeNode = TreeNode();
    treeNode.data = data;
    treeNode.print = function() {
        document.write(treeNode.data);
    }
    if (randomTree.node.length == 0) {
        randomTree.node[0] = treeNode;
    } else {
        var randomAdd = function(current, node) {
            if (Math.random() < 0.5) {
                if (current.left == null) {
                    current.left = treeNode;
                    treeNode.parent = current;
                    randomTree.node.push(treeNode);
                } else {
                    randomAdd(current.left, node);
                }
            } else {
                if (current.right == null) {
                    current.right = treeNode;
                    treeNode.parent = current;
                    randomTree.node.push(treeNode);
                } else {
                    randomAdd(current.right, node);
                }
            }
        }
        randomAdd(randomTree.node[0], treeNode);
    }
}

randomTree.traversal = function(pos) {
    var find = function(node) {
        if (node == null) {
            return;
        }
        node.print();
        document.write(" (");
        find(node.left);
        document.write(") (");
        find(node.right);
        document.write(")");
    };
    find(randomTree.node[pos]);
}

for (var i = 0; i < 10; ++i) {
    randomTree.add(i);
    randomTree.traversal(0);
    document.write("<br/>");
}