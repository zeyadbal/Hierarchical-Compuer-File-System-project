#include "Commands.h"

/*
 * class RmCommand : public BaseCommand {
private:
public:
	RmCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};
 */



RmCommand::RmCommand(string args) : BaseCommand(args) {
	if( verbose == 2 || verbose == 3){
		cout << "rm" << ' ' << args << endl;
	}
}

string RmCommand::toString(){ string st; st+="rm "; st+=this->getArgs(); return st;}

void RmCommand::execute(FileSystem& fs){

	string workingArgs=this->getArgs();

	if(workingArgs=="")return;

	if (fs.getWorkingDirectory().getAbsolutePath() == this->getArgs() || fs.getRootDirectory().getName() == this->getArgs()){
		cout << "Can't remove directory";
	}


	string path;
	string file_dir_name;
	string s;
	unsigned int i=workingArgs.size()-1;
	string c;
	string key;
	bool flag=false;
	while(i>=0){
		c=workingArgs.at(i);
		if(c=="/"){
			file_dir_name= workingArgs.substr(i+1);
			s=my_subtring(workingArgs,0,i);
			workingArgs=s;
			path=workingArgs;
			flag=true;
			break;
		}
		else {
			if(i==0 && !flag ){//means the path is null?
				file_dir_name=workingArgs;
				path="";
				break;
			}
			i--;
		}
	}

	string predictedPath;
	if(path==""){
		predictedPath=fs.getWorkingDirectory().getAbsolutePath();
	}
	else{//means that the path!="" and its a relative
		//	if(found) return;

		if(path.at(0)=='/'){
			predictedPath=path;  //this line has been added
		}
		else if(fs.getWorkingDirectory().getName()=="/" && path.at(0)!='/'){
			predictedPath = "/" + path; // "/" has been added to the head of the string
		}
		else if(fs.getWorkingDirectory().getName()!="/" && path.at(0)!='/'){
			predictedPath = "/"+path;
			predictedPath = fs.getWorkingDirectory().getAbsolutePath() + predictedPath;  //this line has been added
		}
	}


	bool found=false;
	for(unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
		if(fs.getallDirectories()[i]->getAbsolutePath() == predictedPath ){
			for(unsigned int j=0; !found && j<fs.getallDirectories()[i]->getChildren().size(); j++){
				if(fs.getallDirectories()[i]->getChildren().at(j)->getName() == file_dir_name){

					if( ! fs.getallDirectories()[i]->getChildren().at(j)->isFile()){
						fs.removeFromAllDirectories( ((Directory&)(*fs.getallDirectories()[i]->getChildren().at(j))).getAbsolutePath() );
					}
					fs.getallDirectories()[i]->removeFile(file_dir_name);
					found=true;
					return;
				}
			}
		}
	}

	if(!found){

		if(predictedPath==""){// delete the file_dir_name in 'this'

			for(int i=0; i<fs.getWorkingDirectory().getChildrenVectorlength(); i++){
				if(fs.getWorkingDirectory().getChildren().at(i)->getName() == file_dir_name){
					if( ! fs.getallDirectories()[i]->getChildren().at(i)->isFile()){
						fs.removeFromAllDirectories( ((Directory&)(*fs.getallDirectories()[i]->getChildren().at(i))).getAbsolutePath() );
					}
	fs.getWorkingDirectory().removeFile(file_dir_name);
					found=true;
					return;
				}
			}
		}
	}
	if(!found){

		//means the path exists and there is an file with the same name as dir
		cout << "No such file or directory" << endl;
		return;
	}
}

