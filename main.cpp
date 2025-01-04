#include "WorkerPool.h"
#include <iostream>

int main()
{
    WorkerPool pool(4);
    for (int i = 0; i < 4; i++) 
    {
        pool.enqueueTask([i]() {
            std::cout << "Task " << i << " is running on thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }

    // Wait for tasks to complete
    pool.waitForCompletion();
    std::cout << "All tasks completed" << std::endl;
    
    return 0;
}