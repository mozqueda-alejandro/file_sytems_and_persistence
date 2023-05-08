# Single Level Directory Simulator

![CS446](https://user-images.githubusercontent.com/89401406/236718533-05297241-7f28-48c0-9612-6dc7103fe49b.png)

This program is designed to simulate a single level directory system in Linux. It allows the user to create files, append to them, overwrite, and/or delete them. Additionally, the user can display all the directory's files and can display a file's contents. The program automatically retrieves the user's home directory based on the machine it runs on and makes all file changes immediately.

## Usage

The program can be compiled and executed from the command line by running the following commands:

```
make
./singleLevelDirectory
```

## Function Definitions

The program provides the following functions for manipulating files and directories:

- `void createFile();`: Creates a new file with the given filename.
- `void addContentsToFile();`: Adds contents to a file with the given filename.
- `void overwriteFile();`: Overwrites the contents of the file with the given filename with the given content.
- `void deleteFile();`: Deletes the file with the given filename.
- `void displayDirectoryContents();`: Lists all files in the current directory.
- `void displayFileContents();`: Displays the contents of the file with the given filename.

## Changes from original specifications

This program differs from the original specifications in that it makes changes to the files immediately and records any changes in memory through the `Directory` and `File` classes as previously required. As a result, there is no `updateFilesInDirectory()` function.
