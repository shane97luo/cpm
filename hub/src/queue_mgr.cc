#include "queue_mgr.h"

std::map<std::string, UMsgSPtr> g_queue;

std::mutex g_queue_mutex;

// 向 g_queue 中添加元素
void addToQueue(const std::string &key, UMsgSPtr value)
{
    std::lock_guard<std::mutex> lock(g_queue_mutex);
    g_queue[key] = value;
}

// 从 g_queue 中获取元素
UMsgSPtr getFromQueue(const std::string &key)
{
    std::lock_guard<std::mutex> lock(g_queue_mutex);
    auto it = g_queue.find(key);
    if (it != g_queue.end())
    {
        return it->second;
    }
    return nullptr;
}

bool containsInQueue(const std::string &key)
{
    std::lock_guard<std::mutex> lock(g_queue_mutex);
    return g_queue.find(key) != g_queue.end();
}