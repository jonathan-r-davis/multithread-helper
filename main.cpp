#include "WorkerPool.h"
#include "FileHandler.h"
#include <iostream>
#include <filesystem>
#include <algorithm>


void _printTopWords(const std::string filename, const std::unordered_map<std::string, int>& wordCountMap) 
{
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
        std::cout << wordCountVector[i].first << ": " << wordCountVector[i].second << ", ";
    }
    std::cout << std::endl << std::endl;
}

int main()
{
    // Create list of files to process
    FileHandler fileHandler;
    for (const auto& entry : std::filesystem::directory_iterator("txtFiles")) 
    {
        fileHandler.addFile(entry.path().string());
    }

    // ---- START Multithreading ----
    std::cout << "--Multithreading-- " << std::endl;

    //Start Timer for multithreaded file processing
    auto start = std::chrono::high_resolution_clock::now();

    WorkerPool pool(4);
    for (int i = 0; i < fileHandler.getFileCount(); i++) 
    {
        pool.enqueueTask([i, &fileHandler]() {
            // std::cout << "Task " << i << " is running on thread " << std::this_thread::get_id() << std::endl;
            fileHandler.processFile(fileHandler.getFilePath(i));
        });
    }

    // Wait for tasks to complete
    pool.waitForCompletion();

    //End Timer for file processing with multithreading
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_mthread = end - start;

    std::cout << "Elapsed time (Multi-threaded): " << elapsed_mthread.count() << " seconds" << std::endl;

    // Print top 10 word counts from multithreaded processing
    for (const auto& fileInfo : fileHandler.fileWordCounts) 
    {
        _printTopWords(fileInfo.first, fileInfo.second);
    }
    // ---- END Multithreading ----



    // ---- START Sequential Processing ----
    std::cout << "--Sequential-- " << std::endl;

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < fileHandler.getFileCount(); i++) 
        fileHandler.processFile(fileHandler.getFilePath(i));

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_sequential = end - start;
    std::cout << "Elapsed time (Sequential): " << elapsed_sequential.count() << " seconds" << std::endl;

    // Ensure that the word counts are the same for both methods
    for (const auto& fileInfo : fileHandler.fileWordCounts) 
    {
        _printTopWords(fileInfo.first, fileInfo.second);
    }
    // ---- END Sequential ----
    
        
    // Determine how much time was saved by using multithreading
    double timeSaved = elapsed_sequential.count() - elapsed_mthread.count();
    double timeSavedPercent = (timeSaved / elapsed_sequential.count()) * 100;
    std::cout << "Time saved by using multithreading: " << timeSaved << " seconds. " << timeSavedPercent << "% improvement!" << std::endl << std::endl;

    return 0;
}