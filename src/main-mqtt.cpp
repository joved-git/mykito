#include <iostream>
#include <cstring>
#include <stdlib.h>

#include "../include/MyMosq.h"

#define VER "1.1.9"

using namespace std;

int main(int argc, char *argv[])
{
    char mess[50];                              // Test message.
    char host[50];                              // Host hostname.
    char topic[200];                            // Topic name.
    char id[32];                                // The id of the MQTT object.
    bool end=false;                             // End of the road. See bellow.

    int mode=PUB;                               // The default mode.
    int port=1883;                              // The default port.
    strcpy(topic, "topic");                     // The default topic.
    strcpy(host, "localhost");                  // The default host.
    strcpy(mess, "hello");                      // The default message.
    strcpy(id, "mqtt-pub");                     // The default id (pub).

    std::cout << "MQTT [pub/sub]sciptor. Ver " << VER << " - (2019) by Joved" << std::endl;
    std::cout << "Usage: mykito [-h <host, def:localhost>] [-p <port, def:1883>] [-t <topic, def:topic>] [-d <mode (pub|sub), def:pub]" << std::endl;
    std::cout << std::endl;

    // Parse parameters.
    for (int i=0; i<argc; i++) {
    #ifdef DEBUG2
        printf("%d %s\n", i, argv[i]);
    #endif

        // Find the host.
        if (!strcmp(argv[i], "-h")) {
            strcpy(host, argv[++i]);
        }

        // Find the port.
        if (!strcmp(argv[i], "-p")) {
            port=atoi(argv[++i]);
        }

        // Find the topic.
        if (!strcmp(argv[i], "-t")) {
            strcpy(topic, argv[++i]);
        }

        // Find the message.
        if (!strcmp(argv[i], "-m")) {
            strcpy(mess, argv[++i]);
        }

        // Find the mode.
        if (!strcmp(argv[i], "-d"))  {
            if (!strcmp(argv[++i], "sub")) {
                mode=SUB;
                strcpy(id, "mqtt-sub");
            }
        }
    }

    // Print information.
    std::cout << "host : " <<  host << std::endl;
    std::cout << "port : " <<  port << std::endl;
    std::cout << "topic: " << topic << std::endl;
    std::cout << "mess : " << mess << std::endl;
    std::cout << "id   : " << id << std::endl;

    if (mode==SUB) {
        std::cout << "mode : SUB" << std::endl << std::endl;
        std::cout << "All is good. So listening topic [" << topic << "]..." << std::endl;
        std::cout << "I quit if I receive \"quitnow\" message..." << std::endl;
    }
    else {
        std::cout << "mode : PUB" << std::endl;
        std::cout << "Sending <" << mess << "> to topic [" << topic << "]..." << std::endl;
    }
    
    // Create the MQTT objet and set the mode.
    MyMosq myMosq(id, topic, host, port);
    myMosq.setMode(mode);
    
    // Enter to the main loop (pub or sub).
    switch (mode) {
        case PUB:
            // Send the first message and ask for a new one. "Quit" for quit the application.
            while (!end) {
                myMosq.sendMessage(mess);                               // Send default message.
                end=myMosq.haveToQuit();                                // Is this the end ?

                if (!end) {                                             // No, we continue...
                    printf("Please type a new message (or type \"quitnow\" to quit) >>> ");
                    scanf("%s", mess);
                }
            }
        break;

        case SUB:
            // If a message was receive, print it. Quit if "quitnow" is received.
            while (!end) {
                if (myMosq.isMessageReceived()) {                       // Is a message received ?
                    myMosq.clearMessageNotification();                  // yes, I see and print it.

                    std::cout << "Receiving message [" << myMosq.getMessage() << "] on the topic [" << topic << "]..." << std::endl;
                }

                end=myMosq.haveToQuit();                                // Is this the end ?
            }
        break;
    }

    return(0);
}
