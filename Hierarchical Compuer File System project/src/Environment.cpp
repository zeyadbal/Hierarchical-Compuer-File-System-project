#include "Environment.h"
#include <iostream>
#include <string>
#include <typeinfo>
/*
 * class Environment {
private:
	vector<BaseCommand*> commandsHistory;
	FileSystem fs;

public:
	Environment();
	void start();
	FileSystem& getFileSystem(); // Get a reference to the file system
	void addToHistory(BaseCommand *command); // Add a new command to the history
	const vector<BaseCommand*>& getHistory() const; // Return a reference to the history of commands
};
 */


Environment::Environment(): commandsHistory() , fs() {}



void Environment::start(){

	string fullCommand;
	string cmdName;
	string args;
	cout << ">";
	getline(cin, fullCommand);

	while(fullCommand != "exit"){
		bool stop=false;
		for(unsigned int i=0; !stop &&i<fullCommand.length(); i++){
			if( fullCommand.at(i) == ' '){
				stop=true;
				cmdName= fullCommand.substr(0,i);
				args= fullCommand.substr(i+1);
				break;
			}
			else{if( i==0){
				if( fullCommand=="ls" || fullCommand=="Ls"){
					cmdName="ls";
				}
				else if( fullCommand=="history" || fullCommand=="History"){
					cmdName="history";
				}
				else if( fullCommand=="pwd" || fullCommand=="Pwd"){
									cmdName="pwd";
								}
				else{
					cmdName="error";
					args=fullCommand;
				}

			}
		}
		}


		cmdName+="Command";

		if(cmdName == "PwdCommand" || cmdName == "pwdCommand"){ PwdCommand *cmd1=new PwdCommand(args); addToHistory(cmd1); (*cmd1).execute(fs); }
		else if(cmdName == "CdCommand" || cmdName == "cdCommand"){ CdCommand *cmd2=new CdCommand(args); addToHistory(cmd2); (*cmd2).execute(fs); }
		else if(cmdName == "LsCommand" || cmdName == "lsCommand"){ LsCommand *cmd3=new LsCommand(args); addToHistory(cmd3); (*cmd3).execute(fs); }
		else if(cmdName == "MkdirCommand" || cmdName == "mkdirCommand"){ MkdirCommand *cmd4=new MkdirCommand(args); addToHistory(cmd4);  (*cmd4).execute(fs); }
		else if(cmdName == "MkfileCommand" || cmdName == "mkfileCommand"){ MkfileCommand *cmd5=new MkfileCommand(args); addToHistory(cmd5); (*cmd5).execute(fs); }
		else if(cmdName == "CpCommand" || cmdName == "cpCommand"){ CpCommand *cmd6=new CpCommand(args); addToHistory(cmd6); (*cmd6).execute(fs); }
		else if(cmdName == "MvCommand" || cmdName == "mvCommand"){ MvCommand *cmd7=new MvCommand(args); addToHistory(cmd7); (*cmd7).execute(fs); }
		else if(cmdName == "RenameCommand" || cmdName == "renameCommand"){ RenameCommand *cmd8=new RenameCommand(args); addToHistory(cmd8); (*cmd8).execute(fs); }
		else if(cmdName == "RmCommand" || cmdName == "rmCommand"){ RmCommand *cmd9=new RmCommand(args); addToHistory(cmd9); (*cmd9).execute(fs); }
		else if(cmdName == "HistoryCommand" || cmdName == "historyCommand"){ HistoryCommand *cmd10=new HistoryCommand(args, commandsHistory); (*cmd10).execute(fs); addToHistory(cmd10); }
		else if(cmdName == "VerboseCommand" || cmdName == "verboseCommand"){ VerboseCommand *cmd11=new VerboseCommand(args); addToHistory(cmd11); (*cmd11).execute(fs); }
		else if(cmdName == "ExecCommand" || cmdName == "execCommand"){ ExecCommand *cmd12=new ExecCommand(args, commandsHistory);  (*cmd12).execute(fs);addToHistory(cmd12); }
		else  {

			ErrorCommand *cmd13= new ErrorCommand(fullCommand); addToHistory(cmd13); (*cmd13).execute(fs);
		}


		fullCommand="";
		cmdName="";
		args="";
		cout << fs.getWorkingDirectory().getAbsolutePath() + ">" ;

		getline(cin, fullCommand);

	}
}


FileSystem& Environment::getFileSystem(){
	return fs;
}

void Environment::addToHistory(BaseCommand *command){
	commandsHistory.push_back(command);
}

const vector<BaseCommand*>& Environment::getHistory() const{
	return commandsHistory;
}


