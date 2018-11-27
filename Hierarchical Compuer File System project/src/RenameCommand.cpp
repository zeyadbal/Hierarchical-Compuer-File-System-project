#include "Commands.h"

/*
 * class RenameCommand : public BaseCommand {
private:
public:
	RenameCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};
 */


RenameCommand::RenameCommand(string args): BaseCommand(args) {
	if( verbose == 2 || verbose == 3){
		cout << "rename" << ' ' << args << endl;
	}
}
string RenameCommand::toString(){ string st; st+="rename "; st+=this->getArgs(); return st;}

void RenameCommand::execute(FileSystem & fs){


	string path;
	string newName;

	//break the args into sourcePath, destinationPath


	string s;
	string workingArgs=this->getArgs();
	unsigned int i=workingArgs.size()-1;
	string c;
	string key;
	bool flag=false;
	while(i>=0){
		c=workingArgs.at(i);
		if(c==" "){
			newName=workingArgs.substr(i+1);
			path=my_subtring(workingArgs,0,i);
			break;

		}
		else{
			i--;
		}
	}

	////
	s="";

	string sourcePath_path;
	string file_dir_name;
	workingArgs=path;
	i=workingArgs.size()-1;
	key="";
	flag=false;
	while(i>=0){
		c=workingArgs.at(i);
		if(c=="/"){
			file_dir_name=workingArgs.substr(i+1);
			sourcePath_path=my_subtring(workingArgs,0,i);
			flag=true;
			break;
		}
		else {
			if(i==0 && !flag ){//means the path is null?
				file_dir_name=workingArgs;
				sourcePath_path="";
				break;
			}
			i--;
		}
	}


	/* trying to rename the working directory
	 *
	 */
	if(file_dir_name==fs.getWorkingDirectory().getName()){
		cout << "Can't rename the working directory"<<endl;
		return;
	}

	for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
		if(fs.getWorkingDirectory().getChildren().at(i)->getName() == newName){
			return;
		}
	}




	bool found=false;

	//if path is legal


	Directory *currDir=fs.getWorkingDirectoryAddress();// a pointer to the curr working directory

	int vrbs=verbose;
	verbose=0;
	CdCommand cdCMD2(sourcePath_path);
	cdCMD2.execute(fs);

	for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
			if(fs.getWorkingDirectory().getChildren().at(i)->getName() == newName){
			//	cout << "Can't rename the working directory"<<endl;
				fs.setWorkingDirectory(currDir);
				verbose=vrbs;
				return;
			}
		}


	if(!cdCMD2.getFoundVal()){	cout<<"No such file or directory"<<endl;	return; }
	else{
		bool exist=false;
		for(int i=0; !exist && i<fs.getWorkingDirectory().getChildrenVectorlength(); i++){
			if(fs.getWorkingDirectory().getChildren().at(i)->getName() == file_dir_name){
				exist=true;
			}
		}
		if(!exist){
			cout<<"No such file or directory"<<endl;
			fs.setWorkingDirectory(currDir);
			verbose=vrbs;
			return;
		}
	}

	fs.setWorkingDirectory(currDir);

	//other wise, sourcePath_path, sourcePath_file_dir_name, destinationPath are existing


	CdCommand cdCMD(sourcePath_path);
	cdCMD.execute(fs);

	for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
			if(fs.getWorkingDirectory().getChildren().at(i)->getName() == newName){
				fs.setWorkingDirectory(currDir);
				verbose=vrbs;
				return;
			}
		}
	found=false;
	for(unsigned int i=0; !found && i<fs.getWorkingDirectory().getChildren().size(); i++){
		if(fs.getWorkingDirectory().getChildren()[i]->getName() == file_dir_name){
			found=true;
			BaseFile* file_dir= fs.getWorkingDirectory().getChildren()[i];
			file_dir->setName(newName);
		}
	}
	if(!found){
		//throw an exception
	}
	fs.setWorkingDirectory(currDir);// switch back to the original working directory
	verbose=vrbs;
	return;

	}
