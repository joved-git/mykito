#include <iostream>
#include <cstring>
#include "../include/MyMosq.h"

using namespace std;

// Constructor with parameters.
// 
// const char *: the Id of the sub or pub.
// const char *: the topic.
// const char *: the host of the broker.
// int: the port
MyMosq::MyMosq(const char *pId, const char *pTopic, const char *pHost, int pPort) : 
    mosqpp::mosquittopp(pId),
    mKeepAlive(60),
    mId(pId),
    mPort(pPort),
    mHost(pHost),
    mTopic(pTopic),
    mMessageReceived(false),
    mHaveToQuit(false)

{
#ifdef DEBUG
    std::cout << std::endl << "dbg - Create MQTT objet..." << std::endl;
#endif
    mosqpp::lib_init();             // Mandatory initialization for mosquitto library
    //this->mKeepAlive=60;            // Basic configuration setup for myMosq class
    //this->mId=pId;                  // id: id/name of the object.
    //this->mPort=pPort;              // port: the port the broker uses.
    //this->mHost=pHost;              // host: name of the broker.
    //this->mTopic=pTopic;            // topic: the topic, example "root/sensor/temp".
    //this->mMessageReceived=false;   // Not yet message received.
    //this->mHaveToQuit=false;        // For now, Don't quit the application.
    
    
    // non blocking connection to broker request
    connect_async(mHost, mPort, mKeepAlive);
    
    loop_start();                   // Start thread managing connection / publish / subscribe
}

// Destructor.
//
MyMosq::~MyMosq()
{
#ifdef DEBUG
    cout << std::endl << "dbg - Delete MQTT objet..." << endl;
#endif

    loop_stop(true);                    // Kill the thread.

#ifdef DEBUG
    cout << std::endl << "dbg - After loop_Stop()..." << endl;
#endif

    mosqpp::lib_cleanup();          // Mosquitto library cleanup.
}

// Object send message
//
// const char *: the message to be sent.
// ---
// Return - bool: if message is correctly sent or not.
bool MyMosq::sendMessage(const char *pMessage)
{
    // * NULL : Message Id (int *) this allow to latter get status of each message
    // * topic : topic to be used
    // * lenght of the message
    // * message
    // * qos (0,1,2)
    // * retain (boolean) - indicates if message is retained on broker or not
    //     Should return MOSQ_ERR_SUCCESS

    int ret=publish(NULL, this->mTopic, strlen(pMessage), pMessage, 1, false);

    // Is this the quit message ?
    if (!strcmp(pMessage, "quitnow")) {
        mHaveToQuit=true;
    }    

    return (ret==MOSQ_ERR_SUCCESS);
}

// Trigger once when the object is disconnecting to the host.
//
// int: the return code of this deconenction.
// ---
// Return - nothing
void MyMosq::on_disconnect(int pRetCode) 
{
#ifdef DEBUG
    std::cout << std::endl << "dgb - myMosq - disconnection(" << pRetCode << ")" << std::endl;
#endif
}

// Trigger once when the object is connecting to the host.
//
// int: the return code of this connection.
// ---
// Return - nothing
void MyMosq::on_connect(int pRetCode)
{
    if (pRetCode==0) {
        //std::string host=mHost;
        std::cout << std::endl << "MyMosq - Connected with server [" << mHost << "]" << std::endl;

        if (this->mMode==SUB) 
        {
#ifdef DEBUG
        std::cout << std::endl << "dbg - Subscribe to [" << mTopic << "]..............." << std::endl;
#endif
        // In SUB mode, we are subscribing to a topic.
        subscribe(NULL, mTopic, 1);
        }
    } 
    else {
        std::cout << std::endl << "MyMosq - Impossible to connect with server(" << pRetCode << ")" << std::endl;
    }
}

// Trigger when the object is publishing.
//
// int: the return code of this publication.
// ---
// Return - nothing
void MyMosq::on_publish(int pMid)
{
#ifdef DEBUG
    std::cout << std::endl << "dbg - MyMosq - Message (" << pMid << ") succeed to be published " << std::endl;
#endif
}

// Trigger when the object is receiving a message.
//
// const struct mosquitto_message *: message informations.
// ---
// Return - nothing
void MyMosq::on_message(const struct mosquitto_message *pMessage)
{
#ifdef DEBUG
    std::cout << std::endl << "dbg - MyMosq - on_message()" << std::endl;
#endif
    mMessage=((char *) (pMessage->payload));
    mMessageReceived=true;

    // Is this the quit message ?
    if (mMessage=="quitnow") {
        mHaveToQuit=true;
    }

#ifdef DEBUG
    std::cout << "Receiving message [" << mMessage << "] on the topic [" << mTopic << "]..." << std::endl;
#endif
}

// Set the mode (PUB or SUB)
//
// int: the mode (PUB or SUB).
// ---
// Return - nothing
void MyMosq::setMode(int pMode)
{
    mMode=pMode;
}

// Set the mode (PUB or SUB).
//
// No IN params
// ---
// Return - int: the mode (PUB or SUB).
int MyMosq::getMode()
{
    return(mMode);
}

// Have we received a message ?
//
// No IN params
// ---
// Return - bool: message received or not.
bool MyMosq::isMessageReceived()
{
    return(mMessageReceived);
}

// Clear the message arrived notification.
//
// No IN params
// ---
// Return - nothing
void MyMosq::clearMessageNotification()
{
    mMessageReceived=false;
}

// Gives the actual message.
//
// No IN params
// ---
// Return - nothing
std::string MyMosq::getMessage()
{
    return(mMessage);
}

// Should I quit ?
//
// No IN params
// ---
// Return - bool: quit or not
bool MyMosq::haveToQuit()
{
   return(mHaveToQuit);
}