header1("文档对象模型(DOM)");
header2("创建HTML元素");
header3("直接在底部添加");
showScript([
    "for (var i = 0; i < 5; ++i) {",
    "     document.write('<div style = \"border-bottom: 1px solid;\">Test' + i + '</div>');",
    "}"
]);
header3("通过新建元素添加");
showScript([
    "document.write('<div id = create_div style = \"border-left: 20px solid;\">Test 0</div>');",
    "var lastDiv = document.getElementById('create_div');",
    "for (var i = 0; i < 5; ++i) {",
    "    var div = document.createElement('div');",
    "    div.style.cssText = 'border-left: 20px solid;';",
    "    div.innerText = 'Test' + i;",
    "    lastDiv.appendChild(div);",
    "    lastDiv = div;",
    "}"
]);
header2("查找HTML元素");
header3("通过ID查找");
list([
    "可以通过查找获得对应元素。",
    "有ID的元素可以将ID直接当做变量使用。"
]);
showScript([
    "document.write('<div id = find_by_id_div_1></div>');",
    "var div = document.getElementById('find_by_id_div_1');",
    "div.innerText = 'Test 1';",
    "document.write('<div id = find_by_id_div_2></div>');",
    "find_by_id_div_2.innerText = 'Test 2';"
]);
header3("通过Name查找");
list([
    "ID是唯一的，Name是不唯一的，注意元素的拼写。"
]);
showScript([
    "for (var i = 0; i < 5; ++i) {",
    "    document.write('<div name = find_by_name_div></div>');",
    "}",
    "var divs = document.getElementsByName('find_by_name_div');",
    "for (var i = 0; i < divs.length; ++i) {",
    "    divs[i].innerText = 'Test ' + i;",
    "}"
]);
header3("通过Tag查找");
list([
    "为了查找元素内部的元素，可以使用Tag查找。"
]);
showScript([
    "document.write('<div id = find_by_tag_div></div>');",
    "for (var i = 0; i < 5; ++i) {",
    "    var checkbox = document.createElement('input');",
    "    checkbox.type = 'checkbox';",
    "    find_by_tag_div.appendChild(checkbox);",
    "}",
    "document.write(find_by_tag_div.getElementsByTagName('input').length);"
]);
header2("添加元素事件");
header3("悬浮事件");
showScript([
    "document.write('<div style = \"display: inline-block; width: 100px; height: 100px; background: green;\" id = add_event_over_div></div>');",
    "add_event_over_div.onmouseover = function() {",
    "    add_event_over_div.style.background = 'red';",
    "};",
    "add_event_over_div.onmouseout = function() {",
    "    add_event_over_div.style.background = 'green';",
    "};"
]);
header3("点击事件");
showScript([
    "document.write('<div style = \"display: inline-block; width: 100px; height: 100px; background: green;\" id = add_event_click_div></div>');",
    "add_event_click_div.onclick = function() {",
    "    if (add_event_click_div.style.background == 'red') {",
    "        add_event_click_div.style.background = 'green';",
    "    } else {",
    "       add_event_click_div.style.background = 'red'",
    "    }",
    "};"
]);
