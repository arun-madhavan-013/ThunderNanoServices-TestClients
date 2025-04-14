#include <com/com.h>
#include <core/core.h>
#include <iostream>
#include "IFrameRate.h"

using namespace WPEFramework;

int main()
{
	/******************************************* Init *******************************************/
	// Get environment variables
	static char* envThunderAccess = std::getenv("THUNDER_ACCESS");
	if (envThunderAccess != nullptr) {
		std::cout << "THUNDER_ACCESS: " << envThunderAccess << std::endl;
	} else {
		std::cout << "THUNDER_ACCESS env not set, using default: /tmp/communicator" << std::endl;
		envThunderAccess = "/tmp/communicator";
	}
    // Initialize COMRPC
    Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), envThunderAccess);
    Core::ProxyType<RPC::CommunicatorClient> client = Core::ProxyType<RPC::CommunicatorClient>::Create(
        Core::NodeId(envThunderAccess));

    if (client.IsValid() == false) {
        std::cerr << "Failed to create COMRPC client." << std::endl;
        return 1;
    }

	/************************************* Plugin Connector **************************************/
    // Create a proxy for the FrameRate plugin
    Exchange::IFrameRate* frameRate = client->Open<Exchange::IFrameRate>(_T("FrameRate"));
    if (frameRate == nullptr) {
        std::cerr << "Failed to connect to FrameRate plugin." << std::endl;
        return 1;
    }
	std::cout << "Connected to FrameRate plugin." << std::endl;

	/************************************ Subscribe to Events ************************************/

	/************************************* Test All Methods **************************************/
	// Query current frame rate mode - GetFrmMode method
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
	/******************************************* Clean-Up *******************************************/
    // Release the proxy
	std::cout << "Cleaning-up ..." << std::endl;
    frameRate->Release();

    return 0;
}
