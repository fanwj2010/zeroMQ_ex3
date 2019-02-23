// 0MQ publisher
// w.fan@kent.ac.uk
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
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
int main (int argc, char* argv[]) {
    if(argc<3){
        printf("Usage: publisher_0MQ prefix id\n"
               "\tprefix is the zeroMQ publisher sends message on\n"
               "\tid is the unique publisher id\n"
               "\tNote: currently, the publisher connect to localhost:5559\n");
        exit(0);
    }
    //  Prepare our context and publisher
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5559");

    //create logger agent
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in     servaddr;   
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY;     
    char log[100];
  
    char buf[250]; 
    while (1) {
        //  Write two messages, each with an envelope and content
        s_sendmore (publisher, argv[1]);
        sprintf(buf,"{temp:%d}", rand()%45+1);
        printf("send message %s on prefix temperature.\n", buf);
        fflush(stdout);
        s_send (publisher, buf);
        
        //send log
        strcpy(log, argv[2]);
        strcat(log, buf);
        sendto(sockfd, (const char *)log, strlen(log), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
        sleep (3);
    }
    close(sockfd);
    return 0;
}
