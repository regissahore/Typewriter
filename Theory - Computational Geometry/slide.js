desc = [];
show = [];
code = [];

desc.push(function() {
    header("2D点的定义");
    content("点的定义与向量的定义相同，这里不加以区分。");
});
show.push(function(context) {
    drawAxis(context);
});
code.push("struct Point\n{\n    double x, y;\n};\n");

window.onload = function() {
    setContent(desc, show, code);
}