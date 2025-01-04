#ifndef WORKERPOOL_H
#define WORKERPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

class WorkerPool
{
public:
    explicit WorkerPool(size_t numWorkers);
    ~WorkerPool();

    void enqueueTask(std::function<void()> task);
    void waitForCompletion();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable taskCondition;

    std::atomic<bool> stop;
    std::atomic<size_t> activeTasks;

    void workerThread();
};

#endif