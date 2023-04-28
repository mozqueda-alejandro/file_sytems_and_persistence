
**<p align = "center"> CS446-Fall22-PA4: Simulating a single-level file system</p>**

**<p align = "center"> Due May 6th at 11:59 PM</p>**

**<p align = "center">Learning Outcomes</p>**
1. You will simulate directory and file data structures so that you gain a better understanding of the construction of each.   
2. You will translate your simulated directory and files into persistent entities using the filesystem API so that you gain a better understanding of the file system API commands.

**General Instructions and Hints**: 

-Do not change supplied file names. <br/>
-All code _must_ be written in C++. I **strongly** encourage you to use strings where it makes sense to do so. If you need to convert a string to a character array for low level c calls, you can use [c_str()](https://cplusplus.com/reference/string/string/c_str/). <br/>
-These instructions contain general descriptions of funcitonality. You are welcome to implement the code in whatever way makes the most sense to you, unless I explicitly tell you that it must be coded in a certain way. That means that function names, parameters, and return values are yours to choose. You should use helper functions in the main.cpp file to make your life easier- seriously, there are several spots in the directions where I recommend certain functionality be grouped into one function. You are allowed to ignore those suggestions, but that will result in really messy, hard to debug code. <br/>
-You must implement the same error checking as I have in the executable. If you do not implement it, you will lose a significant number of points. <br/>
-All output should match exactly what is shown in the executable (including spacing!). <br/>
-When part 1 is done, open a terminal and cd to your github repo, wherever you saved it. Do the following: _git add ._ then _git commit -m <whatevermessageyouwant>_ then _git push_.<br/>
-Your code must run in Ubuntu 18.04 <br/>
-All work should be done on a machine where you have sudoer permission. <br/>
-All work should be your own. <br/>

-I have provided an example executable named exemplar. Make sure you run it a few times so that you understand what the program is doing. You can fix permission denied errors with `chmod u+x <filename>`<br/>



**<p align = "center"> Part 1, Simulating a single-level file system</p>**
 **<p align = "center"> Background</p>** <br/>
Linux treats directories as specialized files with extra information, such as references to contained files and the . and .. links. In other words, we can think of a directory as being a special file that has a file name and a size, as well as a list of files contained within. Each file has a file name and contents. This is, of course, and extreme simplification, but it will help you better understand the classes I describe later.  

The operating system is responsible for helping translate these directories and files into a file system that is human readable. Usually, we have several directories associated with a file system. In our case, we will simplify things by creating a single root directory that contains all files and no subdirectories. This will allow us to look closely at the linux file system API, include the open, close, read, seek, and write operations (at a higher c++ level).

 
**<p align = "center">General Directions</p>** <br/>
Your program should consist of the following files:    
1. directory.cpp  
2. directory.h  
3. file.cpp  
4. file.h  
5. main.cpp  
6. makefile  

You are welcome to add additional files, but the properties of the Directory and File classes should not be changed from the provided description.   

This program should be robust, so you need to implement error checking. The majority of the errors possible in this program surround user data entry, so you will likely want to use [getline](https://www.geeksforgeeks.org/getline-string-c/) to get user string entries. Additionally, to check that user integer entries are valid, you should use the built in [cin](https://www.hackerearth.com/practice/notes/validating-user-input-in-c/) function calls. Personally, I typically check if cin was successful using its return, and if it wasn't, I clear cin and then use the cin ignore method so that random user entry doesn't break the program.  

You may only use the following libraries (using other libraries will result in a 0): <br/>
 ```
 sys (particularly types.h and stat.h)  
 fstream  
 dirent.h  
 pwd.h  
 unistd.h  
 limits
 iostream (and using namespace std if you want)  
 ```

**Note**: [Common coding practice](https://www.codecademy.com/resources/docs/cpp/classes) for class building is to leave properties as private access, and to set methods that are needed by outside classes as public.   

*Do not* make your properties public, as that defeats the purpose of using a class.  



_makefile_<br/>
This will build the program using the __make__ command. If you've forgotten how to construct one, no worries, [here's](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/) a  good resource from Colby college. Your executable should be named `singleLevelDirectory` <br/><br/>

_File_  
File is a class that you will declare in `file.h` and implement in `file.cpp`. This class is meant to represent a file. For our purposes, we want to track the following properties:  

```
file name (the name of the file)  
size in bytes (the size of the file in bytes)  
contents (the data that has been written to the file)  
```

You should have an explicitly declared default constructor, and you should have getters and setters for each property. You are welcome to add additional methods, such as a parameterized constructor and display functions, if you so choose.  

In File, I have a method called updateContents. It is responsible for taking existing file contents and concatenating new string entries to the file. You can do that in c++ using the + operator.



_Directory_    
Directory is a class that you will declare in `directory.h` and implement in `directory.cpp`. For our purposes, we want to track the following properties: 

```
directory name (name of the directory that will hold all of the files)  
files held in the directory (probably an array of files, though you can choose your data structure)  
number of files in the directory   
```

The maximum number of files we want to be able to hold in a single directory is 1000, which you can use to construct your array of files if you don't want to dynamically allocate them.    

In Directory, I have a method called updateFilesInDirectory. It is responsible for "removing" a deleted file from the file array by copying all elements after the selected entry into the element before and decreasing the number of files in the directory. This will overwrite the position in the array that corresponds to the user entry, and move all following file entries one element.  I also have a method called addFile. That method takes a file and places it at the end of the file array, then increments the number of files in the directory.  



_main.cpp_<br/>
This will be where your main function is stored. Remember, in C based languages, main must exist so that the compiler has an entry point into the program. The helper functions for main are described below. 



**<p align = "center">Assignment</p>**
You must implement the Directory and File classes as described above. You may add additional properties and methods as necessary. Properties should be private.  


main.cpp is going to be responsible for the majority of the work we're interested in- the classes are just there to model directory entries and files in the operating system. Relevant functionality is outlined below under function name headings. You may ignore my function suggestions, but you _must_ implement the functionality described by each function somewhere in your program so that your code functions in the same way as the executable. If I explicitly tell you to use a system call or library call, you must use it somewhere in your code to do the described work.   


_If you haven't already, I suggest running the provided executable so that you can have a general feel for behavior- otherwise these disjointed functionality descriptions may confuse you._

_int main()_  
This function is responsible for taking user input and presenting the main program menu (see the executable for what that looks like). I suggest that a default directory is constructed here, and then passed to a helper function to set the directory name and other values. A switch is also probably easier to use here to filter user input than a if/else cascade.  

_createDirectory_<br/>
**Funtionality**: <br/>
1. Prompt the user for directory name and get input.      
2. Construct a directory object and set its name using user input.   
3. Locate your user home directory path. For me, that would be `Users/sarad`. **Do NOT hardcode your home directory in or your code will not run for testing**.    

There are a variety of ways to get the user's home directory. I did it by using [getuid](https://man7.org/linux/man-pages/man2/getuid.2.html) to get the user running the program's uid, and then providing that to [getpwuid](https://pubs.opengroup.org/onlinepubs/009604499/functions/getpwuid.html) to create a [passwd struct](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/pwd.h.html) which has a property that allows you to get the user's home directory path, which you should cast to a string. Then you can append the directory's name to the home directory path, so that the directory is generated in the user's home directory.     

4. Use the path to the directory to check if it exists. This can be done using [stat](https://pubs.opengroup.org/onlinepubs/009696799/functions/stat.html), though there are other ways if you prefer.   

5. If the directory already exists in the user's home, the directory should be loaded, rather than overwritten. Otherwise, the location of the directory should be displayed.  

**Relevant Library Functions and constants**: getpwuid, getuid, c_str()<br/><br/>

_createFile_<br/>
**Funtionality**:<br/>
1. Prompt the user for file name, and store it.  
2. Check if the filename already exists in the directory.  
3. If the file doesn't exist, create it and prompt the user to add contents to the file if they want. If they want to add contents, get them and add them to the file. Then add the file to the directory object. Note: files should start with a file size of 0 bytes. If the file does exist, tell the user that the file exists.   
**Relevant Library Functions and constants**: cin.clear(), cin.ignore().<br/><br/>


_deleteFile_<br/>
**Funtionality**:<br/>
1. If there are files available to delete, ask the user which file they'd like to delete and display the files that exist in the directory object. Get the user choice.  If there aren't files in the directory, tell the user it's empty.   
2. Either using the updateFilesInDirectory method outlined above, or your own implementation, overwrite the file that was selected for removal.<br/><br/>


_addContentsToFile_<br/>
**Funtionality**:<br/>
1. Prompt the user for the data they want to add to the file's contents, and get their entry.   
2. Update the file's contents by concatenating the old contents with the user entry. I use the updateContents methods that I describe as part of the File class, but you can do it directly from main if you want to.</br></br>


_displayDirectoryContent_<br/>
**Funtionality**: <br/>
1. If there aren't any files in the directory, tell the user that there aren't any.  
2. Otherwise, display the directory name, and then iterate through each of the files in the directory to display their name and size.<br/><br/>


_displayFileContents_<br/>
**Funtionality**: <br/>
1. Display the file name, and then the file contents. <br/><br/>


_findFile_<br/>
**Funtionality**: <br/>
1. Iterate through all of the files in the directory and compare the user entered file name to each file's name in the directory to see if the filename you're looking for already exists in the directory. If it does, return the index of the file. Otherwise return an impossible number to flag for later use.<br/><br/>


_getUserInput_<br/>
**Funtionality**: <br/>
1. I use this function to call getline on the cin stream, and then return the filled string entry from the user.  
**Relevant Library Functions and constants**:getline()<br/><br/>


_overwriteFile_<br/>
**Funtionality**: <br/>
1. If there are files in the directory, display them to the user as a prompt, and then get their entry.  
2. Fully replace the existing contents of the file that was selected with the user entry.  
**Relevant Library Functions and constants**:cin.ignore()<br/><br/>


_constructFileSystem_<br/>
**Funtionality**: <br/>
1. Get the path to the user's home directory using the method you used to find it to create the path to the directory. Append the directory name to form a full path to the directory from the user home.  
2. Use the [mkdir](https://linux.die.net/man/1/mkdir) command to create a persistent directory with the same name as your directory. The user who creates the directory should have read, write, and execute privileges. Everyone else should have read permissions. If you do this correctly, you will see the directory appear in your user home directory.   
3. Iterate through the files stored in the directory object, and concatenate the directory path with the file name to get the file path.  
4. Use each file path to open a file in the directory that will persist. Then write the contents out to the file.
**Relevant Library Functions and constants**: ofstream (open, close), mkdir<br/><br/>


_loadExistingDir_<br/>
**Funtionality**: <br/>
1. After checking to see if a directory with the same name as the one entered by the user for creation exists (described in create directory), get the directory's full path from user home (the way you did earlier).  
2. Construct a [directory pointer](https://itecnote.com/tecnote/r-open-directory-using-c/) and a [dirent](https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html).    
3. Use the directory pointer to store the return from a call to [opendir](https://man7.org/linux/man-pages/man3/fdopendir.3.html).   
4. If it the return isn't null, use the [readdir](https://man7.org/linux/man-pages/man3/readdir.3.html) command on the directory pointer and store the return in the dirent struct that you created.  I used a while loop that checked if the call to readdir returned NULL because that will indicate you've reached the end.   
5. Get the file name from the [directory entry](http://books.gigatux.nl/mirror/kerneldevelopment/0672327201/ch12lev1sec7.html) and open an input file stream to it in binary using ios::binary. Then use [seekg](https://cplusplus.com/reference/istream/istream/seekg/) to read the file from the start to end.   
6. Use [tellg](https://cplusplus.com/reference/istream/istream/tellg/) to get the file size. Then clear the input file's stream, and reset seekg to the beginning of the file stream.  
7. Use your file stream to read the contents of the file.  
8. Construct a File object and set its properties. Add the file to the directory.  
9. Close the file at the end of each iteration. Close the directory using [closedir](https://man7.org/linux/man-pages/man3/closedir.3.html)
**Relevant Library Functions and constants**: directory pointer, dirent, opendir, readdir, seekg, tellg, closedir<br/><br/>



 **To Submit**<br/>
 When you are done, you should use git to git push the following to your assignment repo (see instructions above):
 1) all .cpp and .h files, and the makefile. DO NOT push your .o files or executable. Don't forget to submit your repo link through WebCampus!<br/>

You can submit as many times as you would like.
