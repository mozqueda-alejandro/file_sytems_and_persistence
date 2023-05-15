#include "Directory.h"


Directory::Directory() {
    files[0] = new File("..", "", -1);
    files[1] = new File(".", "", -1);
    numFiles = 2;
}

void Directory::init(std::string directoryName, std::string directoryPath) {
    this->directoryName = directoryName;
    this->directoryPath = directoryPath;
}

File* Directory::getFile(int position) {
    return files[position];
}

std::string Directory::getDirectoryContents() {
    // In the form:
    // directoryName
    //      1. fileName fileSize bytes
    //      2. .. -1 bytes
    //      3. . -1 bytes
    std::string directoryContents = directoryName + "\n";
    for (int j = 0; j < numFiles; j++) {
        directoryContents += '\t' + std::to_string(j + 1) + ". " + files[j]->getFileName() + " " + std::to_string(files[j]->getFileSize()) + " bytes\n";
    }
    return directoryContents;
}

std::string Directory::getDirectoryName() {
    return directoryName;
}

std::string Directory::getDirectoryPath() {
    return directoryPath;
}

std::string Directory::getFileNameAtPosition(int position) {
    return files[position]->getFileName();
}

int Directory::getNumFiles() {
    return numFiles;
}

void Directory::addFile(std::string fileName, std::string fileContents, int fileSize) {
    files[numFiles] = files[numFiles - 1];
    files[numFiles - 1] = files[numFiles - 2];
    files[numFiles - 2] = new File(fileName, fileContents, fileSize);
    numFiles++;
}

void Directory::deleteFile(int position) {
    delete files[position];

    for (int i = position; i < numFiles - 1; i++) {
        files[i] = files[i + 1];
    }
    numFiles--;
}
