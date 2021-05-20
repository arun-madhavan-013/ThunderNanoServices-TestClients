const WebSocket = require('ws');
var myArgs = process.argv.slice(2);
const ThunderAccess = "ws://" + myArgs[0] + "/jsonrpc";

if (myArgs[0] == null || myArgs[1] == null ||myArgs[2] == null) {
	console.log("Usage: nodejs thunderEventListnerJavaScriptClient.js <deviceIP>:<Port> <PluginCallSign>.<PluginVersion> <EventName>");
	process.exit(1);
}

let socket = new WebSocket("ws://" + myArgs[0] + "/jsonrpc", "");
socket.onopen = function(e) {
  console.log("[open] Connection established with Thunder running @ " + myArgs[0]);
  console.log("[open] Subscribing to events...");
  //Eg: {"jsonrpc": "2.0","id": 5,"method":"org.rdk.System.1.register","params": {"event":"onSystemPowerStateChanged","id":"client.events.1"}}
  var cmd = JSON.stringify({jsonrpc:'2.0',id:1, method: myArgs[1] + ".register", params:{event:myArgs[2], id:"client.events.1"}});
  //console.log(cmd);
  socket.send(cmd);
};

socket.onmessage = function(event) {
  console.log(`[message] Data received from server: ${event.data}`);
};

socket.onclose = function(event) {
  if (event.wasClean) {
    console.log(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
  } else {
    // e.g. server process killed or network down
    // event.code is usually 1006 in this case
    console.log('[close] Connection died');
  }
};

socket.onerror = function(error) {
  console.log(`[error] ${error.message}`);
};
