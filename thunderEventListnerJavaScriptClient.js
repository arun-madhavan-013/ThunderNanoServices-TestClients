var configFile = "./config.json";
var myArgs = process.argv.slice(2);

if (myArgs[0]) {
	configFile=myArgs[0];
}
const WebSocket = require('ws');
const axios = require('axios');
const fs = require('fs');
const { PNG } = require('pngjs');

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
var fileID = 1;
var displayWidth = 1920;
var displayHeight = 1080;

async function fetchDisplayResolution() {
	try {
		var url = 'http://' + config.thunderAccess + '/jsonrpc';
		var wRes = await axios.post(url, {jsonrpc:'2.0', id:21, method:'org.rdk.DisplayInfo.width'});
		var hRes = await axios.post(url, {jsonrpc:'2.0', id:13, method:'org.rdk.DisplayInfo.height'});
		if (wRes.data && wRes.data.result) { displayWidth  = wRes.data.result; }
		if (hRes.data && hRes.data.result) { displayHeight = hRes.data.result; }
		console.log('[displayInfo]: Resolution ' + displayWidth + 'x' + displayHeight);
	} catch (err) {
		console.log('[displayInfo]: Failed to fetch resolution, defaulting to ' + displayWidth + 'x' + displayHeight + ' (' + err.message + ')');
	}
}

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
	clearTimeout(timerHandle);
	console.log("[socketOpen]: Connection established with Thunder running @ " + config.thunderAccess);
	/* Try activating plugins... */
	parseConfig(config);
	if (Array.isArray(activateRequests)){activateRequests.forEach(function(eventName,indexEvents){activatePlugin(eventName);});}
	/* Fetch display resolution, then subscribe to Notifications after a timeout... */
	fetchDisplayResolution().then(function() {
		timerHandle = setTimeout(function(socket, subscribeRequests){socket.emit('thunderresponse', socket, subscribeRequests);},500,socket,subscribeRequests);
	});
};

socket.on('thunderresponse', function thunderresponse(socket, subscribeRequests) {
	clearTimeout(timerHandle);
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
		// if its onScreenshotComplete; then save imageData as a file. (Eg: screenshot.png)
		if (data.method && data.method.includes("onScreenshotComplete") && data.params && data.params.success && data.params.imageData) {
			var fileName = "screenshot" + fileID++ + ".png";
			var { imageData, width = displayWidth, height = displayHeight } = data.params;
			var rawBuffer = Buffer.from(imageData, 'base64');
			/* Raw buffer is vertically flipped (bottom-to-top) — reverse row order to correct */
			var flipped = Buffer.alloc(rawBuffer.length);
			var rowBytes = width * 4;
			for (var y = 0; y < height; y++) {
				rawBuffer.copy(flipped, (height - 1 - y) * rowBytes, y * rowBytes, (y + 1) * rowBytes);
			}
			var png = new PNG({ width, height });
			flipped.copy(png.data);
			fs.writeFile(fileName, PNG.sync.write(png), function(err) {
				if (err) {
					console.log("[fileError]: " + err);
				} else {
					console.log("[fileSuccess]: Screenshot saved as " + fileName + " (" + width + "x" + height + ")");
				}
			});
		} else {
			console.log("[thunderEvt]: " + JSON.stringify(data));
		}
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
