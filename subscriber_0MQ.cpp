//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
#include "zhelpers.hpp"
int main (int argc, char* argv[]) {
    if(argc<2){
           printf("Usage: subscriber_0MQ prefix\n"
                  "\tprefix is the zeroMQ subscriber listens on\n"
                  "\tcurrently, the subscriber connects to localhost:5560\n");
           exit(0);
    }
    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    //subscriber.connect("tcp://localhost:5563");
    subscriber.connect("tcp://localhost:5560");
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "temperature", 1);
    while (1) {
        //  Read envelope with address
        std::string address = s_recv (subscriber);
        //  Read message contents
        std::string contents = s_recv (subscriber);
        
        std::cout << "received message on prefix temperature: "<< "[" << address << "] " << contents << std::endl;
    }
    return 0;
}
