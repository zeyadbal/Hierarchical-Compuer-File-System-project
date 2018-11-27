#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>

using namespace std;

class BaseFile {
private:
	string name_;
	
public:
	BaseFile(string name);
	string getName() const;
	void setName(string newName);
	virtual int getSize() = 0;
	virtual bool isFile() = 0;
	virtual ~BaseFile();
};

class File : public BaseFile {
private:
	int size_;
		
public:
	File(string name, int size); // Constructor
	bool isFile();
	 int getSize(); // Return the size of the file
//	 virtual ~File();
	
};

class Directory : public BaseFile {
private:
	vector<BaseFile*> children_;
	Directory *parent_;
	vector<string>myPath;
	void getAbsPath();
	void copyChildren(const Directory& other);
	void copyPath(Directory& other);
	void steal(Directory& other);
	void clean();
	static bool ByName( BaseFile& d1,  BaseFile& d2);
	static bool BySize( BaseFile& d1,  BaseFile& d2);


public:

	Directory(string name, Directory *parent); // Constructor
	Directory(const Directory& rhs);
	Directory(Directory&& rhs);
	Directory& operator=(const Directory& rhs);
	Directory& operator=(Directory&& rhs);
	virtual ~Directory();
	Directory *getParent() const; // Return a pointer to the parent of this directory
	void setParent(Directory *newParent); // Change the parent of this directory
	void addFile(BaseFile* file); // Add the file to children
	void removeFile(string name); // Remove the file with the specified name from children
	void removeFile(BaseFile* file); // Remove the file from children
	void sortByName(); // Sort children by name alphabetically (not recursively)
	void sortBySize(); // Sort children by size (not recursively)
	vector<BaseFile*> getChildren(); // Return children
	 int getSize(); // Return the size of the directory (recursively)
	string getAbsolutePath();  //Return the path from the root to this
	vector<string> getPathAsVector() ;
	bool isFile();
	int getChildrenVectorlength();
};

#endif
