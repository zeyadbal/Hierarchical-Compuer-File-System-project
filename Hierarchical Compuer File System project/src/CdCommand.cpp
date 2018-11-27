#include "Commands.h"
#include "algorithm"

/*
 * class CdCommand : public BaseCommand {
private:
	bool found;
public:
	CdCommand(string args);
	void execute(FileSystem & fs);
	string toString();
	bool getFoundVal();
};
 */


CdCommand::CdCommand(string args): BaseCommand(args) , found() {
	if( verbose == 2 || verbose == 3){
		cout << "cd" << ' ' << args << endl;
	}
}

string CdCommand::toString(){ string st; st+="cd "; st+=this->getArgs(); return st;}

bool CdCommand::getFoundVal(){ return found; }

void CdCommand::execute(FileSystem & fs){


	this->found=false;

	if(this->getArgs()=="" && fs.getRootDirectory().getName()=="/"){
		found=true;
		return;
	}

	//if args is an absolute path
	if(this->getArgs().at(0)=='/'){

		for(unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
			if(fs.getallDirectories()[i]->getAbsolutePath() == this->getArgs() ){
				found=true;
				fs.setWorkingDirectory(fs.getallDirectories()[i]);
				return;
			}
		}
	}


	string predictedPath;
	if( this->getArgs().at(0)=='/'){
		predictedPath=this->getArgs();  //this line has been added
	}
	else if(fs.getWorkingDirectory().getName()=="/" && this->getArgs().at(0)!='/'){
		predictedPath = "/" + this->getArgs(); // "/" has been added to the head of the string
	}
	else if(fs.getWorkingDirectory().getName()!="/" && this->getArgs().at(0)!='/'){
		predictedPath = "/"+this->getArgs();
		predictedPath = fs.getWorkingDirectory().getAbsolutePath() + predictedPath;  //this line has been added
	}

	if(!found){//if args is an relative path

		for(unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
			if(fs.getallDirectories()[i]->getAbsolutePath() == predictedPath ){
				found=true;
				fs.setWorkingDirectory(fs.getallDirectories()[i]);
				return;
			}
		}
	}

	if(found) return;

	if(!found){ // the path may be a relative path and contains "../"



			//convert from from args as string to args as vector

			vector<string>argsAsVector;
			string st;
			unsigned int i=0;
			while(i < this->getArgs().length()){
				if(this->getArgs().at(i)=='/'){
					argsAsVector.insert(argsAsVector.end(),st+="/"); //begin has been changed to end
					st="";
				}
				else{
					st+=this->getArgs().at(i);	}

				i++;
			}
			argsAsVector.insert(argsAsVector.end(),st); //add the last dir which doesn't end with a slash


			Directory *workingDirectory = fs.getWorkingDirectoryAddress();
			bool stop = false;
			while (argsAsVector.size() > 0 && !stop){
				if(argsAsVector.at(0) == "../" || argsAsVector.at(0) == ".."){
					if(fs.getWorkingDirectory().getName() == "/"){
						cout << "The system cannot find the path specified" << endl;
						fs.setWorkingDirectory(workingDirectory);
						return;
					}
					else{
						fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
						argsAsVector.erase(argsAsVector.begin());
					}
				}
				else{
					stop = true;
				}
			}


			if(argsAsVector.size() == 0){ //this means the args contained only ".."
				found=true;
				return;
			}





			// add the args as vector to the end of the current working directory absolute path vector


			vector<string>workingDirectoryAbsPathAsVector;
			//check if the path is absolute or relative
			if(argsAsVector.at(0) == "/"){ //the path is an absolute path and may contain ".."
				workingDirectoryAbsPathAsVector = argsAsVector;

			}
			else{ //the path is an relative path and may contain ".."
				workingDirectoryAbsPathAsVector= fs.getWorkingDirectory().getPathAsVector();
				int k = 0;
				if(fs.getWorkingDirectory().getName() != "/"){
					workingDirectoryAbsPathAsVector.insert(workingDirectoryAbsPathAsVector.end() , "/" + argsAsVector.at(0));
					k++;
				}

				for (unsigned int j = k; j < argsAsVector.size(); j++){
					workingDirectoryAbsPathAsVector.insert(workingDirectoryAbsPathAsVector.end() , argsAsVector.at(j)); //begin has been changed to end
				}
			}

			//checks if the new path is legal


			//searching the directories located right before the backslashes

			/**
			 * erasing elements in positions other than the vector end causes the container
			 *  to relocate all the elements after the segment erased to their new positions
			 *    IS THIS IS TRUE???
			 */











			//vector<string>toBeDeleted;
			for(unsigned int i=0; i<workingDirectoryAbsPathAsVector.size(); i++){
				if(workingDirectoryAbsPathAsVector[i] == "../" || workingDirectoryAbsPathAsVector[i] == ".."){
					int parentIndex = i-1;
					if(workingDirectoryAbsPathAsVector.at(parentIndex) == "/"){
						cout << "The system cannot find the path specified" << endl;
						return;
					}
					//update the vector to be the original one without the backslash and the directory located right before him
					workingDirectoryAbsPathAsVector.erase(workingDirectoryAbsPathAsVector.begin() + i);
					i--;
					workingDirectoryAbsPathAsVector.erase(workingDirectoryAbsPathAsVector.begin() + i);
					i--;
				}
			}

			//now we have the current path followed by the relative path ( after executing the backslashes )
			//convert the vector to string

			string finalSt;



			unsigned j = 0;
			for ( j = 0; j < workingDirectoryAbsPathAsVector.size() - 1; j++){
				finalSt += workingDirectoryAbsPathAsVector.at(j);
			}


			if(workingDirectoryAbsPathAsVector.size() > 0){
				if(workingDirectoryAbsPathAsVector.size() == 1 && workingDirectoryAbsPathAsVector.at(0) == "/"){
					//do nothing
				}
				else{
					string secondLastWord = workingDirectoryAbsPathAsVector.at(j-1);
					if(secondLastWord.at(secondLastWord.length() - 1) != '/'){
						finalSt = finalSt + "/" + workingDirectoryAbsPathAsVector.at(j);
					}
					else{
						finalSt += workingDirectoryAbsPathAsVector.at(j);
					}

					if (finalSt.at(finalSt.length() - 1) == '/'){
						finalSt = finalSt.substr(0 , finalSt.length() - 1);
					}
				}
			}

			for (unsigned int s = 0; s < finalSt.length() - 1; s++){
				if(finalSt.at(s) == '/' && finalSt.at(s+1) == '/'){
					finalSt = finalSt.substr(0 , s) + finalSt.substr(s+1 , finalSt.length());
				}
			}
			//check if the finalSt is an existing path


			for(unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
				if(fs.getallDirectories()[i]->getAbsolutePath() == finalSt ){
					found=true;
					fs.setWorkingDirectory(fs.getallDirectories()[i]);
				}
			}

		}
		if(!found){
			cout << "The system cannot find the path specified" << endl;
			return;
		}
	}
