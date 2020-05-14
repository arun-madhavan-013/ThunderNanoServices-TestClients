#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <core/core.h>

using namespace std;
using namespace WPEFramework;

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
    static void onEventHandler(const Core::JSON::String& parameters) {
        std::string message;
        parameters.ToString(message);
        std::cout << "[FWCtrlEvt] " << __FUNCTION__ << ": " << message << std::endl;
    }
}

int main(int argc, char** argv)
{
    int retStatus = -1;
    JSONRPC::Client* remoteObject = NULL;
    std::string env, server, callsign, event;
    
    if (argc < 5) {
        showUsage(argv[0]);
    }

    for (int i = 0; i < argc; i++) {
        switch (i) {
            case 1: env = argv[i]; std::cout << "SetEnvironment is using :" << env << std::endl; break;
            case 2: server = argv[i]; std::cout << "Connect to server using :" << server << std::endl; break;
            case 3: callsign = argv[i]; std::cout << "Plugin callsign is :" << callsign << std::endl; break;
            case 4: event = argv[i]; std::cout << "Plugin event listening to is :" << event << std::endl; break;
            default: std::cout << "Will not use :" << argv[i] << std::endl; break;
        }
    }
    
    Core::SystemInfo::SetEnvironment(_T(env), (_T(server)));
    
    if (NULL == remoteObject) {
        remoteObject = new JSONRPC::Client(_T(callsign), _T(""));
        if (NULL == remoteObject) {
            std::cout << "JSONRPC::Client initialization failed" << std::endl;
        } else {
            /* Register handlers for Event reception. */
            if (remoteObject->Subscribe<Core::JSON::String>(1000, _T(event),
                        &Handlers::onEventHandler) == Core::ERROR_NONE) {
                std::cout << "Subscribed to event " << event << " with onEventHandler callback" << std::endl;
            } else {
                std::cout << "Failed to Subscribed to event" << event << std::endl;
            }
            /* Main loop */
            showMenu();
            /* Clean-Up */
            delete remoteObject;
        }
    }
    return 0;
}
