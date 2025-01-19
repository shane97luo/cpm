#include "server_application.h"
#include "static_file_handler.h"

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <chrono>
#include <thread>

void ServerApplication::defineOptions(Poco::Util::OptionSet &options)
{
    Poco::Util::Application::defineOptions(options);
    options.addOption(Poco::Util::Option("help", "h", "display help information").required(false).repeatable(false).callback(Poco::Util::OptionCallback<ServerApplication>(this, &ServerApplication::handleHelp)));
}

void ServerApplication::handleHelp(const std::string &name, const std::string &value)
{
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("ServerApplication [options]");
    helpFormatter.setHeader("A simple Poco-based desktop application.");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
    exit(0);
}

int ServerApplication::main(const std::vector<std::string> &args)
{
    std::cout << "Welcome to ServerApplication!" << std::endl;
    std::cout << "This is a simple desktop application using the Poco library." << std::endl;

    // 服务器监听的端口
    unsigned short port = 8080;

    // 静态文件的根目录
    std::string rootDir = "./public";

    // 创建服务器套接字
    Poco::Net::ServerSocket svs(port);

    // 创建 HTTP 服务器
    Poco::Net::HTTPServer srv(new StaticFileHandlerFactory(rootDir), svs, new Poco::Net::HTTPServerParams);

    // 启动服务器
    srv.start();

    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return Poco::Util::Application::EXIT_OK;
}