Environment::Environment(const Environment& rhs): commandsHistory() , fs(){
	if(verbose == 1 || verbose==3){

	}
	clean();
	for(unsigned int i=0; i<rhs.commandsHistory.size(); i++){
		if( typeid(*rhs.commandsHistory.at(i)) == typeid(PwdCommand)){ commandsHistory.push_back(new PwdCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(CdCommand)){ commandsHistory.push_back(new CdCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(LsCommand)){ commandsHistory.push_back(new LsCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(MkdirCommand)){ commandsHistory.push_back(new MkdirCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(MkfileCommand)){ commandsHistory.push_back(new MkfileCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(CpCommand)){ commandsHistory.push_back(new CpCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(MvCommand)){ commandsHistory.push_back(new MvCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(RenameCommand)){ commandsHistory.push_back(new RenameCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(RmCommand)){ commandsHistory.push_back(new RmCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(HistoryCommand)){ commandsHistory.push_back(new HistoryCommand((*rhs.commandsHistory.at(i)).getArgs() , rhs.commandsHistory)); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(VerboseCommand)){ commandsHistory.push_back(new VerboseCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(ExecCommand)){ commandsHistory.push_back(new ExecCommand((*rhs.commandsHistory.at(i)).getArgs() , rhs.commandsHistory)); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(ErrorCommand)){ commandsHistory.push_back(new ErrorCommand((*rhs.commandsHistory.at(i)).getArgs())); }
	}
	fs=FileSystem(rhs.fs);
}

Environment::Environment(Environment&& rhs): commandsHistory() , fs() {
	if(verbose == 1 || verbose==3){
		cout << "Environment::Environment(Environment&& rhs)" << endl;
	}
	clean();
	for(unsigned int i=0; i<rhs.commandsHistory.size(); i++){
		commandsHistory.push_back(rhs.commandsHistory[i]);
		rhs.commandsHistory[i]= nullptr;
	}
	fs=FileSystem( (FileSystem&&) rhs.fs);
	rhs.getFileSystem().setRootDirectory(nullptr);
	rhs.getFileSystem().setWorkingDirectory(nullptr);
}

Environment& Environment::operator=(const Environment& rhs){
	if(verbose == 1 || verbose==3){
		cout << "Environment& Environment::operator=(const Environment& rhs)" << endl;
	}
	if(this!=&rhs){
		clean();
	}
	for(unsigned int i=0; i<rhs.commandsHistory.size(); i++){
		if( typeid(*rhs.commandsHistory.at(i)) == typeid(PwdCommand)){ commandsHistory.push_back(new PwdCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(CdCommand)){ commandsHistory.push_back(new CdCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(LsCommand)){ commandsHistory.push_back(new LsCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(MkdirCommand)){ commandsHistory.push_back(new MkdirCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(MkfileCommand)){ commandsHistory.push_back(new MkfileCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(CpCommand)){ commandsHistory.push_back(new CpCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(MvCommand)){ commandsHistory.push_back(new MvCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(RenameCommand)){ commandsHistory.push_back(new RenameCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(RmCommand)){ commandsHistory.push_back(new RmCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(HistoryCommand)){ commandsHistory.push_back(new HistoryCommand((*rhs.commandsHistory.at(i)).getArgs() , rhs.commandsHistory)); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(VerboseCommand)){ commandsHistory.push_back(new VerboseCommand((*rhs.commandsHistory.at(i)).getArgs())); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(ExecCommand)){ commandsHistory.push_back(new ExecCommand((*rhs.commandsHistory.at(i)).getArgs() , rhs.commandsHistory)); }
		else if( typeid(*rhs.commandsHistory.at(i)) == typeid(ErrorCommand)){ commandsHistory.push_back(new ErrorCommand((*rhs.commandsHistory.at(i)).getArgs())); }
	}
	fs=FileSystem(rhs.fs);
	return *this;

}

Environment& Environment::operator=(Environment&& rhs){
	if(verbose == 1 || verbose==3){
		cout << "Environment& Environment::operator=(Environment&& rhs)" << endl;
	}
	for(unsigned int i=0; i<rhs.commandsHistory.size(); i++){
		commandsHistory.push_back(rhs.commandsHistory[i]);
		rhs.commandsHistory[i]= nullptr;
	}
	fs=FileSystem( (FileSystem&&) rhs.fs);
	rhs.getFileSystem().setRootDirectory(nullptr);
	rhs.getFileSystem().setWorkingDirectory(nullptr);
	return *this;

}

void Environment::clean(){
	for(unsigned int i=0; i<commandsHistory.size(); i++){
		delete commandsHistory.at(i);
	}
	commandsHistory.clear();
}
Environment::~Environment(){
	if(verbose == 1 || verbose==3){
		cout << "Environment::~Environment()" << endl;
	}
	clean();
}
