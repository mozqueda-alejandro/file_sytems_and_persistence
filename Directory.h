#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <list>

#include "File.h"

#define MAX_FILES 1000


class Directory
{
public:
    Directory();
    void init(std::string directoryName, std::string directoryPath);

    File* getFile(int position);

    void addFile(std::string fileName, std::string fileContents, int fileSize);
    void deleteFile(int position);

    std::string getDirectoryContents();
    std::string getDirectoryName();
    std::string getDirectoryPath();
    std::string getFileNameAtPosition(int position);
    int getNumFiles();
    
private:
    File* files[MAX_FILES];
    std::string directoryName;
    std::string directoryPath; // In the form /home/user/my_directory
    int numFiles;
};

#endif // DIRECTORY_H
