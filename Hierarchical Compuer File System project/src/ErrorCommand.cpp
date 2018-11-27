#include "Commands.h"

/*
 * class ErrorCommand : public BaseCommand {
 private:
 public:
 ErrorCommand(string args);
 void execute(FileSystem & fs);
 string toString();
 };
 */

ErrorCommand::ErrorCommand(string args) :
BaseCommand(args) {
	if (verbose == 2 || verbose == 3) {


		cout << args << endl;
	}
}
string ErrorCommand::toString() {
	string st;
	st=this->getArgs();
	return st;
}

void ErrorCommand::execute(FileSystem & fs) {

	string fullCommand=this->getArgs();
	for(unsigned int i=0; i<fullCommand.size(); i++){
		if(fullCommand.at(i)==' '){
			string s= fullCommand.substr(0,i);
			fullCommand=s;
			break;
		}
	}

	cout <<fullCommand + ": " + "Unknown command" << endl;

}
