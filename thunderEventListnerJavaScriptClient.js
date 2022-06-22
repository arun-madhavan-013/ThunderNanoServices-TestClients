var configFile = "./config.json";
var myArgs = process.argv.slice(2);

if (myArgs[0]) {
	configFile=myArgs[0];
}
const WebSocket = require('ws');
const axios = require('axios');

try {
	require(configFile);
} catch (e) {
	console.log('Error: Use relative or absolute path for the config file. (Eg: ./config.json or ~/Desktop/config.json) !!!\n');
}

const config = require(configFile);
console.log("Using config file: '" + configFile + "'");

let socket = new WebSocket('ws://' + config.thunderAccess + '/jsonrpc');
var activateRequests = [];
var subscribeRequests = [];
var totalSubscribedEvents = 0;
var totalActivateReqs = 0;
var timerHandle;

function parseConfig(cfgFile) {
	if (Array.isArray(cfgFile.subscribe)) {
		var idCount = 1;
		cfgFile.subscribe.forEach(function(plugin, indexPlugin){
			var callSign = plugin.pluginCallsign;
			var activate = {jsonrpc:'2.0',id:123, method: "Controller.1.activate", params:{callsign: plugin.pluginCallsign}};
			activateRequests.push(activate);
			totalActivateReqs++;
			if (Array.isArray(plugin.events)) {
				plugin.events.forEach(function(eventName, indexEvents){
					var data = {jsonrpc:'2.0',id:idCount, method:plugin.pluginCallsign + ".register", params:{event:eventName, id:"client.events."+idCount}};
					subscribeRequests.push(data);
					idCount++;
					totalSubscribedEvents++;
				});
			}
		});
	}
}

function activatePlugin(data){try{var res=axios.post('http://'+config.thunderAccess+'/jsonrpc',JSON.stringify(data));}catch(err){console.error(err);}}

socket.onopen = function(e) {
	clearInterval(timerHandle);
	console.log("[socketOpen]: Connection established with Thunder running @ " + config.thunderAccess);
	/* Try activating plugins... */
	parseConfig(config);
	if (Array.isArray(activateRequests)){activateRequests.forEach(function(eventName,indexEvents){activatePlugin(eventName);});}
	/* Subscribe to Notifications after a timeout... */
	timerHandle = setInterval(function(socket, subscribeRequests){socket.emit('thunderresponse', socket, subscribeRequests);},500,socket,subscribeRequests);
};

socket.on('thunderresponse', function thunderresponse(socket, subscribeRequests) {
	clearInterval(timerHandle);
	var req = subscribeRequests.shift();
	if (req != undefined) {
		console.log("[thunderReq]: Sending " + JSON.stringify(req));
		socket.send(JSON.stringify(req));
		if (req.method.includes("unregister")) {
			totalSubscribedEvents--;
			if (totalSubscribedEvents == 0) {
				console.log("[socketClose]: Disconnecting from " + config.thunderAccess);
				socket.close();
				process.exit();
			}
		}
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

function doCleanUp() {
	console.log("[Interrupt!]: Triggering clean-up...");
	if (Array.isArray(config.subscribe)) {
		var idCount = 1;
		config.subscribe.forEach(function(plugin, indexPlugin){
			var callSign = plugin.pluginCallsign;
			if (Array.isArray(plugin.events)) {
				plugin.events.forEach(function(eventName, indexEvents){
					var data = {jsonrpc:'2.0',id:idCount, method:plugin.pluginCallsign + ".unregister", params:{event:eventName, id:"client.events."+idCount}};
					subscribeRequests.push(data);
					idCount++;
				});
			}
		});
	}
	socket.emit('thunderresponse', socket, subscribeRequests);
}

process.on('SIGINT', doCleanUp);
