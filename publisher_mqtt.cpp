//mqtt publisher
//w.fan@kent.ac.uk
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "pubsub.h"
#include "zhelpers.hpp"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1024 

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
	
        //create logger agent
        int sockfd; 
        char buffer[MAXLINE]; 
        struct sockaddr_in servaddr; 
        if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
           perror("socket creation failed"); 
           exit(EXIT_FAILURE); 
        } 
        memset(&servaddr, 0, sizeof(servaddr)); 
      
        servaddr.sin_family = AF_INET; 
        servaddr.sin_port = htons(PORT); 
        servaddr.sin_addr.s_addr = INADDR_ANY; 
        char log[100];
        
        char buf[250];	
        //continually send a random temperature reading, every 3 seconds
	while(1)
	{
               sprintf(buf, "{temp:%d}", rand()%45+1);
	       mq->publish_message(buf);
	       //send log
               strcpy(log, argv[4]);
               strcat(log, buf);
               sendto(sockfd, (const char *)log, strlen(log), 
               MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
               sizeof(servaddr)); 

               sleep(3);
	 }
	close(sockfd);	
	return 0;
}
