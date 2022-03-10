// Handlers.h
#ifndef SERVER_HANDLERS_H_
#define SERVER_HANDLERS_H_
 
#include <Poco/Net/HTTPRequestHandler.h>
 
#include <iostream>
 
class PostIntroduction : public Poco::Net::HTTPRequestHandler {
 public:
 virtual void handleRequest(Poco::Net::HTTPServerRequest& req,
 Poco::Net::HTTPServerResponse& res);
};
 
#endif // SERVER_HANDLERS_H_  