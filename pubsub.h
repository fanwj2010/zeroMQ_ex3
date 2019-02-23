
#ifndef PUBSUB_H
#define PUBSUB_H

#include <iostream>
#include <mosquitto.h>
#include <mosquittopp.h>
          
// This file contains two wrappers for mosqpp::mosquittopp to 
// communicate with a mosquitto broker.
// Publisher and Subscriber are singleton, each can have only one 
// instance.

// Publisher implements only send message functionality to the broker 
// on a specified topic 
class Publisher :public mosqpp::mosquittopp
{
private:
    
    // handler called when the connection with the mosquitto broker has been established
    void on_connect(int rc);
    
    // the topic to publish
    const char* topic;

public:
    // configure the Publisher's instance with mosquitto broker address and port and topic
    Publisher( const char* mqtt_broker_addr, int mqtt_broker_port, const char* topic, const char* pub_id);
	
    ~Publisher();
    
    // publishes a string
	void publish_message(const char* _message);
};


// Subscriber implements only receiving functionality on a specified 
// topic. It supports ro attach a handler to process incoming messages.
class Subscriber :public mosqpp::mosquittopp
{
private:
    // handler called when the connection with the mosquitto broker has been established
    void on_connect(int rc);   
    
    // handler on receiving a message from mqtt broker
	void on_message(const struct mosquitto_message *message);
    
    // the topic to subscribe
    const char* topic;
    
public:
    // configure the Subscriber's instance with mosquitto broker address and port and topic
    Subscriber( const char* mqtt_broker_addr, int mqtt_broker_port, const char* topic, const char* sub_id);
    
    ~Subscriber();

    // attach a user handler to process incoming messages.
    void (* message_handler)(const char* msg);
};


#endif //PUBSUB_H
