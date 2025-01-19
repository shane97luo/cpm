#include "ws_client.h"
#include <fcntl.h>

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPMessage;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::WebSocket;

WsClient::WsClient(const std::string &host)
{}

WsClient::~WsClient()
{}

WsClient &WsClient::instance()
{
    static WsClient instance("127.0.0.1");
    return instance;
}

void WsClient::connect()
{
    Poco::Net::HTTPClientSession cs("127.0.0.1", _port);
    Poco::Net::HTTPRequest request(HTTPRequest::HTTP_GET, "/?encoding=text", HTTPMessage::HTTP_1_1);
    request.set("origin", "http://www.heygears.reflex.org");
    Poco::Net::HTTPResponse response;

    _psocket = std::make_unique<Poco::Net::WebSocket>(cs, request, response);
}

void WsClient::disconnect()
{}

void WsClient::postMessage(const std::string &message)
{}

void WsClient::onOpen()
{}

void WsClient::onClose()
{}

void WsClient::onMessage(const std::string &message)
{}

void WsClient::onError(const std::string &error)
{}