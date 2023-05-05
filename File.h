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
    void updateFileContents(std::string newFileContents);
    
private:
    std::string fileName;
    std::string fileContents;
    int fileSize;
};