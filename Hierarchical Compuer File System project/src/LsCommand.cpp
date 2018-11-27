#include "Commands.h"

/*
 * class LsCommand : public BaseCommand {
private:
public:
	LsCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};
 */

LsCommand::LsCommand(string args): BaseCommand(args) , myargs() {
	if( verbose == 2 || verbose == 3){
		if(this->getArgs() == ""){
			cout << "ls" <<endl;
		}
		else{
			cout << "ls" << ' ' << args << endl;
		}
	}
}
string LsCommand::toString(){ string st; st+="ls "; st+=this->getArgs(); return st;}

void LsCommand::execute(FileSystem & fs){



	vector<BaseFile*>sortedByName;
	vector<BaseFile*>sortedBySize;

	fs.getWorkingDirectory().sortByName();
	for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
		sortedByName.push_back(fs.getWorkingDirectory().getChildren()[i]);
	}

	fs.getWorkingDirectory().sortBySize();
	for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
		sortedBySize.push_back(fs.getWorkingDirectory().getChildren()[i]);
	}




	string st;
	unsigned int size;
	if(this->getArgs() == ""){

		for (unsigned int i=0; i<sortedByName.size(); i++){

			if(sortedByName.at(i)->isFile()){

				size= sortedByName.at(i)->getSize();
				string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
				st+="FILE";
				st+='\t';
				st+=sortedByName.at(i)->getName();
				st+='\t';
				st+=sizeAsString;
				cout << st << endl;
				st="";
				size=0;
				sizeAsString="";
			}
			else{//Directory

				size= sortedByName.at(i)->getSize();
				string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
				st+="DIR";
				st+='\t';
				st+=sortedByName.at(i)->getName();
				st+='\t';
				st+=sizeAsString;
				cout << st << endl;
				st="";
				size=0;
				sizeAsString="";
			}
		}
		return;
	}
	else if(this->getArgs().substr(0,2) != "-s"){  // ls <path>
		int vrbs=verbose;
		verbose=0;

		sortedByName.clear();
		sortedBySize.clear();


		CdCommand cd=CdCommand(this->getArgs());

		Directory *currDir=fs.getWorkingDirectoryAddress();// a pointer to the curr working directory
		CdCommand cdCMD(this->getArgs());

		cdCMD.execute(fs);//the working directory has changed
		if(cdCMD.getFoundVal()==false){
			verbose=vrbs;
			return;
		}

		fs.getWorkingDirectory().sortByName();
		for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
			sortedByName.push_back(fs.getWorkingDirectory().getChildren()[i]);
		}

		fs.getWorkingDirectory().sortBySize();
		for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
			sortedBySize.push_back(fs.getWorkingDirectory().getChildren()[i]);
		}




		string st;
		unsigned int size;

		for (unsigned int i=0; i<sortedByName.size(); i++){

			if(sortedByName.at(i)->isFile()){

				size= sortedByName.at(i)->getSize();
				string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
				st+="FILE";
				st+='\t';
				st+=sortedByName.at(i)->getName();
				st+='\t';
				st+=sizeAsString;
				cout << st << endl;
				st="";
				size=0;
				sizeAsString="";
			}
			else{//Directory

				size= sortedByName.at(i)->getSize();
				string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
				st+="DIR";
				st+='\t';
				st+=sortedByName.at(i)->getName();
				st+='\t';
				st+=sizeAsString;
				cout << st << endl;
				st="";
				size=0;
				sizeAsString="";
			}
		}
		fs.setWorkingDirectory(currDir);// switch back to the original working directory
		verbose=vrbs;
		return;

	}

	else{
		if(this->getArgs() == "-s"){


			bool changed=false;
			unsigned int i=0;
			unsigned int j;
			while(i<sortedBySize.size()-1){
				j=i+1;
				while( j<sortedBySize.size() && sortedBySize[i]->getSize()==sortedBySize[j]->getSize()){
					j++;
					changed=true;
				}
				if(changed){
					j--;
					//sort

					sort(sortedBySize.begin() + i , sortedBySize.begin() + j , []( BaseFile* lhs,  BaseFile* rhs){ return (*lhs).getName() < (*rhs).getName(); });
					i=j+1;
					changed=false;
				}
				else{
					i++;
				}
				//
			}

			//print



			for (unsigned int i=0; i<sortedBySize.size(); i++){

				if(sortedBySize.at(i)->isFile()){

					size= sortedBySize.at(i)->getSize();
					string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
					st+="FILE";
					st+='\t';
					st+=sortedBySize.at(i)->getName();
					st+='\t';
					st+=sizeAsString;
					cout << st << endl;
					st="";
					size=0;
					sizeAsString="";
				}
				else{//Directory

					size= sortedBySize.at(i)->getSize();
					string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
					st+="DIR";
					st+='\t';
					st+=sortedBySize.at(i)->getName();
					st+='\t';
					st+=sizeAsString;
					cout << st << endl;
					st="";
					size=0;
					sizeAsString="";
				}
			}

		}

		else{// -s <path>
			unsigned int vrbs=verbose;
					verbose=0;
			string s= this->getArgs().substr(3);
			sortedByName.clear();
			sortedBySize.clear();

			Directory *currDir=fs.getWorkingDirectoryAddress();// a pointer to the curr working directory
			CdCommand cdCMD(s);

			cdCMD.execute(fs);//the working directory has changed
			if(cdCMD.getFoundVal()==false){
				verbose=vrbs;
				return;
			}

			fs.getWorkingDirectory().sortByName();
			for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
				sortedByName.push_back(fs.getWorkingDirectory().getChildren()[i]);
			}

			fs.getWorkingDirectory().sortBySize();
			for(unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++){
				sortedBySize.push_back(fs.getWorkingDirectory().getChildren()[i]);
			}





			bool changed=false;
			unsigned int i=0;
			unsigned int j;
			while(i<sortedBySize.size()-1){
				j=i+1;
				while( j<sortedBySize.size() && sortedBySize[i]->getSize()==sortedBySize[j]->getSize()){
					j++;
					changed=true;
				}
				if(changed){
					j--;
					//sort

					sort(sortedBySize.begin() + i , sortedBySize.begin() + j , []( BaseFile* lhs,  BaseFile* rhs){ return (*lhs).getName() < (*rhs).getName(); });
					i=j+1;
					changed=false;
				}
				else{
					i++;
				}
				//
			}

			//print

			string st;

			for (unsigned int i=0; i<sortedBySize.size(); i++){

				if(sortedBySize.at(i)->isFile()){

					size= sortedBySize.at(i)->getSize();
					string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
					st+="FILE";
					st+='\t';
					st+=sortedBySize.at(i)->getName();
					st+='\t';
					st+=sizeAsString;
					cout << st << endl;
					st="";
					size=0;
					sizeAsString="";
				}
				else{//Directory

					size= sortedBySize.at(i)->getSize();
					string sizeAsString = static_cast<ostringstream*>( &(ostringstream() << size) )->str();
					st+="DIR";
					st+='\t';
					st+=sortedBySize.at(i)->getName();
					st+='\t';
					st+=sizeAsString;
					cout << st << endl;
					st="";
					size=0;
					sizeAsString="";
				}
			}


			fs.setWorkingDirectory(currDir);// switch back to the original working directory
			verbose=vrbs;
		}
	}



}





