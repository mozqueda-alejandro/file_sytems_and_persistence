#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <list>

#include "File.h"

#define MAX_FILES 1000


class Directory
{
public:
    Directory();
    void init(std::string directoryName, std::string directoryPath);

    std::list<File> getFiles();
    File& getFile(int position);
    void addFile(std::string fileName, std::string fileContents, int fileSize);
    void deleteFile(int position);
    std::string getDirectoryName();
    std::string getDirectoryPath();
    std::string getDirectoryContents();
    int getNumFiles();
    void setDirectoryName(std::string directoryName);


    void updateFilesInDirectory(int position);
    
private:
    std::list<File> files;
    std::string directoryName;
    std::string directoryPath; // In the form /home/user/my_directory
    int numFiles;
};