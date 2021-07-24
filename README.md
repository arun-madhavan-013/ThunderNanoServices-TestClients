## ThunderNanoServices-TestClient

CPP Test client to verify Thunder plugin generated events has been written taking [ThunderNanoServices JSONRPCClient](https://github.com/rdkcentral/ThunderNanoServices/tree/master/examples/JSONRPCClient) as reference.

Visit [Thunder](https://github.com/rdkcentral/Thunder) and [ThunderNanoServices](https://github.com/rdkcentral/ThunderNanoServices) to know more...!!!

JavaScript test client uses `ws` module.

---  

### How to  

Sample usage of CPP Test Client `./ThunderEventListner THUNDER_ACCESS <DeviceIP:Port> <PluginCallSign>.<PluginVersion> <EventName>`  

Sample usage of JavaScript Test Client `nodejs thunderEventListnerJavaScriptClient.js`. Update the config.json with required details.

JavaScript Dependencies (Ubuntu):
```
sudo apt install npm
npm install ws
```
(Optional)
```
npm install --save-optional bufferutil utf-8-validate
```  

---

Sample: add listener on `NetworkControl` plugin `connectionchange` event.  

<details>
  <summary>Click to see CPP ThunderEventListner logs!</summary>  
  
  > root@device:# ./ThunderEventListner THUNDER_ACCESS 127.0.0.1:80 NetworkControl connectionchange  
  > SetEnvironment is using :THUNDER_ACCESS  
  > Connect to server using :127.0.0.1:80  
  > Plugin callsign is :NetworkControl  
  > Plugin event listening to is :connectionchange  
  >      L1 [8014]: "Message: {"id":1,"method":"NetworkControl.register","params":{ "event": "connectionchange", "id": ""}} send"  
  > [2020-05-26 15:20:16.823] Subscribed to event connectionchange with onEventHandler callback  
  > Waiting for event...  
  > Press '0' to exit.  
  > [  130.513994@2] eth0: Link is Down  
  > [WPEFW-JSONRPCEvt][2020-05-26 15:20:26.232] : "{\"name\":\"eth0\",\"address\":\"\",\"status\":\"updated\"}"  
  > [  136.658030@2] eth0: Link is Up - 100Mbps/Full - flow control rx/tx  
  > [WPEFW-JSONRPCEvt][2020-05-26 15:20:32.369] : "{\"name\":\"eth0\",\"address\":\"\",\"status\":\"updated\"}"  
  > [WPEFW-JSONRPCEvt][2020-05-26 15:20:32.882] : "{\"name\":\"eth0\",\"address\":\"192.168.1.102\",\"status\":\"connected\"}"  
  > [  148.945993@2] eth0: Link is Down  
  > [WPEFW-JSONRPCEvt][2020-05-26 15:20:44.664] : "{\"name\":\"eth0\",\"address\":\"\",\"status\":\"updated\"}"  
  > [  152.018034@2] eth0: Link is Up - 100Mbps/Full - flow control rx/tx  
  > [WPEFW-JSONRPCEvt][2020-05-26 15:20:47.729] : "{\"name\":\"eth0\",\"address\":\"\",\"status\":\"updated\"}"  
  > [WPEFW-JSONRPCEvt][2020-05-26 15:20:47.831] : "{\"name\":\"eth0\",\"address\":\"192.168.1.102\",\"status\":\"connectionfailed\"}"  
  > [WPEFW-JSONRPCEvt][2020-05-26 15:20:48.783] : "{\"name\":\"eth0\",\"address\":\"192.168.1.104\",\"status\":\"connected\"}"  
  > 0    
  >      L1 [11307]: "Message: {"id":2,"method":"NetworkControl.unregister","params":{ "event": "connectionchange", "id": ""}} send"    
  > [WPEFW-JSONRPCEvt][2020-05-26 15:21:53.128] Unsubscribed from event connectionchange  
</details>  

<details>
  <summary>Click to see JavaScript in action!</summary>

  > d35@d35:$ nodejs thunderEventListnerJavaScriptClient.js 
  > [socketOpen]: Connection established with Thunder running @ 192.168.0.16:9998 
  > [configData]: {\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"org.rdk.RDKShell.1.register\",\"params\":{\"event\":\"onSuspend\",\"id\":\"client.events.1\"}}
  > [configData]: {\"jsonrpc\":\"2.0\",\"id\":2,\"method\":\"org.rdk.HdcpProfile.1.register\",\"params\":{\"event\":\"onDisplayConnectionChanged\",\"id\":\"client.events.2\"}}
  > [configData]: {\"jsonrpc\":\"2.0\",\"id\":3,\"method\":\"org.rdk.Network.1.register\",\"params\":{\"event\":\"onConnectionStatusChanged\",\"id\":\"client.events.3\"}}
  > [configData]: {\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"org.rdk.Network.1.register\",\"params\":{\"event\":\"onDefaultInterfaceChanged\",\"id\":\"client.events.4\"}}
  > [configData]: {\"jsonrpc\":\"2.0\",\"id\":5,\"method\":\"org.rdk.Network.1.register\",\"params\":{\"event\":\"onInterfaceStatusChanged\",\"id\":\"client.events.5\"}}
  > [thunderReq]: Subscribing {\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"org.rdk.RDKShell.1.register\",\"params\":{\"event\":\"onSuspend\",\"id\":\"client.events.1\"}}
  > [thunderRsp]: {\"jsonrpc\":\"2.0\",\"id\":1,\"result\":0}
  > [thunderReq]: Subscribing {\"jsonrpc\":\"2.0\",\"id\":2,\"method\":\"org.rdk.HdcpProfile.1.register\",\"params\":{\"event\":\"onDisplayConnectionChanged\",\"id\":\"client.events.2\"}}
  > [thunderRsp]: {\"jsonrpc\":\"2.0\",\"id\":2,\"result\":0}
  > [thunderReq]: Subscribing {\"jsonrpc\":\"2.0\",\"id\":3,\"method\":\"org.rdk.Network.1.register\",\"params\":{\"event\":\"onConnectionStatusChanged\",\"id\":\"client.events.3\"}}
  > [thunderRsp]: {\"jsonrpc\":\"2.0\",\"id\":3,\"result\":0}
  > [thunderReq]: Subscribing {\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"org.rdk.Network.1.register\",\"params\":{\"event\":\"onDefaultInterfaceChanged\",\"id\":\"client.events.4\"}}
  > [thunderRsp]: {\"jsonrpc\":\"2.0\",\"id\":4,\"result\":0}
  > [thunderReq]: Subscribing {\"jsonrpc\":\"2.0\",\"id\":5,\"method\":\"org.rdk.Network.1.register\",\"params\":{\"event\":\"onInterfaceStatusChanged\",\"id\":\"client.events.5\"}}
  > [thunderRsp]: {\"jsonrpc\":\"2.0\",\"id\":5,\"result\":0}
  > [thunderNow]: Awaiting events...
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.3.onConnectionStatusChanged\",\"params\":{\"interface\":\"ETHERNET\",\"status\":\"DISCONNECTED\"}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.4.onDefaultInterfaceChanged\",\"params\":{\"oldInterfaceName\":\"ETHERNET\",\"newInterfaceName\":\"\"}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.3.onConnectionStatusChanged\",\"params\":{\"interface\":\"ETHERNET\",\"status\":\"CONNECTED\"}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.4.onDefaultInterfaceChanged\",\"params\":{\"oldInterfaceName\":\"\",\"newInterfaceName\":\"ETHERNET\"}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.2.onDisplayConnectionChanged\",\"params\":{\"HDCPStatus\":{\"isConnected\":false,\"isHDCPCompliant\":false,\"isHDCPEnabled\":false,\"hdcpReason\":2,\"supportedHDCPVersion\":\"2.2\",\"receiverHDCPVersion\":\"1.4\",\"currentHDCPVersion\":\"1.4\"}}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.2.onDisplayConnectionChanged\",\"params\":{\"HDCPStatus\":{\"isConnected\":false,\"isHDCPCompliant\":false,\"isHDCPEnabled\":false,\"hdcpReason\":2,\"supportedHDCPVersion\":\"2.2\",\"receiverHDCPVersion\":\"1.4\",\"currentHDCPVersion\":\"1.4\"}}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.2.onDisplayConnectionChanged\",\"params\":{\"HDCPStatus\":{\"isConnected\":false,\"isHDCPCompliant\":false,\"isHDCPEnabled\":false,\"hdcpReason\":2,\"supportedHDCPVersion\":\"2.2\",\"receiverHDCPVersion\":\"1.4\",\"currentHDCPVersion\":\"1.4\"}}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.2.onDisplayConnectionChanged\",\"params\":{\"HDCPStatus\":{\"isConnected\":true,\"isHDCPCompliant\":true,\"isHDCPEnabled\":false,\"hdcpReason\":2,\"supportedHDCPVersion\":\"2.2\",\"receiverHDCPVersion\":\"1.4\",\"currentHDCPVersion\":\"1.4\"}}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.2.onDisplayConnectionChanged\",\"params\":{\"HDCPStatus\":{\"isConnected\":true,\"isHDCPCompliant\":true,\"isHDCPEnabled\":true,\"hdcpReason\":2,\"supportedHDCPVersion\":\"2.2\",\"receiverHDCPVersion\":\"1.4\",\"currentHDCPVersion\":\"1.4\"}}}
  > [thunderEvt]: {\"jsonrpc\":\"2.0\",\"method\":\"client.events.2.onDisplayConnectionChanged\",\"params\":{\"HDCPStatus\":{\"isConnected\":true,\"isHDCPCompliant\":true,\"isHDCPEnabled\":true,\"hdcpReason\":2,\"supportedHDCPVersion\":\"2.2\",\"receiverHDCPVersion\":\"1.4\",\"currentHDCPVersion\":\"1.4\"}}}
  > 
</details>

---

Sample: add listener on `FirmwareControl` plugin `upgradeprogress` event.  

<details>
  <summary>Click to see logs!</summary>  
  
> root@device:# ./ThunderEventListner THUNDER_ACCESS 127.0.0.1:80 FirmwareControl upgradeprogress  
> SetEnvironment is using :THUNDER_ACCESS  
> Connect to server using :127.0.0.1:80  
> Plugin callsign is :FirmwareControl  
> Plugin event listening to is :upgradeprogress  
>   L1 [11195]: "Message: {"id":1,"method":"FirmwareControl.register","params":{ "event": "upgradeprogress", "id": ""}} send"  
> [2020-05-26 14:37:13.65] Subscribed to event upgradeprogress with onEventHandler callback  
> Waiting for event...  
> Press '0' to exit.  
> [WPEFW-JSONRPCEvt][2020-05-26 14:38:20.147] : "{\"status\":\"downloadstarted\",\"error\":\"unkown\",\"percentage\":0}" 
> [WPEFW-JSONRPCEvt][2020-05-26 14:55:30.934] : "{\"status\":\"downloadcompleted\",\"error\":\"none\",\"percentage\":0}"  
> [WPEFW-JSONRPCEvt][2020-05-26 14:55:34.930] : "{\"status\":\"installstarted\",\"error\":\"none\",\"percentage\":70}"  
> [WPEFW-JSONRPCEvt][2020-05-26 14:57:34.938] : "{\"status\":\"installstarted\",\"error\":\"none\",\"percentage\":70}"  
> [WPEFW-JSONRPCEvt][2020-05-26 14:57:35.116] : "{\"status\":\"upgradecompleted\",\"error\":\"none\",\"percentage\":100}"  
</details>  

### Yocto recipe integration   

<details>
  <summary>Click to see sample recipe file</summary>  
  
```
DESCRIPTION = "Sample recipe for bitbake."
SECTION = "Apps"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRCREV = "${AUTOREV}"

SRC_URI = "git://github.com/arun-madhavan-013/ThunderNanoServices-TestClients.git;protocol=https;branch=master"

S = "${WORKDIR}/git"
inherit pkgconfig cmake
```

</details>  
