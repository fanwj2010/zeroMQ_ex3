CXX := gcc

CXXFLAGS := -std=c++11 -lstdc++ -lzmq -lczmq -lmosquittopp -lmosquitto -lpthread

SOURCE_FILES := \
			pubsub.cpp
			
HEADER_FILES := \
			zhelpers.hpp pubsub.h
			

RM := rm -f

all:
	$(CXX) -o subscriber_0MQ subscriber_0MQ.cpp $(SOURCE_FILES) $(CXXFLAGS)
	$(CXX) -o publisher_0MQ publisher_0MQ.cpp $(SOURCE_FILES) $(CXXFLAGS)
	$(CXX) -o subscriber_mqtt subscriber_mqtt.cpp $(SOURCE_FILES) $(CXXFLAGS)
	$(CXX) -o publisher_mqtt publisher_mqtt.cpp $(SOURCE_FILES) $(CXXFLAGS)
	$(CXX) -o mq_broker mq_broker.cpp $(SOURCE_FILES) $(CXXFLAGS)
	$(CXX) -o logger logger.c $(CXXFLAGS)

clean:
	$(RM) publisher_0MQ publisher_mqtt subscriber_0MQ subscriber_mqtt mq_broker logger *.o *.so *.a
