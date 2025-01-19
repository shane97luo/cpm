#ifndef APPLICATION_H
#define APPLICATION_H

#include <Poco/Util/Application.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <iostream>

#include "ws_proxy.h"

class ServerApplication : public Poco::Util::Application
{
protected:
    // 重写 defineOptions 方法，用于定义命令行选项
    void defineOptions(Poco::Util::OptionSet &options) override;

    // 处理帮助选项的回调函数
    void handleHelp(const std::string &name, const std::string &value);

    // 应用程序的主函数
    int main(const std::vector<std::string> &args) override;

private:
    WsProxy _ws_proxy;
};

#endif // APPLICATION_H