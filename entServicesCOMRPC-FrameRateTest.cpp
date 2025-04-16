#ifndef MODULE_NAME
#define MODULE_NAME COMRPCTestApp
#endif

#include <iostream>
#include <WPEFramework/com/com.h>
#include <WPEFramework/core/core.h>
#include "WPEFramework/interfaces/IFrameRate.h"

using namespace WPEFramework;

// RAII Wrapper for IFrameRate
class FrameRateProxy {
    public:
        explicit FrameRateProxy(Exchange::IFrameRate* frameRate) : _frameRate(frameRate) {}
        ~FrameRateProxy() {
            if (_frameRate != nullptr) {
                std::cout << "Releasing FrameRate proxy..." << std::endl;
                _frameRate->Release();
            }
        }

        Exchange::IFrameRate* operator->() const { return _frameRate; }
        Exchange::IFrameRate* Get() const { return _frameRate; }

    private:
        Exchange::IFrameRate* _frameRate;
};

/********************************* Test All IFrameRate Events **********************************/
class FrameRateEventHandler : public Exchange::IFrameRate::INotification {
    public:
        // Handle FPS event
        void OnFpsEvent(int average, int min, int max) override {
            std::cout << "FPS Event - Average: " << average << ", Min: " << min << ", Max: " << max << std::endl;
        }

        // Handle display frame rate changing event
        void OnDisplayFrameRateChanging(const std::string& displayFrameRate) override {
            std::cout << "Display Frame Rate Changing to: " << displayFrameRate << std::endl;
        }

        // Handle display frame rate changed event
        void OnDisplayFrameRateChanged(const std::string& displayFrameRate) override {
            std::cout << "Display Frame Rate Changed to: " << displayFrameRate << std::endl;
        }

        BEGIN_INTERFACE_MAP(FrameRateEventHandler)
            INTERFACE_ENTRY(Exchange::IFrameRate::INotification)
        END_INTERFACE_MAP
};

int main(void)
{
    /******************************************* Init *******************************************/
    // Get environment variables
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
    // Create a proxy for the FrameRate plugin
    Exchange::IFrameRate* rawFrameRate = client->Open<Exchange::IFrameRate>(_T("FrameRate"));
    if (rawFrameRate == nullptr) {
        std::cerr << "Failed to connect to FrameRate plugin." << std::endl;
        return 1;
    }
    std::cout << "Connected to FrameRate plugin." << std::endl;

    // Use RAII wrapper for FrameRate proxy
    FrameRateProxy frameRate(rawFrameRate);

    /************************************ Subscribe to Events ************************************/
    FrameRateEventHandler eventHandler;
    frameRate->Register(&eventHandler);
    std::cout << "Event handler registered." << std::endl;

    /************************************* Test All Methods **************************************/
    bool success = false;
    int frmmode = 0;

    // Gets the Display Frame Rate - GetDisplayFrameRate method
    uint32_t result = frameRate->GetDisplayFrameRate(frmmode, success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Current Display Frame Rate: " << frmmode << std::endl;
    } else {
        std::cerr << "Failed to get display frame rate. Error: " << result << std::endl;
    }

    // Gets framerate mode - GetFrmMode method
    result = frameRate->GetFrmMode(frmmode, success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Current Frame Mode - Enabled AutoFrameRate: " << frmmode << std::endl;
    } else {
        std::cerr << "Failed to get frame mode. Error: " << result << std::endl;
    }

    // Sets the FPS data collection interval - SetCollectionFrequency method
    int frequency = 30;
    result = frameRate->SetCollectionFrequency(frequency, success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Set Collection Frequency: " << frequency << std::endl;
    } else {
        std::cerr << "Failed to set collection frequency. Error: " << result << std::endl;
    }

    // Sets the display framerate values - SetDisplayFrameRate method
    const char* displayFrameRate = "60";
    result = frameRate->SetDisplayFrameRate(displayFrameRate, success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Set Display Frame Rate: " << displayFrameRate << std::endl;
    } else {
        std::cerr << "Failed to set display frame rate. Error: " << result << std::endl;
    }

    // Sets the auto framerate mode - SetFrmMode method
    int autoFrameRate = 1;
    result = frameRate->SetFrmMode(autoFrameRate, success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Set Auto Frame Rate Mode: " << autoFrameRate << std::endl;
    } else {
        std::cerr << "Failed to set auto frame rate mode. Error: " << result << std::endl;
    }

    // Starts the FPS data collection - StartFpsCollection method
    result = frameRate->StartFpsCollection(success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Started FPS data collection." << std::endl;
    } else {
        std::cerr << "Failed to start FPS data collection. Error: " << result << std::endl;
    }

    // Stops the FPS data collection - StopFpsCollection method
    result = frameRate->StopFpsCollection(success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Stopped FPS data collection." << std::endl;
    } else {
        std::cerr << "Failed to stop FPS data collection. Error: " << result << std::endl;
    }

    // Update the FPS values - UpdateFps method
    int fps = 60;
    result = frameRate->UpdateFps(fps, success);
    if (result == Core::ERROR_NONE && success) {
        std::cout << "Updated FPS: " << fps << std::endl;
    } else {
        std::cerr << "Failed to update FPS. Error: " << result << std::endl;
    }

	/************************************ Wait for Notifications ************************************/

    std::cout << "Waiting for events... Press Ctrl+C to exit." << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    /******************************************* Clean-Up *******************************************/
    // FrameRateProxy destructor will automatically release the proxy
    std::cout << "Exiting..." << std::endl;
    frameRate->Unregister(&eventHandler);
    return 0;
}
