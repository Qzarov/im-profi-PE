// Handlers.cpp 
 
#include "./Handlers.h"
#include "./KeyGeneration.h"
 
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
//#include <Poco/Net/HTMLForm.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>
 
#include <iostream>

#include <cstdlib>

#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip> 
 
void PostIntroduction::handleRequest(Poco::Net::HTTPServerRequest& request,
 Poco::Net::HTTPServerResponse& response) 
{
    try {
        KeyGeneration key;

        std::string recv_string;
        Poco::StreamCopier::copyToString(request.stream(), recv_string);
        std::cout << recv_string << std::endl;

        std::string response_string(
                "{\"request_id\":\"" + request.get("X-Request-Id") + "\", \"key_authorization\": \"" + key.getKey() +
                "\"}");

        std::string Host = request.getHost();
        std::string IP;
        char tempHost[Host.length()];
        strcpy(tempHost, Host.c_str());
        uint16_t i = 0;
        while (tempHost[i] != ':') {
            IP += tempHost[i];
            i++;
        }

        nlohmann::json clientInfo = nlohmann::json::parse(recv_string);
        clientInfo["key_authorization"] = key.getKey();
        clientInfo["IP"] = IP;

        std::ifstream fileInClientsInfo("ClientsInfo.json");
        fileInClientsInfo.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        nlohmann::json jsonClientsInfo;
        fileInClientsInfo >> jsonClientsInfo;
        bool flUserReWritten = false;
        if(jsonClientsInfo.contains("payload")) {
            for (auto &payloadClientsInfo: jsonClientsInfo.at("payload")) {
                if (payloadClientsInfo.at("user_id") == clientInfo.at("user_id")) {
                    payloadClientsInfo = clientInfo;
                    flUserReWritten = true;
                    break;
                }
            }
        }
        if (!flUserReWritten)
            jsonClientsInfo["payload"] += clientInfo;

        std::ofstream fileOutClientsInfo("ClientsInfo.json");
        fileOutClientsInfo.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fileOutClientsInfo << std::setw(4) << jsonClientsInfo << std::endl;

        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");
        std::ostream &ostr = response.send();
        ostr << response_string;
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);

        std::string callClient = "./serverMainClient 1 " + IP + ":6666";
        std::system(callClient.c_str());

        callClient = "./serverMainClient 2 " + IP + ":6666";
        std::system(callClient.c_str());
    }
    catch (Poco::Exception &ex)
    {
        std::cerr <<"HTTP exception: "<< ex.displayText()<<". Code:"<<ex.code()<< std::endl;
    }
    catch (nlohmann::json::exception &ex)
    {
        std::cerr <<"JSON exception: "<< ex.what()<<". Id:"<<ex.id << std::endl;
    }
    catch (std::ios_base::failure &ex)
    {
        std::cerr <<"File exception: "<< ex.what()<<". Code:"<<ex.code() << std::endl;
    }
}