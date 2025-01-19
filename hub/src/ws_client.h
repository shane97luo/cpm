#ifndef WS_CLIENT_H
#define WS_CLIENT_H

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/WebSocket.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

class WsClient
{
public:
    WsClient(const std::string &host = "127.0.0.1");
    ~WsClient();

    static WsClient &instance();

    void connect();

    void disconnect();

    void postMessage(const std::string &message);

private:
    void onOpen();
    void onClose();
    void onMessage(const std::string &message);

    void onError(const std::string &error);

    uint16_t _port{8888};

    std::unique_ptr<Poco::Net::WebSocket> _psocket;
};

#endif // WS_CLIENT_H