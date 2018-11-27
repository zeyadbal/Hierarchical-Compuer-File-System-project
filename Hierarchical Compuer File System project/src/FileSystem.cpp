#include "FileSystem.h"
#include <algorithm>
#include <vector>

/*
class FileSystem {
private:
	Directory* rootDirectory;
	Directory* workingDirectory;
	vector<Directory*> allDirectories;
	vector<Directory*> getallDirectories();
public:
	FileSystem();
	Directory& getRootDirectory() const; // Return reference to the root directory
	Directory& getWorkingDirectory() const; // Return reference to the working directory
	void setWorkingDirectory(Directory *newWorkingDirectory); // Change the working directory of the file system


};
 *
 */





FileSystem::FileSystem(): rootDirectory(new Directory("/",nullptr)) , workingDirectory(rootDirectory) , allDirectories() , allFilesPaths(){

	this->allDirectories.push_back(rootDirectory);
}



Directory& FileSystem::getRootDirectory() const{
	return *(this->rootDirectory);
}

Directory& FileSystem::getWorkingDirectory() const{
	return *(this->workingDirectory);
}

void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory){



	this->workingDirectory=newWorkingDirectory;

	bool found=false;
	for(unsigned int i=0; !found && i<allDirectories.size(); i++){
		if(allDirectories[i]->getAbsolutePath() == newWorkingDirectory->getAbsolutePath()){
			found=true;
		}
	}
		if(!found){

			this->allDirectories.push_back(newWorkingDirectory);
		}
}

void FileSystem::addDirectoryToAllDirectories(Directory *newWorkingDirectory){

	bool found=false;
	for(unsigned int i=0; !found && i<allDirectories.size(); i++){
		if(allDirectories[i]->getAbsolutePath() == newWorkingDirectory->getAbsolutePath()){
			found=true;
		}
	}
	if(!found){
		this->allDirectories.push_back(newWorkingDirectory);
	}
}

void FileSystem::setRootDirectory(Directory *newRootDirectory){
	this->rootDirectory= newRootDirectory;
}

vector<Directory*> FileSystem::getallDirectories() const{
	return this->allDirectories;
}
vector<Directory*> FileSystem::getallDirectories() {
	return this->allDirectories;
}


Directory* FileSystem::getWorkingDirectoryAddress(){
	return this->workingDirectory;
}

Directory* FileSystem::getRootDirectoryAddress(){
	return this->rootDirectory;
}


///rule of 5
FileSystem::FileSystem(const FileSystem& other): rootDirectory() , workingDirectory() , allDirectories(),allFilesPaths() {
	if( verbose == 1 || verbose==3 ){
		cout << "FileSystem::FileSystem(const FileSystem &other)" << endl;
	}
	clean();
	rootDirectory= new Directory(other.getRootDirectory());
	workingDirectory= rootDirectory;
}

FileSystem::FileSystem(FileSystem&& other): rootDirectory(other.rootDirectory) , workingDirectory(other.workingDirectory) , allDirectories(),allFilesPaths() {
	if( verbose == 1 || verbose==3 ){
		cout << "FileSystem::FileSystem(FileSystem&& other)" << endl;
	}
	clean();
	other.rootDirectory=nullptr;
	other.workingDirectory=nullptr;
	for(unsigned int i=0; i<other.allDirectories.size(); i++){
		allDirectories.push_back(other.allDirectories.at(i));
		other.allDirectories.at(i)=nullptr;
	}
}

FileSystem& FileSystem::operator=(const FileSystem& rhs){
	if( verbose == 1 || verbose==3 ){
		cout << "FileSystem& FileSystem::operator=(const FileSystem& rhs)" << endl;
	}
	if (&rhs != this){
		clean();
	}
	rootDirectory= new Directory(rhs.getRootDirectory());
	workingDirectory= rootDirectory;
	return *this;
}

FileSystem& FileSystem::operator=(FileSystem &&rhs){
	if( verbose == 1 || verbose==3 ){
		cout << "FileSystem& FileSystem::operator=(FileSystem &&rhs)" << endl;
	}
	rootDirectory= rhs.rootDirectory;
	workingDirectory= rhs.workingDirectory;
	rhs.rootDirectory=nullptr;
	rhs.workingDirectory=nullptr;
	for(unsigned int i=0; i<rhs.allDirectories.size(); i++){
		allDirectories.push_back(rhs.allDirectories.at(i));
		rhs.allDirectories.at(i)=nullptr;
	}
	return *this;
}



FileSystem::~FileSystem(){
	if( verbose == 1 || verbose==3 ){
		cout << "FileSystem::~FileSystem()" << endl;
	}
	clean();
}
void FileSystem::removeFromAllDirectories(string path){
	for(unsigned int i=0; i<allDirectories.size(); i++){
		 string::size_type loc = (allDirectories.at(i)->getAbsolutePath()).find(path);
					 if( loc != string::npos ) {
						  allDirectories.erase( allDirectories.begin()+i);
						  i--;

					  }
		}
		}


void FileSystem::clean(){


	delete rootDirectory;


}
void FileSystem::addFilePathToAllFilesPaths(string path){

	allFilesPaths.push_back(path);
}

vector<string> FileSystem::getAllFilesPaths(){
	return allFilesPaths;
}
