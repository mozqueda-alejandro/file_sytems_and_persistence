#include "Directory.h"

Directory::Directory() {
    numFiles = 0;
}

void Directory::init(std::string directoryName) {
    this->directoryName = directoryName;
}

std::list<File> Directory::getFiles() {
    return files;
}

std::string Directory::getDirectoryName() {
    return directoryName;
}

int Directory::getNumFiles() {
    return numFiles;
}

