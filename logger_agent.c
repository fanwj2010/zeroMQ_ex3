//logger client side
//w.fan@kent.ac.uk
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <memory.h>

#define PORT	 8080 
#define MAXLINE 1024 

char* createLog(const char* role, const char* message){
        char* log = (char*)malloc(1+strlen(role)+strlen(message));
        strcpy(log, role);
        strcat(log, message);
        return log; 
}

void logger_agent(const char* role, const char* message) { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char * log = createLog(role, message); 
	struct sockaddr_in servaddr; 
	printf("hello logger\n"); 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len; 
	
	sendto(sockfd, (const char *)log, strlen(log), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	printf("log sent: %s\n", log); 
		

	close(sockfd); 
//	return 0; 
} 

