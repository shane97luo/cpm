#include "ws_proxy.h"
#include "queue_mgr.h"
#include "ws_client.h"

#include "queue_mgr.h"
#include <chrono>

std::string WsProxy::sendMessage(const std::string &topic, const std::string &payload)
{
    std::string result;

    if (containsInQueue(topic))
    {
        std::cerr << "topic already exists" << std::endl;
        return result;
    }

    WsClient::instance().postMessage(payload);

    UMessage msg(topic, payload);
    auto promise = std::make_shared<std::promise<UMessage>>();

    auto future = promise->get_future();

    addToQueue(topic, promise);

    auto status = future.wait_for(std::chrono::milliseconds(1000 * 5));
    if (status == std::future_status::ready)
    {
        getFromQueue(topic);
        auto fut_ret = future.get();

        result = fut_ret.payload;

    } else if (status == std::future_status::timeout)
    {
        std::cerr << "timeout" << std::endl;
        auto pro = getFromQueue(topic);

        promise->set_value(msg);
    }

    return result;
}
