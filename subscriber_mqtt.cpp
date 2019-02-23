//mqtt subscriber
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
//create logger agent
static int sockfd; 
static char buffer[MAXLINE]; 
static struct sockaddr_in servaddr; 
static char* sub_id;

void handler (const char * msg)
{
    //connect logger agent
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    //send the log
    char log[100];
    strcpy(log, sub_id);
    strcat(log, msg);
    sendto(sockfd, (const char *)log, strlen(log), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    close(sockfd);  
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
        
        sub_id = argv[4];
	// create a subscriber, that listens for messages on the topic temperature
	Subscriber* mq = new Subscriber(argv[1], atoi(argv[2]), argv[3], argv[4]);
	
        // attach a handler that calls a function on receipt of each message
	mq->message_handler = &handler;

	while(1){
		sleep(1);
        }
		
	return 0;
}
