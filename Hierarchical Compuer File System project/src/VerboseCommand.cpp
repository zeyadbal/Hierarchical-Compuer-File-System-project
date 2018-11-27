#include "Commands.h"


/*
 * class VerboseCommand : public BaseCommand {
private:
public:
	VerboseCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};
 */

VerboseCommand::VerboseCommand(string args): BaseCommand(args){
	if( verbose == 2 || verbose == 3){
		cout << "verbose" << ' ' << args << endl;
	}
}
string VerboseCommand::toString(){ string st; st+="verbose "; st+=this->getArgs(); return st;}


void VerboseCommand::execute(FileSystem & fs){


	unsigned int v;

	if(this->getArgs() == "0"){
		v=0; }
	else if(this->getArgs() == "1"){
		v=1; }
	else if(this->getArgs() == "2"){
		v=2; }
	else if(this->getArgs() == "3"){
		v=3; }
	else {
		cout << "Wrong verbose input" << endl;
		v=verbose;
	}

	verbose=v;

}
