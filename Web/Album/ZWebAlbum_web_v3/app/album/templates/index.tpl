{include file = "header.tpl"}
<script src = "js/ajax.js"></script>
<script src = "js/querystring.js"></script>
{if $tab == ""}
    {if $tabsub == "album_list"}
        {include file = "album_list.tpl"}
    {elseif $tabsub == "photo_list"}
        <script src = "js/photo_list.js"></script>
        {include file = "photo_list.tpl"}
    {elseif $tabsub == "photo"}
        <script src = "js/photo.js"></script>
        {include file = "photo.tpl"}
    {/if}
{elseif $tab == "new"}
    <script src = "js/new.js"></script>
    {include file = "new.tpl"}
{elseif $tab == "upload"}
    <script src = "js/upload.js"></script>
    {include file = "upload.tpl"}
{/if}
{include file = "footer.tpl"}