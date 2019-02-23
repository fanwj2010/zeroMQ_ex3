//mq broker to bridge the mqtt and zeroMQ publishers and subscribers
//w.fan@kent.ac.uk
#include "zhelpers.hpp"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "pubsub.h"
#include <thread>

char g_msg[250];
//static zmq::socket_t backend;
static zmq::context_t context(1);
static zmq::socket_t backend (context, ZMQ_PUB);
char* topic;
 
void handler (const char * msg)
{
    //transfer MQTT broker data to 0MQ subscriber
    memcpy(g_msg, msg, strlen(msg)+1);
    s_sendmore (backend, topic);
    std::cout << "mq_broker backend sends data to zeroMQ subscriber " << g_msg << "\n" <<std::endl;
    s_send (backend, g_msg);
}


int main (int argc, char *argv[])
{
    
    // parse arguments
    if(argc<6)
    {
	     printf("Usage: mq_broker addr port topic pub_id sub_id\n"
		    "\taddr is the mosquitto broker address\n"
		    "\tport is the mosquitto broker port\n"
		    "\ttopic is the mq_broker listens on, which equals to prefix\n"
		    "\tpub_id is the unique mqtt publisher id\n"
		    "\tsub_id is the unique mqtt subscriber id\n"
                    "\tNote: frontend binds tcp://*:5559; backend binds tcp://*:5560\n");
	     exit(0);
    }
    topic = argv[3];
    //zmq::context_t context(1);
    //  Socket facing publisher
    zmq::socket_t frontend (context, ZMQ_SUB);
    frontend.bind("tcp://*:5559");
    frontend.setsockopt (ZMQ_SUBSCRIBE, argv[3], 1);
    
    //  Socket facing services
    //static zmq::socket backend (context, ZMQ_PUB);
    backend.bind("tcp://*:5560");

    //create a publisher of MQTT
    Publisher* mq_pub = new Publisher(argv[1], atoi(argv[2]), argv[3], argv[4]);
    // create a subscriber of MQTT
    Subscriber* mq_sub = new Subscriber(argv[1], atoi(argv[2]), argv[3], argv[5]);	
    
    //receive data from MQTT broker   
    mq_sub->message_handler = &handler;
    
    char buf[250];	
    while(1){
        
        //receive the data from 0MQ publisher
        std::string address = s_recv (frontend);
        std::string contents = s_recv (frontend);
        strcpy(buf,contents.c_str());
        std::cout << "received data from zeroMQ publisher by mq_borker frontend" << g_msg << std::endl;   
            
        //send 0MQ data to MQTT broker
        mq_pub->publish_message(buf);  
 
        sleep (1);
    }	
    
    return 0;
}
