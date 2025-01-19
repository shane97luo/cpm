#ifndef _FILE_SERVER_H
#define _FILE_SERVER_H

#include <Poco/File.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/PartHandler.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Path.h>
#include <Poco/StreamCopier.h>
#include <Poco/Util/ServerApplication.h>
#include <fstream>
#include <iostream>

// 静态文件请求处理器
class StaticFileHandler : public Poco::Net::HTTPRequestHandler
{
public:
    StaticFileHandler(const std::string &rootDir) : rootDir_(rootDir)
    {}

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    // 处理文件请求
    void handelFileRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

    // 处理系统信息请求
    void handelSystemInfoRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

private:
    std::string rootDir_;
};

// 静态文件请求处理器工厂
class StaticFileHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    StaticFileHandlerFactory(const std::string &rootDir) : rootDir_(rootDir)
    {}

    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

private:
    std::string rootDir_;
};

#endif // _FILE_SERVER_H