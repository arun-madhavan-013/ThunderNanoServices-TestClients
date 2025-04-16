#ifndef MODULE_NAME
#define MODULE_NAME COMRPCTestApp
#endif

#include <iostream>
#include <WPEFramework/com/com.h>
#include <WPEFramework/core/core.h>
#include "WPEFramework/interfaces/IDisplayInfo.h"
#include <thread>
#include <chrono>
#include <atomic>

using namespace WPEFramework;

// RAII Wrapper for DisplayInfo
class DisplayInfoProxy {
    public:
        explicit DisplayInfoProxy(Exchange::IConnectionProperties* connectionProperties)
            : _connectionProperties(connectionProperties) {}
        ~DisplayInfoProxy() {
            if (_connectionProperties != nullptr) {
                std::cout << "Releasing DisplayInfo proxy..." << std::endl;
                _connectionProperties->Release();
            }
        }

        Exchange::IConnectionProperties* operator->() const { return _connectionProperties; }
        Exchange::IConnectionProperties* Get() const { return _connectionProperties; }

    private:
        Exchange::IConnectionProperties* _connectionProperties;
};

// Notification handler for DisplayInfo updates
class DisplayInfoNotification : public Exchange::IConnectionProperties::INotification {
    public:
        DisplayInfoNotification() : _refCount(0) {}
        ~DisplayInfoNotification() override = default;

        // Override the Updated method
        void Updated(const Source event) override {
            std::string eventName = EventToString(event);
            std::cout << "DisplayInfo updated notification received! Event: " << eventName << std::endl;
        }

        // Implement AddRef and Release methods
        void AddRef() const override {
            _refCount.fetch_add(1, std::memory_order_relaxed);
        }

        uint32_t Release() const override {
            uint32_t refCount = _refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
            if (refCount == 0) {
                delete this;
            }
            return refCount;
        }

        BEGIN_INTERFACE_MAP(DisplayInfoNotification)
            INTERFACE_ENTRY(Exchange::IConnectionProperties::INotification)
        END_INTERFACE_MAP

    private:
        // Helper function to map Source enum to string
        std::string EventToString(const Source event) const {
            switch (event) {
                case PRE_RESOLUTION_CHANGE: return "PreResolutionChange";
                case POST_RESOLUTION_CHANGE: return "PostResolutionChange";
                case HDMI_CHANGE: return "HdmiChange";
                case HDCP_CHANGE: return "HdcpChange";
                default: return "UnknownEvent";
            }
        }

        mutable std::atomic<uint32_t> _refCount; // Reference count for AddRef/Release
};

// Helper function to print results
template <typename T>
void PrintResult(const std::string& propertyName, uint32_t result, const T& value) {
    if (result == Core::ERROR_NONE) {
        std::cout << propertyName << ": " << value << std::endl;
    } else {
        std::cerr << "Failed to get " << propertyName << ". Error: " << result << std::endl;
    }
}

int main()
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
    // Create a proxy for the DisplayInfo plugin
    Exchange::IConnectionProperties* rawConnectionProperties = client->Open<Exchange::IConnectionProperties>(_T("DisplayInfo"));
    if (rawConnectionProperties == nullptr) {
        std::cerr << "Failed to connect to DisplayInfo plugin." << std::endl;
        return 1;
    }
    std::cout << "Connected to DisplayInfo plugin." << std::endl;

    // Use RAII wrapper for DisplayInfo proxy
    DisplayInfoProxy displayInfo(rawConnectionProperties);

    // Create and register the notification handler
    DisplayInfoNotification notificationHandler;
    uint32_t result = displayInfo->Register(&notificationHandler);
    if (result != Core::ERROR_NONE) {
        std::cerr << "Failed to register for DisplayInfo notifications. Error: " << result << std::endl;
    } else {
        std::cout << "Registered for DisplayInfo notifications." << std::endl;
    }

    /************************************* Test All Methods **************************************/
    bool isConnected = false;
    result = displayInfo->Connected(isConnected);
    PrintResult("HDMI Connection Status", result, (isConnected ? "Connected" : "Disconnected"));

    uint32_t width = 0, height = 0;
    result = displayInfo->Width(width);
    PrintResult("Display Width", result, width);

    result = displayInfo->Height(height);
    PrintResult("Display Height", result, height);

    /************************************* Wait for Events **************************************/
    std::atomic<bool> running(true);
    std::cout << "Listening for DisplayInfo events. Press Ctrl+C to exit..." << std::endl;

    // Wait loop to keep the program running and listen for events
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    /******************************************* Clean-Up *******************************************/
    // Unregister the notification handler
    result = displayInfo->Unregister(&notificationHandler);
    if (result != Core::ERROR_NONE) {
        std::cerr << "Failed to unregister from DisplayInfo notifications. Error: " << result << std::endl;
    } else {
        std::cout << "Unregistered from DisplayInfo notifications." << std::endl;
    }

    // DisplayInfo proxy destructor will automatically release the proxy
    std::cout << "Exiting..." << std::endl;
    return 0;
}
