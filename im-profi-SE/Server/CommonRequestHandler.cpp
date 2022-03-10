// CommonRequestHandler.cpp 
 
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>
 
#include "./Handlers.h"
#include "./CommonRequestHandler.h"
 
CommonRequestHandler::CommonRequestHandler() 
{
}
 
Poco::Net::HTTPRequestHandler* CommonRequestHandler::createRequestHandler (
    const Poco::Net::HTTPServerRequest& request) 
 {
 Poco::URI uri(request.getURI());
 
 if (request.getMethod()=="POST" && uri.getPath() == "/Introduction" )
 {
 return new PostIntroduction();
 }
 return nullptr; 
};