#include "Files.h"



	BaseFile::BaseFile(string name): name_(name){}

	string BaseFile::getName() const{
		return name_;
	}

	void BaseFile::setName(string newName){
		name_=newName;
	}
	BaseFile::~BaseFile(){};




