#include <iostream>


class File
{
public:
    File();
    File(std::string fileName, std::string fileContents, std::size_t fileSize);

    std::string getFileName();
    std::string getFileContents();
    std::size_t getFileSize();

    void setFileName(std::string newFileName);
    void setFileSize(std::size_t newFileSize);
    void updateFileContents(std::string newFileContents);
    

    ~File();

private:
    std::string fileName;
    std::string fileContents;
    std::size_t fileSize;
};