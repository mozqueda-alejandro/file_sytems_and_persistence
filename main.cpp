#include <dirent.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Directory.h"


std::string directoryName;
std::string directoryPath; // In the form /home/user/my_directory
DIR* dir;
Directory directoryObject;

std::string getHomeDirectory();
void initializeDirectory();
void createDirectory();

void loadExistingDirectory();

void printMenu();
int validateMenuInput(std::string str);

bool writeToFile();

void createFile();
void deleteFile();
void addContentsToFile();
void overwriteFile();
void displayDirectoryContents();
void displayFileContents();


int main() {
    createDirectory();

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
        
        // Perform action based on user input
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
                // Close the directory
                closedir(dir);
                return 0;
        }
    }
}

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

void initializeDirectory() {
    dir = opendir(directoryPath.c_str());
    if (!dir) {
        std::cerr << "Error: Failed to open directory." << std::endl;
        exit(1);
    }
}

void createDirectory() {
    // Get directory name from user and validate it
    std::cout << "\n";
    std::cout << "Let's create a directory!\n";
    while (true) {
        std::cout << "Enter directory name: ";
        std::cin >> directoryName;
        if (directoryName.find("/") == std::string::npos) {
            break;
        }
        std::cout << "Directory name cannot contain a slash\n";
    }
    directoryPath = getHomeDirectory() + "/" + directoryName;
    directoryObject.init(directoryName);

    // Check if directory already exists
    struct stat statbuf;
    if (stat(directoryPath.c_str(), &statbuf) == 0) {
        std::cout << "Loading existing directory\n";
        loadExistingDirectory();
    } else {
        if (mkdir(directoryPath.c_str(), 0777) == -1) {
            std::cout << "Error creating directory\n";
            exit(1);
        }
        std::cout << "Directory created in " + directoryPath + "\n";
    }

    return;
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

void loadExistingDirectory() {
    // Read each entry in the directory
    initializeDirectory();
    struct dirent* entry;
    while ((entry = readdir(dir))) {
        // Ignore directories and hidden files
        if (entry->d_type == DT_DIR || entry->d_name[0] == '.') {
            continue;
        }
        
        // Open the file for reading
        std::string filePath = directoryPath + "/" + entry->d_name;
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Failed to open file " << entry->d_name << std::endl;
            continue;
        }
        
        // Read the contents of the file
        std::string contents;
        std::getline(file, contents);
        file.close();
        
        // Print the contents of the file
        std::cout << "File " << entry->d_name << " contains: " << contents << std::endl;
    }
}

int validateMenuInput(std::string str) {
    if (str.length() != 1 || !isdigit(str[0])) {
        return -1;
    }
    int choice = str[0] - '0';
    if (choice < 0 || choice > 6) {
        return -1;
    }
    return choice;
}

bool writeToFile() {
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
    std::string filePath = directoryPath + "/" + fileName;

    // Check if file already exists
    struct stat statbuf;
    if (stat(filePath.c_str(), &statbuf) == 0) {
        std::cout << "File already exists.\n";
        return;
    }

    // Create file
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cout << "Error creating file\n";
        return;
    }
    if (writeToFile()) {
        std::string userInput;
        std::cout << "Enter the information you'd like to write to the file: ";
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        getline(std::cin, userInput);
        outFile << userInput;
    }

    outFile.close();
    std::cout << "File created in " + filePath + "\n";
    return;
}

void deleteFile() {

}

void addContentsToFile() {

}

void overwriteFile() {

}

void displayDirectoryContents() {
    {
    // initializeDirectory();
    // std::cout << "\n";
    // std::cout << directoryName << std::endl;
    // struct dirent* entry;
    // int i = 1;
    // while ((entry = readdir(dir))) {
    //     // Ignore directories and hidden files
    //     if (entry->d_type == DT_DIR || entry->d_name[0] == '.') {
    //         continue;
    //     }
    //     std::cout << "\t" << i << ". " << entry->d_name << std::endl;
    //     i++;
    // }
    }


    std::cout << "Display directory contents successful\n";
}

void displayFileContents() {

}
