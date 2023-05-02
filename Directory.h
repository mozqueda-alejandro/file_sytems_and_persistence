#include <iostream>
#include <list>

#include "File.h"

#define MAX_FILES 1000


class Directory
{
public:
    Directory();

    std::list<File> getFiles();
    std::string getDirectoryName();
    int getNumFiles();

    void updateFilesInDirectory(int position);
    

    ~Directory();
private:
    std::list<File> files;
    std::string directoryName;
    int numFiles;
};