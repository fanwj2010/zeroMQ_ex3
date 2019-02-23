//mqtt subscriber
//w.fan@kent.ac.uk

#include <cstdio>
#include <cstdlib>

#include <unistd.h> //sleep
#include "pubsub.h"


void handler (const char * msg)
{
    //print out the message received
    // std::cout << " in handler " << msg << std::endl;
}


int main(int argc, char **argv)
{
	// parse arguments
	if(argc<5)
	{
		printf("Usage: subscriber_mqtt addr port topic id\n"
               "\taddr is the mosquitto broker address\n"
               "\tport is the mosquitto broker port\n"
               "\ttopic is the subscriber listens on\n"
               "\tid is the unique subscriber id\n");
		exit(0);
	}

	// create a subscriber, that listens for messages on the topic temperature
	Subscriber* mq = new Subscriber(argv[1], atoi(argv[2]), argv[3], argv[4]);
	
	// attach a handler that calls a function on receipt of each message
	mq->message_handler = &handler;

	while(1)
		sleep(1);
		
	return 0;
}
