//mqtt publisher
//w.fan@kent.ac.uk

#include <cstdio>
#include <cstdlib>

#include <unistd.h> //sleep
#include "pubsub.h"



int main(int argc, char **argv)
{
	// parse arguments
	if(argc<5)
	{
		printf("Usage: publisher_mqtt addr port topic id\n"
		       "\taddr is the mosquitto broker address\n"
		       "\tport is the mosquitto broker port\n"
		       "\ttopic is the thermometer sends message on\n"
		       "\tid is the unique thermometer id\n");
		exit(0);
	}

	// create a publisher, last paramater the 'topic' on which to publish
	Publisher* mq = new Publisher(argv[1], atoi(argv[2]), argv[3], argv[4]);
	char buf[250];
	
    //continually send a random temperature reading, every 3 seconds
	while(1)
	{
        sprintf(buf, "{temp:%d}", rand()%45+1);
		mq->publish_message(buf);
		
		sleep(3);
	}
		
	return 0;
}
