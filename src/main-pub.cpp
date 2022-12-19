#include <iostream>
#include <cstring>
#include <stdlib.h>

#include "../include/MyMosq.h"

#define VER "0.9.2"

using namespace std;

int main(int argc, char *argv[])
{
    int mode=PUB;
    char mess[50];
    char host[50];
    char topic[200];
    bool end=false;

    int port=1883;                              // The default port.
    strcpy(topic, "topic");                     // The default topic.
    strcpy(host, "localhost");                  // The default host.
    strcpy(mess, "hello");                      // The default message.

    cout << "MQTT publiqher. Ver " << VER << endl;
    cout << "Usage: mqtt-pub [-h <host, def:localhost>] [-p <port, def:1883>] [-t <topic, def:topic>] [-m <message, def:hello>]" << endl;
    cout << endl;

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
    }

    //#ifdef DEBUG
    printf("host : %s\n", host);
    printf("port : %d\n", port);
    printf("topic: [%s]\n", topic);
    printf("mess : [%s]\n", mess);
    //#endif
    
    // Create the MQTT objet.
    MyMosq pubMosq("mymosq-pub", topic, host, port);

    switch (mode) {
        case PUB:
            while (!end) {
                if (!strcmp(mess, "quit")) {
                    end=true;
                }
                else {
#ifdef DEBUG
                    cout << "Try to Send message [" << mess << "]..." << endl;
#endif
                    pubMosq.sendMessage(mess);

                    printf("Please type a new message (or quit to quit) >>> ");
                    scanf("%s", mess);
                }
            }
        break;

        case SUB:
            cout << "SUB SUB SUB........................" << endl;
            //pubMosq.subscribeTopic();

            while (!end) {
#ifdef DEBUG
                    //cout << "Try to Send message [" << mess << "]..." << endl;
#endif
            }
        break;
    }
    return(0);

}