## ThunderNanoServices-TestClient  

CPP Test client to verify Thunder plugin generated events.  

---  

### How to  

Sample usage `./ThunderEventListner THUNDER_ACCESS <LocalIP:Port> <PluginCallSign>.<PluginVersion> <EventName>`  
Sample usage to add listener on `NetworkControl` plugin `connectionchange` event.  

---  
> root@machine:# ./ThunderEventListner THUNDER_ACCESS 127.0.0.1:80 NetworkControl.1 connectionchange  
> SetEnvironment is using :THUNDER_ACCESS  
> Connect to server using :127.0.0.1:80  
> Plugin callsign is :NetworkControl.1  
> Plugin event listening to is :connectionchange  
>      L1 [11307]: "Message: {"id":1,"method":"NetworkControl.register","params":{ "event": "connectionchange", "id": ""}} send"  
> Subscribed to event connectionchange with onEventHandler callback  
> Waiting for event...  
> Press '0' to exit.  
> [WPEFW-JSONRPCEvt] : "{\"name\":\"wlan0\",\"address\":\"\",\"status\":\"updated\"}"  
> [WPEFW-JSONRPCEvt] : "{\"name\":\"eth0\",\"address\":\"\",\"status\":\"updated\"}"  
> [  553.066682@2] meson6-dwmac ff3f0000.ethernet eth0: Link is Up - 100Mbps/Full - flow control rx/tx  
> [WPEFW-JSONRPCEvt] : "{\"name\":\"eth0\",\"address\":\"\",\"status\":\"updated\"}"  
> [WPEFW-JSONRPCEvt] : "{\"name\":\"eth0\",\"address\":\"192.168.1.103\",\"status\":\"connected\"}"  
> 0  
>      L1 [11307]: "Message: {"id":2,"method":"NetworkControl.unregister","params":{ "event": "connectionchange", "id": ""}} send"  
> Unsubscribed from event connectionchange  
