var configFile = "./config.json";
var myArgs = process.argv.slice(2);

if (myArgs[0]) {
    configFile=myArgs[0];
}
const WebSocket = require('ws');

try {
    require(configFile);
} catch (e) {
    console.log('Error: Use relative or absolute path for the config file. (Eg: ./config.json or ~/Desktop/config.json) !!!\n');
}

const config = require(configFile);
console.log("Using config file: '" + configFile + "'");

let socket = new WebSocket("ws://" + config.thunderAccess + "/jsonrpc", "");
var subscribeRequests = [];

socket.onopen = function(e) {
	console.log("[socketOpen]: Connection established with Thunder running @ " + config.thunderAccess);
	if (Array.isArray(config.subscribe)) {
		var idCount = 1;
		config.subscribe.forEach(function(plugin, indexPlugin){
			var callSign = plugin.pluginCallsign;
			if (Array.isArray(plugin.events)) {
				plugin.events.forEach(function(eventName, indexEvents){
                    var data = {jsonrpc:'2.0',id:idCount, method:plugin.pluginCallsign + ".register", params:{event:eventName, id:"client.events."+idCount}};
					console.log("[configData]: " + JSON.stringify(data));
                    subscribeRequests.push(data);
					idCount++;
				});
			}
		});
	}
    socket.emit('thunderresponse', socket, subscribeRequests);
};

socket.on('thunderresponse', function thunderresponse(socket, subscribeRequests) {
    var req = subscribeRequests.shift();
    if (req != undefined) {
        console.log("[thunderReq]: Subscribing " + JSON.stringify(req));
        socket.send(JSON.stringify(req));
    } else if (req == undefined) {
        console.log("[thunderNow]: Awaiting events...");
    }
});

socket.onmessage = function(thunderevent) {
    var data = JSON.parse(thunderevent.data);
    if (data.hasOwnProperty('result') && data['result'] != 0) {
        console.log("[thunderRsp]: something is not right...!!!");
    } else if (data.hasOwnProperty('error') || data.hasOwnProperty('result') && data['result'] == 0) {
        console.log("[thunderRsp]: " + JSON.stringify(data));
        /* TODO: handle error. */
        /* Continue assuming that particular plugin is deactivated, Subscribe to remaining events */
        socket.emit('thunderresponse', socket, subscribeRequests);
    } else {
        /* May be the event. */
        console.log("[thunderEvt]: " + JSON.stringify(data));
    }
};

socket.onclose = function(event) {
	if (event.wasClean) {
		console.log(`[socktClose]: Connection closed cleanly, code=${event.code} reason=${event.reason}`);
	} else {
		console.log("[socktClose]: Connection died");
	}
};

socket.onerror = function(error) {
	console.log(`[socktError]: ${error.message}`);
};

