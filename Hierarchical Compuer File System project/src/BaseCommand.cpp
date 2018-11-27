#include "Commands.h"


/*
 * class BaseCommand {
private:
	string args_;

public:
	BaseCommand(string args);
	string getArgs();
	virtual void execute(FileSystem & fs) = 0;
	virtual string toString() = 0;
};
 */


	BaseCommand::BaseCommand(string args): args(args){}


	string BaseCommand::getArgs(){
		return this->args;
}
	 BaseCommand::~BaseCommand(){

	}
	 string BaseCommand::my_subtring(string st, int start, int end){
         return st.substr(start,end-start);
	 }
