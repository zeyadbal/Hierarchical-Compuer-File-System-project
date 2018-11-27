#include "Commands.h"

/*
 * class HistoryCommand : public BaseCommand {
private:
	const vector<BaseCommand *> & history;
public:
	HistoryCommand(string args, const vector<BaseCommand *> & history);
	void execute(FileSystem & fs);
	string toString();
};
 */


HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> & history): BaseCommand(args) , history(history) {
	if( verbose == 2 || verbose == 3){
		cout << "history" << args << endl;
	}
}
string HistoryCommand::toString() { return "history";}

void HistoryCommand::execute(FileSystem & fs){

	if(history.size()==0) return;


	for(unsigned int i=0; i<history.size(); i++){

		cout << i << "\t" << history.at(i)->toString() << endl;

	}

}
