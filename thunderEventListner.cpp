#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <core/core.h>
#include <websocket/websocket.h>

using namespace std;
using namespace WPEFramework;

std::string TimeStamp(void)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) -
                  std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    std::stringstream timeNow;
    timeNow << std::put_time(std::localtime(&time), "%F %T.") << ms.count();
    return (timeNow.str());
}

void showMenu(void)
{
    int input = 1;
    std::cout << "Waiting for event..." << std::endl;
    std::cout << "Press '0' to exit." << std::endl;
    do {
        std::cin >> input;
    } while (input);
}

void showUsage(char *pName)
{
    std::cout << pName << " <Environment> <ip:port> <callSign> <event>" << std::endl;
    std::cout << pName << " THUNDER_ACCESS 127.0.0.1:80 testPlugin testEvent" << std::endl;
    exit(0);
}

/* This section is related to the event handler implementation for Thunder Plugin Events. */
namespace Handlers {
    /* Event Handlers */
    static void onEventHandler(const JsonObject& parameters) {
        std::string message;
        parameters.ToString(message);
        std::cout << "[WPEFW-JSONRPCEvt][" << TimeStamp() << "] : " << message << std::endl;
    }
}

int main(int argc, char** argv)
{
    int retStatus = -1;
    std::string env, server, callsign, event;
    
    if (argc < 5) {
        showUsage(argv[0]);
    }

    for (int i = 0; i < argc; i++) {
        switch (i) {
            case 0: break;
            case 1: env = argv[i]; std::cout << "SetEnvironment is using :" << env << std::endl; break;
            case 2: server = argv[i]; std::cout << "Connect to server using :" << server << std::endl; break;
            case 3: callsign = argv[i]; std::cout << "Plugin callsign is :" << callsign << std::endl; break;
            case 4: event = argv[i]; std::cout << "Plugin event listening to is :" << event << std::endl; break;
            default: std::cout << "Will not use :" << argv[i] << std::endl; break;
        }
    }

    Core::SystemInfo::SetEnvironment(_T(env), (_T(server)));
    JSONRPC::LinkType<Core::JSON::IElement> *remoteObject = new JSONRPC::LinkType<Core::JSON::IElement>(_T(callsign), _T(""));

    if (remoteObject) {
        /* Register handlers for Event reception. */
        if (remoteObject->Subscribe<JsonObject>(1000, _T(event), &Handlers::onEventHandler) == Core::ERROR_NONE) {
            std::cout << "[" << TimeStamp() << "] Subscribed to event " << event << " with onEventHandler callback" << std::endl;

            /* Main loop */
            showMenu();

            /* Clean-Up */
            remoteObject->Unsubscribe(1000, _T(event));
            std::cout << "[" << TimeStamp() << "] Unsubscribed from event " << event << std::endl;
        } else {
            std::cout << "[" << TimeStamp() << "] Failed to Subscribed to event" << event << std::endl;
        }
        delete remoteObject;
    } else {
        std::cout << "[" << TimeStamp() << "] remoteObject creation failed" << std::endl;
    }
    return 0;
}
