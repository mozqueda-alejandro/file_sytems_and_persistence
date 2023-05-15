#include <dirent.h>
#include <fstream>
#include <iostream>
#include <limits> // For std::cin.ignore(std::numeric_limits<std::streamsize>::max()
#include <list>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Directory.h"


Directory directoryObject;
struct stat statbuf;


// Required function prototypes
void createDirectory();
void loadExistingDirectory();
void createFile();
void deleteFile();
void addContentsToFile();
void overwriteFile();
void displayDirectoryContents();
void displayFileContents();

// Helper function prototypes
std::string getHomeDirectory();
void printMenu();
int validateMenuInput(std::string str, int min = 0, int max = 6);
bool promptWriteToFile();
int getFileIndex(std::string prompt);
int getFileSize(std::string filePath);


int main() {
    createDirectory();
    // Main loop
    while (true) {
        // Print directory menu and get user input
        printMenu();
        int choice;
        while (true) {
            std::cout << "\n";
            std::cout << "What would you like to do? ";
            std::string userInput;
            std::cin >> userInput;
            choice = validateMenuInput(userInput);
            if (choice != -1) {
                break;
            }
            std::cout << "Invalid input\n";
        }
        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                deleteFile();
                break;
            case 3:
                addContentsToFile();
                break;
            case 4:
                overwriteFile();
                break;
            case 5:
                displayDirectoryContents();
                break;
            case 6:
                displayFileContents();
                break;
            case 0:

                return 0;
        }
    }
}

//Required functions
void createDirectory() {
    // Get directory name and construct directory path
    std::cout << "\n";
    std::cout << "Let's create a directory!\n";
    std::string directoryName;
    while (true) {
        std::cout << "Enter directory name: ";
        std::cin >> directoryName;
        if (directoryName.find("/") == std::string::npos) {
            break;
        }
        std::cout << "Directory name cannot contain a slash\n";
    }
    directoryName = (directoryName == "q") ? "my_test_dir" : directoryName; // For testing purposes
    std::string homeDirectory = getHomeDirectory();
    std::string directoryPath = homeDirectory + "/" + directoryName;

    // Create directory IN MEMORY
    directoryObject.init(directoryName, directoryPath);

    // Check if directory already exists
    struct stat statbuf;
    if (stat(directoryPath.c_str(), &statbuf) == 0) {
        std::cout << "Loading existing directory\n\n";
        loadExistingDirectory();
    } else {
        // Create directory IN FILE SYSTEM
        if (mkdir(directoryPath.c_str(), 0777) == -1) {
            std::cout << "Error creating directory in " + homeDirectory << std::endl;
            exit(1);
        }
        std::cout << "Directory created in " + homeDirectory << "\n\n";
    }

    return;
}

void loadExistingDirectory() {
    // Open directory
    std::string directoryPath = directoryObject.getDirectoryPath();
    DIR* dir = opendir(directoryPath.c_str());
    if (!dir) {
        std::cerr << "Error: Failed to open directory " << directoryPath << std::endl;
        exit(1);
    }

    // Read each entry in the directory
    struct dirent* entry;
    while ((entry = readdir(dir))) {
        std::string fileName = entry->d_name;

        // Ignore directories and hidden files
        // Ignores '.' and '..' files
        if (entry->d_type == DT_DIR || fileName[0] == '.') {
            continue;
        }
        
        // Create file IN FILE SYSTEM and get file size
        std::string filePath = directoryPath + "/" + fileName;
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Failed to open file " << fileName << std::endl;
            continue;
        } 
        if (stat(filePath.c_str(), &statbuf) == -1) {
            std::cout << "Error getting file size" << std::endl;
            return;
        }
        int fileSize = statbuf.st_size;
        
        // Read contents of file, create file IN MEMORY
        std::string contents;
        std::getline(file, contents);
        directoryObject.addFile(fileName, contents, fileSize);

        file.close();
    }

    closedir(dir);
}

void createFile() {
    // Get file name from user and validate it
    std::string fileName;
    while (true) {
        std::cout << "\n";
        std::cout << "Enter the name of the file you'd like to add: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        getline(std::cin, fileName);
        if (fileName.find("/") != std::string::npos) {
            std::cout << "File name cannot contain a slash\n";
        } else if (fileName.length() == 0) {
            std::cout << "File must have a name\n";
        } else {
            break;
        }
    }
    std::string filePath = directoryObject.getDirectoryPath() + "/" + fileName;

    // Check if file already exists
    if (stat(filePath.c_str(), &statbuf) == 0) {
        std::cout << "File already exists.\n";
        return;
    }

    // Create file IN FILE SYSTEM
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cout << "Error creating file\n";
        return;
    }
    std::string contents;
    if (promptWriteToFile()) {
        std::cout << "\n";
        std::cout << "Enter the information you'd like to write to the file: ";
        std::cout << "\n";
        getline(std::cin, contents);
        outFile << contents;
    }
    outFile.close();


    // Create file IN MEMORY and add it to the directory object
    int fileSize = getFileSize(filePath);
    directoryObject.addFile(fileName, contents, fileSize);
    // std::cout << "File created in " + filePath + "\n";

    return;
}

