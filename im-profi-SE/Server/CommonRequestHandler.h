// CommonRequestHandler.h
#ifndef SERVER_COMMONREQUESTHANDLER_H_
#define SERVER_COMMONREQUESTHANDLER_H_
 
#include <Poco/Net/HTTPRequestHandlerFactory.h>
 
class CommonRequestHandler : public Poco::Net::HTTPRequestHandlerFactory 
{
 
 public:
 CommonRequestHandler();
 
 virtual Poco::Net::HTTPRequestHandler* createRequestHandler(
              const Poco::Net::HTTPServerRequest& request);
 
};
 
#endif // SERVER_COMMONREQUESTHANDLER_H_  