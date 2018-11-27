#include "Files.h"
#include <typeinfo>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "GlobalVariables.h"
/*
class Directory : public BaseFile {
private:
	vector<BaseFile*> children_;
	Directory *parent_;
	vector<string>myPath;
	void getAbsPath();
	void copyChildren(const Directory& other);
	void steal(Directory& other);
	void clean();

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
	vector<string> getPathAsVector();
	void addDirectory(BaseFile* newDirectory);

};
 */


Directory::Directory(string name, Directory *parent): BaseFile(name)  , children_(), parent_(parent) , myPath()   { }

Directory* Directory::getParent() const{
	return parent_;
}

void Directory::setParent(Directory *newParent){
	parent_=newParent;
}

void Directory::addFile(BaseFile* file){

	children_.push_back(file);
}

vector<string> Directory::getPathAsVector(){
	Directory* currParent=parent_;
	string st;
	myPath.clear();
	if(currParent==nullptr){
		st= "/";
	}
	myPath.insert(myPath.begin(), this->getName());
	while(currParent != nullptr){
		if(currParent->getName()=="/"){
			myPath.insert(myPath.begin(),"/");
			break;
		}
		else{

			string st=(*currParent).getName();
			st+="/";
			myPath.insert(myPath.begin(),  st );
		}
		currParent=currParent->getParent();
	}
	return myPath;
}





void Directory::sortByName(){
	sort(children_.begin(), children_.end(), []( BaseFile* lhs,  BaseFile* rhs){ return (*lhs).getName() < (*rhs).getName(); });
}


void Directory::sortBySize(){
	sort(children_.begin(), children_.end(), []( BaseFile* lhs,  BaseFile* rhs){ return (*lhs).getSize() < (*rhs).getSize(); });
}



vector<BaseFile*> Directory::getChildren(){
	return children_;
}

int Directory::getChildrenVectorlength(){
	return children_.size();
}


int Directory::getSize(){
	int sum=0;
	for (unsigned int i=0; i<children_.size(); i++){
		BaseFile* curr=children_[i];
		sum+=(*curr).getSize();
	}
	return sum;
}

string Directory::getAbsolutePath(){
	string st;
	myPath.clear();
	Directory* currParent=parent_;
	if(currParent==nullptr){
		st= '/';
		return st;
	}
	myPath.insert(myPath.begin(), this->getName());
	while(currParent != nullptr){
		myPath.insert(myPath.begin(),  (*currParent).getName() + "/");
		currParent=currParent->getParent();
	}
	for (vector<string>::iterator it=myPath.begin(); it!=myPath.end(); it++)
		st+=*it;

	return st.substr(1);
}

Directory::Directory(const Directory& rhs): BaseFile(rhs.getName()) , children_() , parent_(rhs.getParent()), myPath() {

	if(verbose == 1 || verbose==3){
		cout << "Directory::Directory(const Directory& rhs)" << endl;
	}
	clean();


	copyChildren(rhs);

	for(unsigned int i=0; i<rhs.myPath.size(); i++){
		this->myPath.push_back(rhs.myPath.at(i));
	}
}

Directory::Directory(Directory&& rhs):BaseFile(rhs.getName()) , children_() , parent_() , myPath() {
	if(verbose == 1 || verbose==3){
		cout << "Directory::Directory(Directory&& rhs)" << endl;
	}
	steal(rhs);

}


Directory& Directory::operator=(const Directory& rhs) {
	if(verbose == 1 || verbose==3){
		cout << "Directory& Directory::operator=(const Directory& rhs)" << endl;
	}
	if (&rhs != this) {
		clean();
	}
	if(rhs.getParent() != nullptr){
		this->parent_=new Directory(*rhs.getParent());
	}
	else this->parent_= nullptr;
	copyChildren(rhs);
	for(unsigned int i=0; i<rhs.myPath.size(); i++){
		this->myPath.push_back(rhs.myPath.at(i));
	}
	return *this;
}

Directory& Directory::operator=(Directory&& rhs) {
	if(verbose == 1 || verbose==3){
		cout << "Directory& Directory::operator=(Directory&& rhs)" << endl;
	}
	clean();
	steal(rhs);
	for(unsigned int i=0; i<rhs.myPath.size(); i++){
		this->myPath.push_back(rhs.myPath.at(i));
	}
	return *this;
}

void Directory::removeFile(string name){
	bool notFound=false;
	for(unsigned int i=0; !notFound && i<children_.size() ; i++){
		if( (*children_[i]).getName() == name ){
			notFound=true;
			BaseFile *toBeDeleted= children_.at(i);
			children_.at(i)=nullptr;
			children_.erase(children_.begin()+i);
			delete toBeDeleted;

		}
	}
}

void Directory::removeFile(BaseFile* file){

	bool notFound=false;
	for(unsigned int i=0; !notFound && i<children_.size() ; i++){
		if( children_[i]==file ){
			notFound=true;
			BaseFile *toBeDeleted= children_[i];
			children_[i]=nullptr;
			children_.erase(children_.begin()+i);
			if( ! toBeDeleted->isFile()){
				((Directory&)*toBeDeleted).setParent(nullptr);
			}
			delete toBeDeleted;
		}
	}
}

Directory::~Directory(){
	if(verbose == 1 || verbose==3){
		cout << "Directory::~Directory()" << endl;
	}
	clean();
}

void Directory::clean() {

	for(unsigned int i=0; i<children_.size(); i++){
		if( ! children_[i]->isFile()){
			((Directory&)(*children_[i])).setParent(nullptr);
		}
		delete children_[i];
	}
	children_.clear();
	myPath.clear();

}



bool Directory::isFile(){
	return false;
}

void Directory::copyChildren(const Directory& other){
	for(unsigned int i=0;i<other.children_.size(); i++){
		if(other.children_[i]->isFile()){

			children_.push_back( new File((File&)(*other.children_[i])   ));
		}
		else{ //Directory

			children_.push_back( new Directory((Directory&)(*other.children_[i])   ));
			((Directory&)(*other.children_[i])).setParent(this);
		}
	}
}


void Directory::steal(Directory& other){

	for(unsigned int i=0;i<other.children_.size(); i++){
		children_.push_back(other.children_[i]);
		if(!other.children_.at(i)->isFile()){
		((Directory&)(*other.children_[i])).setParent(this);
		}
		other.children_[i]=nullptr;
		delete other.children_[i];
	}

	other.children_.clear();

	if(other.parent_!=nullptr){
		for(unsigned int i=0; i<other.parent_->children_.size(); i++){
			if(other.parent_->children_.at(i)->getName() == other.getName() ){
				Directory* toBeDeleted=(Directory*)(other.parent_->children_.at(i));
				other.parent_->children_.erase(  other.parent_->children_.begin() + i  );
				((Directory&)(*toBeDeleted)).setParent(nullptr);
				delete ((Directory&)(*toBeDeleted)).parent_;
			delete	toBeDeleted;
				break;

			}
		}
	}
}
