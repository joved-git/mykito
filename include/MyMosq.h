#include <mosquittopp.h>

#define VER_MY_MQTT "1.1.1"

#define PUB 0
#define SUB 1

//#define DEBUG ON
//#define DEBUG2 ON

class MyMosq : public mosqpp::mosquittopp
{
public:
    // Constructor with parameters.
    // 
    // const char *: the Id of the sub or pub.
    // const char *: the topic.
    // const char *: the host of the broker.
    // int: the port
    MyMosq(const char *, const char *, const char *, int);                      

    // Destructor.
    ~MyMosq();    

    // Object send message
    //
    // const char *: the message to be sent.
    // ---
    // Return - bool: if message is correctly sent or not.
    bool sendMessage(const char *);                                             // Object send a massage

    // Set the mode (PUB or SUB)
    //
    // int: the mode (PUB or SUB).
    // ---
    // Return - nothing
    void setMode(int);

    // Set the mode (PUB or SUB).
    //
    // No IN params
    // ---
    // Return - int: the mode (PUB or SUB).
    int getMode();

    // Have we received a message ?
    //
    // No IN params
    // ---
    // Return - bool: message received or not.
    bool isMessageReceived();

    // Clear the message arrived notification.
    //
    // No IN params
    // ---
    // Return - nothing
    void clearMessageNotification();

    // Get the actual message.
    //
    // No IN params
    // ---
    // Return - nothing
    std::string getMessage();

    // Should I quit ?
    //
    // No IN params
    // ---
    // Return - bool: quit or not
    bool haveToQuit();
    
private:
    // Trigger once when the object is connecting to the host.
    //
    // int: the return code of this connection.
    // ---
    // Return - nothing
    void on_connect(int);

    // Trigger once when the object is disconnecting to the host.
    //
    // int: the return code of this deconenction.
    // ---
    // Return - nothing
    void on_disconnect(int);

    // Trigger when the object is publishing.
    //
    // int: the return code of this publication.
    // ---
    // Return - nothing
    void on_publish(int);

    // Trigger when the object is receiving a message.
    //
    // const struct mosquitto_message *: message informations.
    // ---
    // Return - nothing
    void on_message(const struct mosquitto_message *);
            
    // Members.
    const char *mHost;                          // The host of the object.
    const char *mId;                            // the Id/name of the publisher or subscriber.
    const char *mTopic;                         // The topic used.
    int mPort;                                  // The port used.
    int mMode;                                  // The mode used (pub or sub).
    int mKeepAlive;                             //
    bool mMessageReceived;                      // Have we receive a message (sub mode only).
    std::string mMessage;                       // message received.
    bool mHaveToQuit;                           // The software should quit. This is just a quit condiction.
};