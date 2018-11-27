#include "Commands.h"

/*
 * class ExecCommand : public BaseCommand {
private:
	const vector<BaseCommand *> & history;
public:
	ExecCommand(string args, const vector<BaseCommand *> & history);
	void execute(FileSystem & fs);
	string toString();
};
 */

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> & history): BaseCommand(args) , history(history){
	if( verbose == 2 || verbose == 3){
		cout << "exec" << ' ' << args << endl;
	}

}
string ExecCommand::toString(){ string st; st+="exec "; st+=this->getArgs(); return st; }

int ExecCommand::convertToInt(string st){
	int sum=0;
	for(unsigned int i=0; i<st.size(); i++){
		sum+= (int)st.at(i);
	}
	return sum;
}
void ExecCommand::execute(FileSystem & fs){

	  int k = atoi(this->getArgs().c_str());
	 int historySize=history.size();
	if( k<0 || k>=historySize){//illegal number
		cout << "Command not found"<<endl;
	}
	else history.at(k)->execute(fs);
}

