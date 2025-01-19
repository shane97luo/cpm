#include "static_file_handler.h"

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/OptionProcessor.h>
#include <Poco/Util/ServerApplication.h>

void StaticFileHandler::handelFileRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    Poco::Path path(request.getURI());
    if (path.isDirectory())
    {
        path.makeDirectory();
        path.append("index.vue");
    }

    std::string fullPath = rootDir_ + path.toString();

    Poco::File file(fullPath);
    if (file.exists() && file.isFile())
    {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        std::string extension = Poco::Path(fullPath).getExtension();
        if (extension == "html" || extension == "htm")
        {
            response.setContentType("text/html");
        } else if (extension == "css")
        {
            response.setContentType("text/css");
        } else if (extension == "js")
        {
            response.setContentType("application/javascript");
        } else if (extension == "png")
        {
            response.setContentType("image/png");
        } else if (extension == "jpg" || extension == "jpeg")
        {
            response.setContentType("image/jpeg");
        } else if (extension == "gif")
        {
            response.setContentType("image/gif");
        } else if (extension == "vue")
        {
            response.setContentType("vue");
        } else
        {
            response.setContentType("application/octet-stream");
        }

        std::ifstream istr(fullPath, std::ios::binary);
        if (istr)
        {
            std::ostream &ostr = response.send();
            Poco::StreamCopier::copyStream(istr, ostr);
        } else
        {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.setReason("File could not be opened");
            response.send();
        }
    } else
    {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        response.setReason("File not found");
        response.send();
    }
}

void StaticFileHandler::handelSystemInfoRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    // 设置响应头
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    response.setContentType("application/json");

    // 模拟系统信息数据
    Poco::JSON::Object systemInfo;
    static int cpuUsage = 0;

    cpuUsage += 1;

    systemInfo.set("cpuUsage", cpuUsage);
    systemInfo.set("cpuUser", "0.2");
    systemInfo.set("cpuSystem", "0.1");
    systemInfo.set("cpuIowait", "0");
    systemInfo.set("cpuIdle", "99.7");
    systemInfo.set("cpuCtxSw", "354");
    systemInfo.set("memUsage", "36.4");
    systemInfo.set("memTotal", "7.65");
    systemInfo.set("memUsed", "2.80");
    systemInfo.set("memFree", "4.85");
    systemInfo.set("memActive", "124");
    systemInfo.set("memInactive", "2.40");
    systemInfo.set("memBuffers", "17.8");
    systemInfo.set("memCached", "421");
    systemInfo.set("swapUsage", "0");
    systemInfo.set("swapTotal", "2.00");
    systemInfo.set("swapUsed", "0");
    systemInfo.set("swapFree", "2.00");
    systemInfo.set("load1m", "0.06");
    systemInfo.set("load5m", "0.02");
    systemInfo.set("load15m", "0.02");
    systemInfo.set("networkRps", "70");
    systemInfo.set("networkTxs", "70");

    std::ostream &out = response.send();
    systemInfo.stringify(out);
}

void StaticFileHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    auto uri = request.getURI();

    std::cout << "uri: " << uri << std::endl;

    const std::string sysinfo_api = "/api/1/all/info";

    if (uri == "/")
    {
        std::cout << "handelFileRequest d sjhhhds" << std::endl;

        handelFileRequest(request, response);
    } else if (uri == sysinfo_api)
    {
        std::cout << "handelSystemInfoRequest d sjhhhds" << std::endl;
        handelSystemInfoRequest(request, response);
    } else
    {}
}

// 静态文件请求处理器工厂
Poco::Net::HTTPRequestHandler *StaticFileHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    return new StaticFileHandler(rootDir_);
}
