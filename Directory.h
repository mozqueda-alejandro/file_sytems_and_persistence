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
    std::string getDirectoryName();
    std::string getDirectoryPath();
    int getNumFiles();

    void addFile(std::string fileName, std::string fileContents, int fileSize);

    void setDirectoryName(std::string directoryName);

    void updateFilesInDirectory(int position);
    
private:
    std::list<File> files;
    std::string directoryName;
    std::string directoryPath; // In the form /home/user/my_directory
    int numFiles;
};