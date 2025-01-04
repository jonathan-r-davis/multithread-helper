#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>

class FileHandler {
public:
    FileHandler();
    ~FileHandler();

    void addFile(const std::string& filename);
    void processFile(const std::string& filename);

    int getFileCount() const 
    { 
        return filePaths.size(); 
    }

    std::string getFilePath(int index) const 
    { 
        return filePaths[index]; 
    }

    // <filename, <word, count>>
    std::unordered_map<std::string, std::unordered_map<std::string, int>> fileWordCounts;

private:
    std::vector<std::string> filePaths;
};


#endif // FILEHANDLER_H