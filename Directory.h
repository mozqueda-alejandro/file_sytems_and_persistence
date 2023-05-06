#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <list>

#include "File.h"


class Directory
{
public:
    Directory();
    void init(std::string directoryName, std::string directoryPath);

    std::list<File> getFiles();
    File& getFile(int position);
    void addFile(std::string fileName, std::string fileContents, int fileSize);
    void deleteFile(int position);
    std::string getDirectoryContents();
    std::string getDirectoryName();
    std::string getDirectoryPath();
    int getNumFiles();
    void setDirectoryName(std::string directoryName);
    
private:
    std::list<File> files;
    std::string directoryName;
    std::string directoryPath; // In the form /home/user/my_directory
    int numFiles;
};

#endif // DIRECTORY_H
