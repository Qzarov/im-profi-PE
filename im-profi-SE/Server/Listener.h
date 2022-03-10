// Listener.h
#ifndef SERVER_LISTENER_H_
#define SERVER_LISTENER_H_
 
#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPServer.h>
 
#include <vector>
#include <string>
#include <iostream>
 
#include "CommonRequestHandler.h"


class Listener : public Poco::Util::ServerApplication 
{
 virtual int main(const std::vector<std::string>& args) 
 {
 Poco::Net::HTTPServerParams* params = new Poco::Net::HTTPServerParams();
 params->setMaxQueued(50);
 params->setMaxThreads(4);
 
 Poco::Net::ServerSocket socket(std::stoi(args[0])); // argument is a port 
 
 Poco::Net::HTTPServer server(new CommonRequestHandler(),
 socket,
 params);
 
 server.start();
 waitForTerminationRequest();
 server.stop();
 
 return 0;
 }
};
#endif // SERVER_LISTENER_H_