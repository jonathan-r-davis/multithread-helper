#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>


FileHandler::FileHandler()
{
    std::cout << "FileHandler Constructor" << std::endl;
}

FileHandler::~FileHandler()
{
    std::cout << "FileHandler Destructor" << std::endl;
}

void FileHandler::addFile(const std::string& filename)
{
    std::cout << "Adding file: " << filename << std::endl;
    filePaths.push_back(filename);
}

void FileHandler::processFile(const std::string& filename)
{
    std::cout << "Processing file: " << filename << " on thread " << std::this_thread::get_id() << std::endl;
    std::ifstream file(filename);
    if (file.is_open()) 
    {
        // Using a 1 MB buffer to read file reduces the number of I/O operations
        std::vector<char> buffer(1024 * 1024); // 1 MB buffer
        std::unordered_map<std::string, int> wordCountMap;

        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) 
        {
            std::istringstream iss(std::string(buffer.data(), file.gcount()));
            std::string word;
            while (iss >> word)
                ++wordCountMap[word];
            
        }
        file.close();
        fileWordCounts[filename] = wordCountMap;
    } 
    else 
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}