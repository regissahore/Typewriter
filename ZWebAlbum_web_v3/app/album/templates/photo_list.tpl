<div class = "title">
    <a href = {$url}>全部相册</a>&gt;
    {$album->Name}
    <hr/>
</div>
<div class = "pagerDiv">
{include file = "pager.tpl"}
</div>
{$pageCount = 0}
{foreach item = photo from = $photos}
<div class = "albumDiv">
    <a href = {$url}&albumid={$album->AlbumID}&photopos={($page - 1) * $itemPerPage + $pageCount}>
        {$pageCount = $pageCount + 1}
        <div class = "photoDiv">
            <img width = 200px height = 150px src = {$photo->PhotoPath}></img>
        </div>
    </a>
    <div class = "nameDiv">
        {$photo->Description}
    </div>
</div>
{/foreach}
<div class = "pagerDiv">
{include file = "pager.tpl"}
</div>