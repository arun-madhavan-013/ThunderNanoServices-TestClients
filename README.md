## ThunderNanoServices-TestClient

CPP Test client to verify Thunder plugin generated events and methods.
Visit [Thunder](https://github.com/rdkcentral/Thunder) to know more...!!!

JavaScript test client uses `ws` module.

---

### How to

Sample usage of CPP Test Client `./ThunderEventListner THUNDER_ACCESS <DeviceIP:Port>`

Sample usage of JavaScript Test Client `nodejs thunderEventListnerJavaScriptClient.js`. Update the config.json with required details.

JavaScript Dependencies (Ubuntu):
```
sudo apt install npm
npm install
```

---

Sample: add listener on `NetworkControl` plugin `connectionchange` event.

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

<details>
  <summary>Click to see logs!</summary>

> root@raspberrypi4-64-rdke:/opt# ./ComRPCPluginTestDeviceInfoTest
> Using THUNDER_ACCESS: /tmp/communicator
> Connected to DeviceInfo plugin.
> Make response: RaspberryPi4
> Exiting...
> Releasing DeviceInfo proxy...
> root@raspberrypi4-64-rdke:/opt#
</details>

### Yocto recipe integration

<details>
  <summary>Click to see sample recipe file</summary>

```
DESCRIPTION = "Sample recipe for bitbake."
SECTION = "Apps"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

PV ?= "1.0.0"
PR ?= "r0"

S = "${WORKDIR}/git"
inherit cmake pkgconfig

SRC_URI = "git://github.com/arun-madhavan-013/ThunderNanoServices-TestClients;protocol=https;nobranch=1"
SRCREV = "${AUTOREV}"

TOOLCHAIN = "gcc"
DISTRO_FEATURES_CHECK = "wpe_r4_4 wpe_r4"

DEPENDS += "wpeframework rdkservices-apis wpeframework-tools-native"
RDEPENDS:${PN} += "wpeframework"

TARGET_LDFLAGS += " -Wl,--no-as-needed -Wl,--as-needed "

CXXFLAGS += " -Wall -Werror "
SELECTED_OPTIMIZATION:append = " -Wno-deprecated-declarations"

EXTRA_OECMAKE += " \
    -DBUILD_REFERENCE=${SRCREV} \
    -DBUILD_SHARED_LIBS=ON \
    -DDEVICEINFOTESTAPP=ON \
"

# ----------------------------------------------------------------------------

FILES_SOLIBSDEV = ""

INSANE_SKIP:${PN} += "libdir staticdev dev-so"
INSANE_SKIP:${PN}-dbg += "libdir"
```

</details>
