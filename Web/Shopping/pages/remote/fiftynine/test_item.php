<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品信息测试</title>
    </head>
    <body>
        <?php
        /**
         * 对商品信息的测试。
         * @author ZHG <CyberZHG@gmail.com>
         */
        require_once "DataSourceFiftynine.class.php";
        require_once "test.php";
        $source = new DataSourceFiftynine();
        $result = $source->getItem(34262687);
        printArrayWithTable($result);
        ?>
    </body>
</html>
