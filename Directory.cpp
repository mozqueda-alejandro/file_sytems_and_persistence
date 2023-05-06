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

File& Directory::getFile(int position) {
    std::list<File>::iterator it = files.begin();
    std::advance(it, position);
    return *it;
}

std::string Directory::getDirectoryName() {
    return directoryName;
}

std::string Directory::getDirectoryPath() {
    return directoryPath;
}

std::string Directory::getDirectoryContents() {
    // std::cout << "\t" << i << ". " << file.getFileName() << " " << file.getFileSize() << " bytes" << std::endl;
    std::string directoryContents = directoryName + "\n";
    int i = 1;
    for (auto file : files) {
        directoryContents += "\t" + std::to_string(i) + ". " + file.getFileName() + " " + std::to_string(file.getFileSize()) + " bytes\n";
        i++;
    }
    return directoryContents;
}

int Directory::getNumFiles() {
    return numFiles;
}

void Directory::addFile(std::string fileName, std::string fileContents, int fileSize) {
    files.emplace_front(fileName, fileContents, fileSize);
    numFiles++;
}

void Directory::deleteFile(int position) {
    std::list<File>::iterator it = files.begin();
    std::advance(it, position);
    files.erase(it);
    numFiles--;
}

void Directory::setDirectoryName(std::string directoryName) {
    this->directoryName = directoryName;
}
