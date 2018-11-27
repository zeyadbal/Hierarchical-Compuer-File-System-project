#include "Commands.h"
#include <iostream>

/*
class PwdCommand : public BaseCommand {
private:
public:
	PwdCommand(string args);
	void execute(FileSystem & fs); // Every derived class should implement this function according to the document (pdf)
	virtual string toString();
};*/


PwdCommand::PwdCommand(string args):BaseCommand(args){
	if( verbose == 2 || verbose == 3){
		cout << "pwd"  << endl;
	}
}

string PwdCommand::toString(){ string st; st+="pwd "; st+=this->getArgs(); return st;}

void PwdCommand::execute(FileSystem & fs){
	cout << fs.getWorkingDirectory().getAbsolutePath() << endl;


}
