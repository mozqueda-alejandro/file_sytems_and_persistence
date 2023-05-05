#include "File.h"


File::File(std::string fileName) {
    this->fileName = fileName;
    fileContents = "";
    fileSize = 0;
}

File::File(std::string fileName, std::string fileContents) {
    this->fileName = fileName;
    this->fileContents = fileContents;
}

File::File(std::string fileName, std::string fileContents, int fileSize) {
    this->fileName = fileName;
    this->fileContents = fileContents;
    this->fileSize = fileSize;
}

std::string File::getFileName() {
    return fileName;
}

std::string File::getFileContents() {
    return fileContents;
}

int File::getFileSize() {
    return fileSize;
}

void File::setFileName(std::string newFileName) {
    fileName = newFileName;
}

void File::setFileSize(int newFileSize) {
    fileSize = newFileSize;
}

void File::updateFileContents(std::string newFileContents) {
    fileContents = newFileContents;
}