void deleteFile() {
    // Print directory files and get file number from user
    int choice = getFileIndex("Which file would you like to delete?");
    if (choice == -1) {
        return;
    }

    // Delete file corresponding to user input using unlink command
    std::string fileName = directoryObject.getFileNameAtPosition(choice - 1);
    std::string filePath = directoryObject.getDirectoryPath() + "/" + fileName;
    if (unlink(filePath.c_str()) == -1) {
        std::cout << "Error deleting file\n";
        return;
    }

    // Delete file object from directory object
    directoryObject.deleteFile(choice - 1);

    return;
}

void addContentsToFile() {
    // Print directory files and get file number from user
    int choice = getFileIndex("Which file would you like to add contents to?");
    if (choice == -1) {
        return;
    }

    // Open file for appending
    File* file = directoryObject.getFile(choice - 1);
    std::string filePath = directoryObject.getDirectoryPath() + "/" + file->getFileName();
    std::ofstream outFile(filePath, std::ios_base::app);
    if (!outFile) {
        std::cout << "Error opening file\n";
        return;
    }

    // Get contents from user and append it to the file
    std::cout << "Enter the contents to add: ";
    std::string contents;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    getline(std::cin, contents);
    outFile << contents;
    outFile.close();

    // Update file object in directory object
    file->addFileContents(contents);
    file->setFileSize(getFileSize(filePath));

    return;    
}

void overwriteFile() {
    // Print directory files and get file number from user
    int choice = getFileIndex("Which file would you like to overwrite?");
    if (choice == -1) {
        return;
    }

    // Open file for writing
    File* file = directoryObject.getFile(choice - 1);
    std::string filePath = directoryObject.getDirectoryPath() + "/" + file->getFileName();
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cout << "Error opening file\n";
        return;
    }

    // Get contents from user and overwrite the file
    std::cout << "Enter the contents to overwrite the file with: ";
    std::string contents;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    getline(std::cin, contents);
    outFile << contents;
    outFile.close();

    // Update file object in directory object
    file->setFileContents(contents);
    file->setFileSize(getFileSize(filePath));

    return;
}

void displayDirectoryContents() {
    std::cout << directoryObject.getDirectoryContents();
    return;
}

void displayFileContents() {
    // Print directory files and get file number from user
    int choice = getFileIndex("Which file would you like to display?");
    if (choice == -1) {
        return;
    }

    // Print file corresponding to user input
    File* file = directoryObject.getFile(choice - 1);
    std::cout << "\n";
    std::cout << file->getFileName() << ":" << std::endl;
    std::cout << file->getFileContents() << std::endl;

    return;
}

// Helper functions
std::string getHomeDirectory() {
    // Get home directory
    uid_t uid = getuid();
    struct passwd* pw = getpwuid(uid);
    if (pw == nullptr) {
        std::cout << "User information could not be found" << std::endl;
        exit(1);
    }
    std::string homeDirectory = pw->pw_dir;
    return homeDirectory;
}

void printMenu() {
    std::cout << "1. Create File\n";
    std::cout << "2. Delete File\n";
    std::cout << "3. Add Contents to File\n";
    std::cout << "4. Overwrite File\n";
    std::cout << "5. Display Directory Contents\n";
    std::cout << "6. Display File Contents\n";
    std::cout << "0. Exit\n";
    return;
}

int validateMenuInput(std::string str, int min, int max) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]) || str.length() > 3) {
            return -1;
        }
    }
    int choice = std::stoi(str);
    if (choice < min || choice > max) {
        return -1;
    }
    return choice;
}

bool promptWriteToFile() {
    std::string userInput = "";
    bool writeToFile;
    static bool first = true;
    while (true) {
        std::cout << "\n";
        std::cout << "Would you like to write anything to the file?\n";
        std::cout << "Y. Yes\n";
        std::cout << "N. No\n";
        //IMPORTANT: FLUSHES INPUT STREAM
        if (!first) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        getline(std::cin, userInput);
        if (userInput == "N" || userInput == "n") {
            writeToFile = false;
            break;
        } else if (userInput == "Y" || userInput == "y" || userInput.empty()) {
            writeToFile = true;
            break;
        }
    }
    first = false;
    return writeToFile;
}

int getFileIndex(std::string prompt) {
    int choice;
    int lastFileIndex = directoryObject.getNumFiles();
    while (true) {
        std::cout << "\n\n";
        std::cout << prompt; // Example: "Which file would you like to display?"
        std::cout << "\n\n";

        displayDirectoryContents();
        std::cout << "\t" << (lastFileIndex + 1) << ". Nevermind\n"; // Example: 5. Nevermind

        std::cout << "\n";
        std::string userInput;
        std::cin >> userInput;
        choice = validateMenuInput(userInput, 1, lastFileIndex + 1);
        if (choice == -1) {
            std::cout << "Invalid input\n";
            continue;
        } else if (choice == lastFileIndex + 1) {
            return -1; // User chose Nevermind
        }
        break;
    }

    return choice;
}

int getFileSize(std::string filePath) {
    if (stat(filePath.c_str(), &statbuf) == -1) {
        std::cout << "Error getting file size\n";
        return -1;
    }
    return statbuf.st_size;
}
