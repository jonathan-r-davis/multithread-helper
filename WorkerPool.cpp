#include "WorkerPool.h"

WorkerPool::WorkerPool(size_t numThreads) : stop(false), activeTasks(0)
{
    for (size_t i = 0; i < numThreads; ++i)
        workers.emplace_back(&WorkerPool::workerThread, this);
}

WorkerPool::~WorkerPool()
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    taskCondition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}

void WorkerPool::enqueueTask(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasks.push(std::move(task));
        ++activeTasks;
    }
    taskCondition.notify_one();
}

void WorkerPool::waitForCompletion()
{
    std::unique_lock<std::mutex> lock(queueMutex);
    taskCondition.wait(lock, [this] { return tasks.empty() && activeTasks == 0; });
}

void WorkerPool::workerThread()
{
    while (true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            taskCondition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty())
                return;

            task = std::move(tasks.front());
            tasks.pop();
        }

        task();

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            --activeTasks;
            if (tasks.empty() && activeTasks == 0)
                taskCondition.notify_all();
        }
    }
}