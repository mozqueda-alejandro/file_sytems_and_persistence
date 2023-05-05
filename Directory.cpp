#include "Directory.h"


Directory::Directory() {
    files.emplace_back("..", "", -1);
    files.emplace_back(".", "", -1);
    numFiles = 2;
}

void Directory::init(std::string directoryName, std::string directoryPath) {
    this->directoryName = directoryName;
    this->directoryPath = directoryPath;
}

std::list<File> Directory::getFiles() {
    return files;
}

std::string Directory::getDirectoryName() {
    return directoryName;
}

std::string Directory::getDirectoryPath() {
    return directoryPath;
}

int Directory::getNumFiles() {
    return numFiles;
}

void Directory::addFile(std::string fileName, std::string fileContents, int fileSize) {
    files.emplace_front(fileName, fileContents, fileSize);
    numFiles++;
}

void Directory::setDirectoryName(std::string directoryName) {
    this->directoryName = directoryName;
}
