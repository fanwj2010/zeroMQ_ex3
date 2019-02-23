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

char* createLog(const char* role, const char* message){};

void logger_agent(const char* role, const char* message){}; 

