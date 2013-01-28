<?php
include_once "sql.php";

function isSymbolExist($symbol) {
    $sql = new SQL();
    $sql->query("SELECT * FROM D_Application WHERE Symbol = '" . $symbol . "';");
    $result = $sql->getAllResult();
    return count($result) > 0;
}

function isNameExist($name) {
    $sql = new SQL();
    $sql->query("SELECT * FROM D_Application WHERE Name = '" . $name . "';");
    $result = $sql->getAllResult();
    return count($result) > 0;
}

/**
 * Get all the applications belong to the user.
 * @param int $userID The id of the user.
 */
function getApplicationByUser($userID) {
    $sql = new SQL();
    $sql->query("SELECT * FROM D_Application WHERE UserID = '" . $userID . "';");
    return $sql->getAllResult();
}

/**
 * Delete application by application ID.
 * @param int $applicationID
 */
function deleteApplication($applicationID) {
    $sql = new SQL();
    $sql->query("DELETE FROM D_Application_Permission WHERE ApplicationID = '" . $applicationID . "';");
    $sql->query("DELETE FROM D_Application WHERE ApplicationID = '" . $applicationID . "';");
}

function applyApplication($info, $permission) {
    $apikey = substr(md5(uniqid(mt_rand(), true)), 0, 32);
    $sql = new SQL();
    $sql->query("INSERT INTO D_Application (UserID, APIKey, Symbol, Name, Description, Type) VALUES (" .
            "'" . $info["id"] . "',"  .
            "'" . $apikey . "'," .
            "'" . $info["symbol"] . "'," .
            "'" . $info["name"] . "'," .
            "'" . $info["description"] . "'," .
            "'" . $info["type"] . "');");
    if(mysql_error()) {
        return false;
    }
    $sql->query("SELECT LAST_INSERT_ID()");
    $result = $sql->getSingleResult();
    $applicationID = $result[0];
    foreach($permission as $row) {
        $sql->query("INSERT INTO D_Application_Permission (ApplicationID, Permission, Type) VALUES (" .
            "'" . $applicationID . "'," .
            "'" . $row . "'," .
            "'" . "0" . "');");
        if(mysql_error()){
            return false;
        }
    }
    return true;
}
?>
