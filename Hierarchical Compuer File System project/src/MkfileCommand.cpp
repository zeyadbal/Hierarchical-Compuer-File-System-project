#include "Commands.h"
#include <string>
/*
 * class MkfileCommand : public BaseCommand {
private:
public:
	MkfileCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};
 */


MkfileCommand::MkfileCommand(string args): BaseCommand(args){
	if( verbose == 2 || verbose == 3){
		cout << "mkfile" << ' ' << args << endl;
	}
}

string MkfileCommand::toString(){ string st; st+="mkfile "; st+=this->getArgs(); return st;}

void MkfileCommand::execute(FileSystem & fs){

	//break the args into path, filename, size


	string path;
	string filename;
	string s;
	unsigned int size;
	string workingArgs=this->getArgs();
	unsigned int i=workingArgs.size()-1;
	string c;
	string key;
	bool flag=false;
	while(i>=0){
		c=workingArgs.at(i);
		if(c==" "){
			string st=workingArgs.substr(i+1);
			size = atoi(st.c_str());
			s=my_subtring(workingArgs,0,i);
			workingArgs=s;
			i--;

		}


		else{
			if(c=="/"){
				filename= workingArgs.substr(i+1);
				s=my_subtring(workingArgs,0,i);
				workingArgs=s;
				path=workingArgs;
				flag=true;
				break;
			}
			else {
				if(i==0 && !flag ){//means the path is null?
					filename=workingArgs;
					path="";
					break;
				}
				i--;
			}
		}
	}


	bool found=false;

	//if path is an absolute path
	string thisPath;
	if(path==""){
		for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
			if(fs.getWorkingDirectory().getChildren().at(i)->getName() == filename){
				cout << "File already exists" << endl;
				return;
			}
		}
		fs.getWorkingDirectory().addFile(new File(filename,size));
		if(fs.getWorkingDirectory().getName()!="/"){
		 thisPath=fs.getWorkingDirectory().getAbsolutePath()+"/"+filename;
		}
		else {thisPath=fs.getWorkingDirectory().getAbsolutePath()+filename;}

		fs.addFilePathToAllFilesPaths(thisPath);
		return;
	}


	if(path.at(0)=='/'){

		for(unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
			if(fs.getallDirectories()[i]->getAbsolutePath() == path ){
				found=true;
				for( int j=0; j<fs.getallDirectories()[i]->getChildrenVectorlength(); j++){
					if(fs.getallDirectories()[i]->getChildren().at(j)->getName() == filename){
						cout << "File already exists" << endl;
						return;
					}
					else{
						fs.getallDirectories()[i]->addFile(new File(filename,size));
						string thisPath=fs.getallDirectories()[i]->getAbsolutePath()+"/"+filename;
						fs.addFilePathToAllFilesPaths(thisPath);
						return;
					}
				}
			}
		}

		//The system cannot find the path

	}

	if(found) return;


	string predictedPath;
	if(fs.getWorkingDirectory().getName()=="/" && path.at(0)=='/'){
		predictedPath=path.substr(1);
	}
	if(fs.getWorkingDirectory().getName()!="/" && path.at(0)=='/'){
		predictedPath=path;
	}
	if(fs.getWorkingDirectory().getName()=="/" && path.at(0)!='/'){
		predictedPath=path;
	}
	if(fs.getWorkingDirectory().getName()!="/" && path.at(0)!='/'){
		predictedPath="/"+path;
	}


	predictedPath=fs.getWorkingDirectory().getAbsolutePath()+predictedPath;

	if(!found){//if args is an relative path
		for(unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
			if(fs.getallDirectories()[i]->getAbsolutePath() == predictedPath ){
				found=true;
				if(fs.getallDirectories()[i]->getChildrenVectorlength()==0){//if the dir have no files/dirs at all
					fs.getallDirectories()[i]->addFile(new File(filename,size));
					string thisPath=fs.getallDirectories()[i]->getAbsolutePath()+"/"+filename;
					fs.addFilePathToAllFilesPaths(thisPath);
					return;
				}
				else{
					for( int j=0; j<fs.getallDirectories()[i]->getChildrenVectorlength(); j++){
						if(fs.getallDirectories()[i]->getName() == filename){
							cout << "The directory already exists" << endl;
							return;
						}
						if(fs.getallDirectories()[i]->getChildren().at(j)->getName() == filename){
							cout << "File already exists" << endl;
							return;
						}
					}

					fs.getallDirectories()[i]->addFile(new File(filename,size));
					string thisPath=fs.getallDirectories()[i]->getAbsolutePath()+"/"+filename;
					fs.addFilePathToAllFilesPaths(thisPath);
					return;
				}
			}
		}
	}



	//if <path> doesnt exist

	if(!found){//means the path does not exists
		cout << "The system cannot find the path specified" << endl;
		return;
	}
}

