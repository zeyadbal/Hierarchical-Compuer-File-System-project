#include "Commands.h"

/*
 * class MkdirCommand : public BaseCommand {
private:
public:
	MkdirCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};
 */

MkdirCommand::MkdirCommand(string args): BaseCommand(args){
	if( verbose == 2 || verbose == 3){
		cout << "mkdir" << ' ' << args << endl;
	}
}
string MkdirCommand::toString() { string st; st+="mkdir "; st+=this->getArgs(); return st;}

void MkdirCommand::execute(FileSystem & fs){

	string path;
	string dirname;
	string s;
	string workingArgs=this->getArgs();
	unsigned int i=workingArgs.size()-1;
	string c;
	string key;
	bool flag=false;
	while(i>=0){
		c=workingArgs.at(i);
		if(c=="/"){
			dirname= workingArgs.substr(i+1);
			s=my_subtring(workingArgs,0,i);
			workingArgs=s;
			path=workingArgs;
			flag=true;
			break;
		}
		else {
			if(i==0 && !flag ){//means the path is null?
				dirname=workingArgs;
				path="";
				break;
			}
			i--;
		}
	}

	string predictedPath;
	if(path==""){
		predictedPath="/"+dirname;
	}
	else{//means that the path!="" and its a relative
		//	if(found) return;

		if(path.at(0)=='/'){
			predictedPath=path;  //this line has been added
		}
		else if(fs.getWorkingDirectory().getName()=="/" && path.at(0)!='/'){
			predictedPath = "/" + this->getArgs(); // "/" has been added to the head of the string
		}
		else if(fs.getWorkingDirectory().getName()!="/" && path.at(0)!='/'){
			predictedPath = "/"+path;
			predictedPath = fs.getWorkingDirectory().getAbsolutePath() + predictedPath;  //this line has been added
		}
	}
	//if args is an relative path

	bool found=false;
	if(fs.getWorkingDirectory().getAbsolutePath() == predictedPath){
		found=true;
		cout << "The directory already exists" << endl;
		return;
	}
	for(unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
		if(fs.getallDirectories()[i]->getAbsolutePath() == predictedPath ){
			if(fs.getallDirectories()[i]->getName() == dirname){
				cout << "The directory already exists" << endl;
				return;
			}
			for(unsigned int j=0; !found && j<fs.getallDirectories()[i]->getChildren().size(); j++){
				if(fs.getallDirectories()[i]->getChildren().at(j)->getName() == dirname){
					cout << "The directory already exists" << endl;
					return;
				}
			}
		}
	}
	for(unsigned int i=0; i<fs.getAllFilesPaths().size(); i++){
		 string::size_type loc = predictedPath.find(fs.getAllFilesPaths().at(i));
						 if( loc != string::npos ) {
			cout << "The directory already exists" << endl;
								return;
		}
	}

	//convert from args as string to args as vector

	if(path==""){
		Directory* newDir=new Directory(dirname,nullptr);
		newDir->setParent(fs.getWorkingDirectoryAddress());
		fs.getWorkingDirectory().addFile(newDir);

		fs.addDirectoryToAllDirectories(newDir);
		return;
	}
	vector<string>argsAsVector;
	string st;
	i=0;
	if(path!=""){
		while(path!="" && i < path.length()){
			if(path.at(i)=='/'){
				argsAsVector.push_back(st+='/');
				st="";
			}
			else{
				st+=path.at(i);	}
			i++;
		}
		if(st!=""){
			argsAsVector.push_back(st);
		}

	}


	//
	//  abs path: search if the path exists, if yes, create there.
	// else, search if the path without the last dir exist, if yes, create there.
	// and so on.. till you get to the root. (if you get there, create a new dir there




	vector<string>pathToBeCreated;

	argsAsVector.push_back(dirname);


	unsigned int k= argsAsVector.size()-1;
	while(k>=0){
		unsigned int b=argsAsVector.at(k).size();
		if(argsAsVector.at(k)!="/" && argsAsVector.at(k).at(b-1)=='/'){
			string newlast=argsAsVector.at(k).substr(0,b-1);
			argsAsVector.pop_back();
			argsAsVector.push_back(newlast);
		}
		pathToBeCreated.insert(pathToBeCreated.begin(),argsAsVector.at(k));


		argsAsVector.pop_back();

		//convert args as vector to args as string (after updated)
		string st="";
		if(k>0){
			//		cout<<"k in for:"<<k<<endl;
			for( unsigned int i=0; i<argsAsVector.size(); i++){
				st+= argsAsVector[i];
			}
		}
		//check if the currpath exists

		if(st==""){
			st="/"+st;
		}
		else if(st!="/"){
			if(st.at(st.length()-1)=='/'){
				st=st.substr(0,st.length()-1);
			}
			st="/"+st;
		}

		if(st=="/"){
			st=fs.getWorkingDirectory().getAbsolutePath();
		}
		Directory* currDir;


		for( unsigned int i=0; !found && i<fs.getallDirectories().size(); i++){
			if(fs.getallDirectories()[i]->getAbsolutePath() == st ){

				found=true;
				currDir=fs.getallDirectories()[i];
			}
		}
		if(found){//the currpath exists, create here!

			//create a new directories series according to the currpath

			vector<Directory*>newDirs;

			for( unsigned int i=0; i<pathToBeCreated.size(); i++){

				newDirs.push_back( new Directory( pathToBeCreated[i] ,  nullptr));
			}
			for( unsigned int i=0; i<newDirs.size()-1; i++){
				newDirs[i]->addFile(newDirs[i+1]);
			}
			for(unsigned int i=newDirs.size()-1; i>0; i--){
				newDirs[i]->setParent(newDirs[i-1]);
			}

			currDir->addFile(newDirs[0]);
			newDirs[0]->setParent(currDir);

			for(unsigned int p=0; p<pathToBeCreated.size(); p++){
				fs.addDirectoryToAllDirectories(newDirs[p]);
			}
			return;
		}

		else{
			k--;
		}

	}

}




