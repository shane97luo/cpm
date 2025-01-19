#ifndef _WS_PROXY_H_
#define _WS_PROXY_H_

#include "nlohmann/json.hpp"
#include "ws_client.h"

#include <deque>
#include <future>
#include <map>
#include <mutex>
#include <string>

class WsProxy
{
public:
    std::string sendMessage(const std::string &topic, const std::string &payload);

private:
};

#endif // _WS_PROXY_H_