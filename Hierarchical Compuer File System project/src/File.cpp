#include "Files.h"


File::File(string name, int size):BaseFile(name) , size_(size){}

 int File::getSize(){
	return size_;
}

bool File::isFile(){
	return true;
}

