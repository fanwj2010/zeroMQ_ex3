
#include <cstring>
#include <cstdlib>
#include <iostream>

#include <mosquittopp.h>
#include "pubsub.h"


///////// Publisher

Publisher::Publisher( const char* mqtt_broker_addr, int mqtt_broker_port, const char* _topic, const char* pub_id): mosquittopp(pub_id),topic(_topic) {
	std::cout<< "Plugging MQTT module " <<std::endl;
	
	
	mosqpp::lib_init();
	int conresult = connect(mqtt_broker_addr, mqtt_broker_port, 60);
	//std::cout << " con: "<< conresult << std::endl;
	loop_start();
}

Publisher::~Publisher() {
	loop_stop();
	mosqpp::lib_cleanup();
}

void Publisher::on_connect(int rc)
 {
	 if ( rc != MOSQ_ERR_SUCCESS ) {
		std::cout << ">> Could not connect to the MQTT broker. Does it run(" << rc << ")" << std::endl;
		return;
	}
	
	std::cout << ">> Connected(" << rc << ")" << std::endl;
 }
 

void Publisher::publish_message(const char* _message) {
	    char * buf = (char*)malloc(strlen(_message)+10);
	    sprintf(buf, "{data:%s}", _message);
        std::cout << "MQTT publisher Send message " <<  buf << "to broker on topic " << this->topic << std::endl;
        int ret = publish(NULL, this->topic, strlen(buf), buf, 2, false);
        if(ret != MOSQ_ERR_SUCCESS)
            std::cout << "failed " << std::endl;
        free(buf);
}


//////////////Subscriber

Subscriber::Subscriber( const char* mqtt_broker_addr, int mqtt_broker_port, const char* _topic, const char* sub_id ): mosquittopp(sub_id), topic(_topic) {
	std::cout<< "Plugging MQTT module " <<std::endl;
	
	mosqpp::lib_init();
	connect(mqtt_broker_addr, mqtt_broker_port, 60);
	loop_start();
	
	this->message_handler = NULL;
}

Subscriber::~Subscriber() {
	loop_stop();
	mosqpp::lib_cleanup();
}

void Subscriber::on_connect(int rc)
 {
	 if ( rc != MOSQ_ERR_SUCCESS ) {
		std::cout << ">> Could not connect to the MQTT broker. Does it run(" << rc << ")" << std::endl;
		return;
	}
     
    std::cout<< "Subscribing to topic " << this->topic << std::endl;
	if (subscribe(NULL, this->topic, 2) != MOSQ_ERR_SUCCESS)
	{
		std::cerr << "Could not subscribe to topic " << this->topic << std::endl;
		return;
	}
	
	std::cout << ">> Connected(" << rc << ")" << std::endl;
 }


void Subscriber::on_message(const struct mosquitto_message *message) {
        std::cout << "Received message from MQTT broker by subscriber: " << (char*)(message->payload) <<std::endl;
        if(message_handler != NULL){
			(*Subscriber::message_handler)((char*)(message->payload));
		}
}
