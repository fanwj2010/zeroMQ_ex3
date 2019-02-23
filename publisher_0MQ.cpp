//
//  Pubsub envelope publisher
//  Note that the zhelpers.h file also provides s_sendmore
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "zhelpers.hpp"
int main (int argc, char* argv[]) {
    if(argc<2){
        printf("Usage: publisher_0MQ prefix\n"
               "\tprefix is the zeroMQ publisher sends message on\n"
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
        fflush(stdout);
        s_send (publisher, buf);
        sleep (3);
    }
    return 0;
}
