#ifndef _QUEUE_MGR_H_
#define _QUEUE_MGR_H_

#include <future>
#include <map>
#include <mutex>
#include <string>

struct UMessage {
    UMessage(const std::string topic, std::string payload)
    {
        this->topic = topic;
        this->payload = payload;
    }
    std::string topic;
    std::string payload;
};

using UMsgSPtr = std::shared_ptr<std::promise<UMessage>>;

extern std::map<std::string, UMsgSPtr> g_queue;

// 声明辅助函数
void addToQueue(const std::string &key, UMsgSPtr value);
UMsgSPtr getFromQueue(const std::string &key);

bool containsInQueue(const std::string &key);

#endif // _QUEUE_MGR_H_