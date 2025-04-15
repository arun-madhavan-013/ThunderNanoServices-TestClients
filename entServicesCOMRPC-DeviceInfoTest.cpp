#include <iostream>
#include <WPEFramework/com/com.h>
#include <WPEFramework/core/core.h>
#include "WPEFramework/interfaces/IDeviceInfo.h"

using namespace WPEFramework;

// RAII Wrapper for DeviceInfo
class DeviceInfoProxy {
    public:
        explicit DeviceInfoProxy(Exchange::IDeviceInfo* deviceInfo) : _deviceInfo(deviceInfo) {}
        ~DeviceInfoProxy() {
            if (_deviceInfo != nullptr) {
                std::cout << "Releasing DeviceInfo proxy..." << std::endl;
                _deviceInfo->Release();
            }
        }

        Exchange::IDeviceInfo* operator->() const { return _deviceInfo; }
        Exchange::IDeviceInfo* Get() const { return _deviceInfo; }

    private:
        Exchange::IDeviceInfo* _deviceInfo;
};

int main(void)
{
    /******************************************* Init *******************************************/
    // Get environment variables
    const char* thunderAccess = std::getenv("THUNDER_ACCESS");
    std::string envThunderAccess = (thunderAccess != nullptr) ? thunderAccess : "/tmp/communicator";
    std::cout << "Using THUNDER_ACCESS: " << envThunderAccess << std::endl;

    // Initialize COMRPC
    Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), envThunderAccess.c_str());
    Core::ProxyType<RPC::CommunicatorClient> client = Core::ProxyType<RPC::CommunicatorClient>::Create(
            Core::NodeId(envThunderAccess.c_str()));

    if (client.IsValid() == false) {
        std::cerr << "Failed to create COMRPC client." << std::endl;
        return 1;
    }

    /************************************* Plugin Connector **************************************/
    // Create a proxy for the DeviceInfo plugin
    Exchange::IDeviceInfo* rawDeviceInfo = client->Open<Exchange::IDeviceInfo>(_T("DeviceInfo"));
    if (rawDeviceInfo == nullptr) {
        std::cerr << "Failed to connect to DeviceInfo plugin." << std::endl;
        return 1;
    }
    std::cout << "Connected to DeviceInfo plugin." << std::endl;

    // Use RAII wrapper for DeviceInfo proxy
    DeviceInfoProxy deviceInfo(rawDeviceInfo);

    /************************************* Test All Methods **************************************/
    bool success = false;
    uint32_t result = Core::ERROR_NONE;

    std::string makeResponse;
    result = deviceInfo->Make(makeResponse, success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Make response: " << makeResponse << std::endl;
    } else {
        std::cerr << "Failed to get Make info. Error: " << result << std::endl;
    }

    /******************************************* Clean-Up *******************************************/
    // deviceInfo proxy destructor will automatically release the proxy
    std::cout << "Exiting..." << std::endl;
    return 0;
}
