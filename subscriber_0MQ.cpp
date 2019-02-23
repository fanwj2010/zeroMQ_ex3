// 0MQ subscriber
// w.fan@kent.ac.uk
#include "zhelpers.hpp"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

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
           printf("Usage: subscriber_0MQ prefix id\n"
                  "\tprefix is the zeroMQ subscriber listens on\n"
                  "\tid is the unique subscriber id\n"
                  "\tcurrently, the subscriber connects to localhost:5560\n");
           exit(0);
    }
    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    //subscriber.connect("tcp://localhost:5563");
    subscriber.connect("tcp://localhost:5560");
    subscriber.setsockopt( ZMQ_SUBSCRIBE, argv[1], 1);
    
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
    while (1) {
        //  Read envelope with address
        std::string address = s_recv (subscriber);
        //  Read message contents
        std::string contents = s_recv (subscriber);
        
        std::cout << "received message on prefix temperature: "<< "[" << address << "] " << contents << std::endl;

        //send log
        strcpy(log, argv[2]);
        strcat(log, contents.c_str());
        sendto(sockfd, (const char *)log, strlen(log), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
     }

    close(sockfd); 

    return 0;
}
