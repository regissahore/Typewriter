<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品搜索</title>
        <link rel = stylesheet href = ../../styles/search/indexResult.css />
        <!-- wPaint -->
        <script src = ./wpaint/inc/jquery.1.8.2.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.core.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.widget.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.mouse.min.js ></script>
        <script src = ./wpaint/inc/jquery.ui.draggable.min.js ></script>
        <script src = ./wpaint/inc/wColorPicker.js ></script>
        <script src = ./wpaint/wPaint.js ></script>
        <link rel = stylesheet href = ./wpaint/inc/wColorPicker.css />
        <link rel = stylesheet href = ./wpaint/wPaint.css />
        <!-- wPaint -->
        <script src = ../../scripts/util/cookie.js></script>
        <script src = ../../scripts/search/setting.js ></script>
        <script src = ../../scripts/search/index2.js ></script>
    </head>
    <body>
        <input id = Result_Number type = hidden value = 0></input>
        <div class = searchDiv>
            <div class = searchLogo>
                <img src = ../../images/logo.png></img>
            </div>
            <div id = dropbox type = text class = searchText ondragover= "dropOver(event);" ondrop = "dropImage(event);">
                将图片拖放于此或利用右边按钮进行搜索
                <input type = button class = searchImage></input>
            </div>
            <div class = uploadImageDiv>
                <a id = Link_Url href = #>粘贴图片网址</a> | 
                <a id = Link_Upload href = #>上传图片</a> |
                <a id = Link_Sketch href = #>绘制轮廓</a>
                <div id = Div_Url>
                    <input id = Text_Url name = website type = text></input>
                    <input id = Button_Url type = submit value = 搜索></input>
                </div>
                <div id = Div_Upload style = display:none>
                    <input id = File_Upload name = upload type = file></input>
                    <ifame id = Hidden_Frame name = Hidden_Frame style = display:none></ifame>
                </div>
                <div id = Div_Sketch style = display:none>
                    <table>
                        <tr>
                            <td>
                                <div id = wPaint style = "position:relative; width:470px; height:300px; background:#CACACA; border:solid black 1px;"></div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <input type = button value = 清除画布 onclick = wPaint_clear(); />
                                <input type = button value = 上传图像 onclick = wPaint_upload(); />
                            </td>
                        </tr>
                    </table>
                    <script src = ../../scripts/search/index2sketch.js></script>
                </div>
            </div>
        </div>
        <div class = resultDiv>
            <div class = infoDiv>
                <div class = searchConfigDetailDiv>
                    <div>
                        <div>
                            原始图像：
                        </div>
                        <div class = originImageDiv>
                            <img id = Img_Origin ></img>
                        </div>
                        <div>
                            <div>
                                搜索设置
                            </div>
                            <hr/>
                            <div>价格范围：</div>
                            <input id = Input_Price_Start type = text></input>
                            -
                            <input id = Input_Price_End type = text></input>
                            <span>元</span>
                        </div>
                        <div>
                            <span>商家：</span>
                            <select id = Select_Seller style = max-width:200px>
                                <option value = 0>不限制</option>
                            </select>
                        </div>
                        <div>
                            <span>类别：</span>
                            <select id = Select_Category style = max-width:200px>
                                <option value = 0>不限制</option>
                            </select>
                            <select id = Select_Category_Sub style = max-width:200px disabled = true >
                                <option value = 0>不限制</option>
                            </select>
                        </div>
                        <div>
                            <div>
                                关注内容：
                            </div>
                            <input id = CheckBox_Shape type = checkbox checked = checked>形状</input>
                            <input id = CheckBox_Color type = checkbox>颜色</input>
                            <input id = CheckBox_Stripe type = checkbox>轮廓</input>
                        </div>
                        <hr/>
                        <input id = Button_Search type = button value = 搜索></input>
                    </div>
                </div>
                <div class = historyDiv >
                    搜索历史：<br/>
                </div>
            </div>
            <div id = Div_Result_Column_0 class = resultColumnDiv></div>
        </div>
        
        <div id = Div_Show_Back></div>
        <div id = Div_Show_Image>
            <img id = Img_Show></img>
        </div>
    </body>
</html>