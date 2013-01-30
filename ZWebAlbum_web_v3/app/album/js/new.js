/**
 * The scripts for creating new album.
 * @author ZHG <CyberZHG@gmail.com>
 */

/**
 * Judge if the album name is already exist.
 */
function judgeNameExist() {
    var xmlhttp = getXMLHttp();
    xmlhttp.onreadystatechange = function() {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            if(xmlhttp.responseText.length > 0) {
                setStatus("Status_Name", TYPE_ERROR, xmlhttp.responseText);
            } else {
                setStatus("Status_Name", TYPE_CORRECT, "");
            }
        }
    }
    xmlhttp.open("GET", "new_exist_ajax.php?albumname=" + Text_Name.value);
    xmlhttp.send();
    setStatus("Status_Name", TYPE_WAITING, "检测中。。。");
}

/**
 * Judge if the length of description is less than valid length.
 * @return boolean
 */
function judgeDescription() {
    var text = "[" + TextArea_Description.value.length + "/240]";
    if(TextArea_Description.value.length <= 240) {
        setStatus("Status_Description", TYPE_CORRECT, text);
        return true;
    } else {
        setStatus("Status_Description", TYPE_ERROR, text);
        return false;
    }
}

function createAlbum() {
    var xmlhttp = getXMLHttp();
    xmlhttp.onreadystatechange = function() {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            if(xmlhttp.responseText.length == "0") {
                setStatus("Status_Create", TYPE_ERROR, "创建失败");
            } else {
                setStatus("Status_Create", TYPE_CORRECT, "");
            }
        }
    }
    var name = Text_Name.value;
    var description = TextArea_Description.value;
    xmlhttp.open("GET", "new_create_ajax.php?name=" + name + "&description=" + description);
    xmlhttp.send();
    setStatus("Status_Create", TYPE_WAITING, "检测中。。。");
}