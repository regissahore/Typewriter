<?php
/**
 * 通过传递进来的图片的网址进行搜索。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "search.image.php";

if (isset($_POST["website"])) {
    $extension = "";
    $website = $_POST["website"];
    for ($i = strlen($website) - 1; $i >= 0; --$i) {
        $extension = $website[$i] . $extension;
        if ($website[$i] === "?") {
            $extension = "";
        } else if ($website[$i] === ".") {
            break;
        }
    }
    $extension = strtolower($extension);
    if (isExtensionValid($extension)) {
        $token = getTempToken();
        $token .= $extension;
        downloadImage($website, TEMP_PATH . $token);
        $trueToken = getToken(TEMP_PATH . $token) . $extension;
        rename(TEMP_PATH . $token, TEMP_PATH . $trueToken);
        echo json_encode(array("token" => $trueToken));
        if (isset($_POST["redirect"])) {
            header("Location: " . getRedirectURL($trueToken));
            return;
        }
    } else {
        echo json_encode(array("错误" => "图片格式不支持。"));
    }
}
if (isset($_POST["redirect"])) {
    header("Location: ../search/index.php");
    return;
} 
?>