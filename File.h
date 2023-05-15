#ifndef FILE_H
#define FILE_H

#include <iostream>


class File
{
public:
    File(std::string fileName);
    File(std::string fileName, std::string fileContents);
    File(std::string fileName, std::string fileContents, int fileSize);

    std::string getFileName();
    std::string getFileContents();
    int getFileSize();

    void setFileName(std::string newFileName);
    void setFileSize(int newFileSize);
    void setFileContents(std::string newFileContents);
    void addFileContents(std::string additionalFileContents);

    ~File() = default;    
private:
    std::string fileName;
    std::string fileContents;
    int fileSize;
};

#endif // FILE_H
