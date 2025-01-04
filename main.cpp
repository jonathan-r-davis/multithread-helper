#include "WorkerPool.h"
#include "FileHandler.h"
#include <iostream>
#include <filesystem>

int main()
{
    // Create list of files to process
    FileHandler fileHandler;
    for (const auto& entry : std::filesystem::directory_iterator("txtFiles")) 
    {
        fileHandler.addFile(entry.path().string());
    }

    WorkerPool pool(4);
    for (int i = 0; i < fileHandler.getFileCount(); i++) 
    {
        pool.enqueueTask([i, &fileHandler]() {
            fileHandler.processFile(fileHandler.getFilePath(i));
        });
    }

    // Wait for tasks to complete
    pool.waitForCompletion();
    std::cout << "All tasks completed" << std::endl;

    // Sort data and print out top 10 words for each file
    for (const auto& fileInfo : fileHandler.fileWordCounts) 
    {
        std::string filename = fileInfo.first;
        std::unordered_map<std::string, int> wordCountMap = fileInfo.second;
        
        std::vector<std::pair<std::string, int>> wordCountVector(wordCountMap.begin(), wordCountMap.end());
        std::sort(wordCountVector.begin(), wordCountVector.end(), 
            [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) 
            {
                return a.second > b.second;
            });

        std::cout << "File: " << filename << " top 10 words:" << std::endl;
        std::cout << "\t";
        for (int i = 0; i < 10; i++) 
        {
            i == 9 ?
                std::cout << wordCountVector[i].first << ": " << wordCountVector[i].second
                : 
                std::cout << wordCountVector[i].first << ": " << wordCountVector[i].second << ", ";
        }
        std::cout << std::endl << std::endl;
    }
    
    return 0;
}