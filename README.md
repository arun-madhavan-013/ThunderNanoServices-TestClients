## ThunderNanoServices-TestClient  

CPP Test client to verify Thunder plugin generated events.  

This code has been written taking [ThunderNanoServices JSONRPCClient](https://github.com/rdkcentral/ThunderNanoServices/tree/master/examples/JSONRPCClient) as reference.

Visit [Thunder](https://github.com/rdkcentral/Thunder) and [ThunderNanoServices](https://github.com/rdkcentral/ThunderNanoServices) to know more...!!!

---  

### How to  

Sample usage `./ThunderEventListner THUNDER_ACCESS <LocalIP:Port> <PluginCallSign>.<PluginVersion> <EventName>`  

---

Sample: add listener on `NetworkControl` plugin `connectionchange` event.  

<details>
  <summary>Click to see logs!</summary>  
  
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
