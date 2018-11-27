#include "Commands.h"

/*
 * class MvCommand : public BaseCommand {
private:
public:
	MvCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};
 */

MvCommand::MvCommand(string args): BaseCommand(args){
	if( verbose == 2 || verbose == 3){
		cout << "mv" << ' ' << args << endl;
	}
}
string MvCommand::toString(){ string st; st+="mv "; st+=this->getArgs(); return st;}

void MvCommand::execute(FileSystem & fs){



	//break the args into sourcePath, destinationPath

	string sourcePath;
	string destinationPath;

	string s;
	string workingArgs=this->getArgs();
	int i=workingArgs.size()-1;
	string c;
	string key;
	bool flag=false;
	while(i>=0){
		c=workingArgs.at(i);
		if(c==" "){
			destinationPath=workingArgs.substr(i+1);
			sourcePath=my_subtring(workingArgs,0,i);
			break;

		}
		else{
			i--;
		}
	}

	////
	s="";
	string spareSourcePath=sourcePath;
	string sourcePath_path;
	string sourcePath_file_dir_name;
	workingArgs=sourcePath;
	i=workingArgs.size()-1;
	key="";
	flag=false;
	while(i>=0){
		c=workingArgs.at(i);
		if(c=="/"){
			sourcePath_file_dir_name=workingArgs.substr(i+1);
			sourcePath_path=my_subtring(workingArgs,0,i);
			flag=true;
			break;
		}
		else {
			if(i==0 && !flag ){//means the path is null?
				sourcePath_file_dir_name=workingArgs;
				sourcePath_path="";
				break;
			}
			i--;
		}
	}

	//check if the destinationPath exists
	int vrbs=verbose;
	verbose=0;
	Directory *currDir=fs.getWorkingDirectoryAddress();// a pointer to the curr working directory
	CdCommand cdCMD1(destinationPath);
	cdCMD1.execute(fs);
	if(!cdCMD1.getFoundVal()){	cout<<"No such file or directory"<<endl;verbose=vrbs;	return; }
	else{
		fs.setWorkingDirectory(currDir);
	}

	//check if the sourcePath: by checking if the sourcePath_path exist and contain a file/dir with name sourcePath_file_dir_name

	CdCommand cdCMD2(sourcePath_path);
	cdCMD2.execute(fs);



	if(!cdCMD2.getFoundVal()){	cout<<"No such file or directory"<<endl;verbose=vrbs;	return; }
	else{
		bool exist=false;
		for(int i=0; !exist && i<fs.getWorkingDirectory().getChildrenVectorlength(); i++){
			if(fs.getWorkingDirectory().getChildren().at(i)->getName() == sourcePath_file_dir_name){
				exist=true;
			}
		}
		if(!exist){
			cout<<"No such file or directory"<<endl;
			verbose=vrbs;
			return;
		}
	}

	fs.setWorkingDirectory(currDir);

	//other wise, sourcePath_path, sourcePath_file_dir_name, destinationPath are existing


	BaseFile* file_dir;
	CdCommand cdCMD3(sourcePath_path);
	cdCMD3.execute(fs);
	vector<Directory*>predicted_Dirs;
	bool found=false;
	for(unsigned int i=0; !found && i<fs.getWorkingDirectory().getChildren().size(); i++){
			if(fs.getWorkingDirectory().getChildren()[i]->getName() == sourcePath_file_dir_name){

				if(fs.getWorkingDirectory().getChildren()[i]->isFile()){
					found=true;
					file_dir=new File(((File&)(*fs.getWorkingDirectory().getChildren()[i])));
		//	fs.getWorkingDirectory().removeFile(sourcePath_file_dir_name);
					fs.getWorkingDirectory().removeFile(fs.getWorkingDirectory().getChildren()[i]);
					fs.setWorkingDirectory(currDir);

					CdCommand cdCMD4(destinationPath);
					cdCMD4.execute(fs);

					//check if the goal dir is having the same file as filename
					bool existingAFileWithASameNameOrtheFileDoesntExist=false;
					for(unsigned int i=0; !existingAFileWithASameNameOrtheFileDoesntExist && i<fs.getWorkingDirectory().getChildren().size(); i++){
						if(fs.getWorkingDirectory().getChildren()[i]->getName() == sourcePath_file_dir_name){
							existingAFileWithASameNameOrtheFileDoesntExist=true;
							cout << "No such file or directory"<<endl;
							delete file_dir;
							fs.setWorkingDirectory(currDir);
							verbose=vrbs;
							return;
						}
					}

					fs.setWorkingDirectory(currDir);
					cdCMD3.execute(fs);


				fs.getWorkingDirectory().removeFile(sourcePath_file_dir_name);

					fs.setWorkingDirectory(currDir);
					cdCMD4.execute(fs);

					fs.getWorkingDirectory().addFile(file_dir);

					fs.setWorkingDirectory(currDir);
					verbose=vrbs;
					return;
				}
				else{
					fs.removeFromAllDirectories(sourcePath_file_dir_name);
					file_dir=new Directory(((Directory&&)(*fs.getWorkingDirectory().getChildren()[i])));

					fs.setWorkingDirectory(currDir);

					CdCommand cdCMD4(destinationPath);
					cdCMD4.execute(fs);

					//check if the goal dir is having the same file as filename
					bool existingAFileWithASameNameOrtheFileDoesntExist=false;
					for(unsigned int i=0; !existingAFileWithASameNameOrtheFileDoesntExist && i<fs.getWorkingDirectory().getChildren().size(); i++){
						if(fs.getWorkingDirectory().getChildren()[i]->getName() == sourcePath_file_dir_name){
							existingAFileWithASameNameOrtheFileDoesntExist=true;
							cout << "No such file or directory"<<endl;
							delete file_dir;
							fs.setWorkingDirectory(currDir);
							verbose=vrbs;
							return;
						}
					}

					fs.setWorkingDirectory(currDir);
					cdCMD3.execute(fs);

					fs.setWorkingDirectory(currDir);
					cdCMD4.execute(fs);


					((Directory&)(*file_dir)).setParent(fs.getWorkingDirectoryAddress());
					fs.getWorkingDirectory().addFile(file_dir);

					fs.addDirectoryToAllDirectories((Directory*) file_dir);
					addAllChildsToFsAllDirectoriesRecursively( fs, (Directory*) file_dir);

					fs.setWorkingDirectory(currDir);
					verbose=vrbs;
					return;





			}
		}
	}

}



void MvCommand::addAllChildsToFsAllDirectoriesRecursively(FileSystem &fs, Directory *newDir){


	if(newDir==nullptr)return;


	for(int i=0; i<(*newDir).getChildrenVectorlength(); i++){
		if( ! (*newDir).getChildren().at(i)->isFile()){
			fs.addDirectoryToAllDirectories((Directory*)(*newDir).getChildren().at(i));
			addAllChildsToFsAllDirectoriesRecursively( fs, (Directory*)((*newDir).getChildren().at(i)) );
		}

	}

}



