#include <dirent.h>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


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

void createDirectory() {
    // Get home directory
    uid_t uid = getuid();
    struct passwd* pw = getpwuid(uid);

    if (pw == nullptr) {
        std::cout << "User information could not be found" << std::endl;
        exit(1);
    }

    std::string homeDirectory = pw->pw_dir;

    // Get directory name from user and validate it
    std::string directoryName;
    std::cout << "Let's create a directory!\n";

    while (true) {
        std::cout << "Enter directory name: ";
        std::cin >> directoryName;
        if (directoryName.find("/") != std::string::npos) {
            break;
        }
        std::cout << "Directory name cannot contain a slash\n";
    }

    // Get path to new directory
    std::string directoryPath = homeDirectory + "/" + directoryName;
    struct stat statbuf;
    if (stat(directoryName.c_str(), &statbuf) == 0) {
        std::cout << "Loading existing directory\n";
        loadExistingDirectory();
    } else {
        std::cout << "Directory created in " + directoryPath + "\n";
    }

    return;
}

void loadExistingDirectory() {

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

int main() {
    createDirectory();
    printMenu();

    int choice;
    while (true) {
        std::cout << "What would you like to do? ";
        std::string userInput;
        std::cin >> userInput;
        choice = validateMenuInput(userInput);
        if (choice != -1) {
            break;
        }
        std::cout << "Invalid input\n\n";
    }
    
    switch (choice) {
        case 1:
            createDirectory();
            break;
        
        default:
            break;
    }

    return 0;
}