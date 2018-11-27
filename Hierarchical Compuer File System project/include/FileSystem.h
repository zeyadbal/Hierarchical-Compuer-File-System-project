#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Files.h"
#include <iostream>
#include "GlobalVariables.h"

class FileSystem {
private:
	Directory* rootDirectory;
	Directory* workingDirectory;
	vector<Directory*> allDirectories;
	vector<string>allFilesPaths;
	void copyallDirectories(const FileSystem &other);
	void steal(FileSystem& other);
	void clean();

public:
	FileSystem();
	FileSystem(const FileSystem &other);
	FileSystem(FileSystem&& other);
	FileSystem& operator=(const FileSystem& rhs);
	FileSystem& operator=(FileSystem &&rhs);
	virtual ~FileSystem();
	Directory& getRootDirectory() const; // Return reference to the root directory
	Directory& getWorkingDirectory() const; // Return reference to the working directory
	void setWorkingDirectory(Directory *newWorkingDirectory); // Change the working directory of the file system
	void setRootDirectory(Directory *newWorkingDirectory); // Change the working directory of the file system
	vector<Directory*> getallDirectories()const;
	vector<Directory*> getallDirectories();
	Directory* getWorkingDirectoryAddress();
	Directory* getRootDirectoryAddress();
	void addDirectoryToAllDirectories(Directory *newWorkingDirectory);
	void removeFromAllDirectories(string file_dir_name);
	void removeChildFromChildrenVector(int i);
	void addFilePathToAllFilesPaths(string path);
	vector<string> getAllFilesPaths();


};


#endif
