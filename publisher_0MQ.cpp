// 0MQ publisher
// w.fan@kent.ac.uk
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "zhelpers.hpp"
#include "logger_agent.h"
int main (int argc, char* argv[]) {
    if(argc<3){
        printf("Usage: publisher_0MQ prefix id\n"
               "\tprefix is the zeroMQ publisher sends message on\n"
               "\tid is the zeroMQ publisher id\n"
               "\tNote: currently, the publisher connect to localhost:5559\n");
        exit(0);
    }
    //  Prepare our context and publisher
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    //publisher.bind("tcp://*:5563");
    publisher.connect("tcp://localhost:5559");
    char buf[250]; 
    while (1) {
        //  Write two messages, each with an envelope and content
        s_sendmore (publisher, argv[1]);
        sprintf(buf,"{temp:%d}", rand()%45+1);
        printf("send message %s on prefix temperature.\n", buf);
        printf(" %s : %s.\n",argv[2], buf);
        logger_agent(argv[2],buf);
        printf(" %s : %s!!!\n",argv[2], buf);
        fflush(stdout);
        s_send (publisher, buf);
        sleep (3);
    }
    return 0;
}
