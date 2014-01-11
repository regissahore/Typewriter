var ids = null;

function saveUserID() {
  var idText = area_id.value;
  ids = idText.split("\n");
  chrome.storage.sync.set({'ids': ids});
}

function loadUserID() {
  chrome.storage.sync.get('ids', function(items) {
    if (items.ids) {
      ids = items.ids;
	  area_id.value = ids.join("\n");
	}
  });
}

window.onload = function() {
  loadUserID();
  button_save.onclick = saveUserID;
}