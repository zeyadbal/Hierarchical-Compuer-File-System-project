#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Files.h"
#include "Commands.h"

#include <string>
#include <vector>

using namespace std;

class Environment {
private:
	vector<BaseCommand*> commandsHistory;
	FileSystem fs;
	void clean();

public:
	Environment(); // constructor
	Environment(const Environment& rhs);
	Environment(Environment&& rhs);
	Environment& operator=(const Environment& rhs);
	Environment& operator=(Environment&& rhs);
	virtual ~Environment();
	void start();
	FileSystem& getFileSystem(); // Get a reference to the file system
	void addToHistory(BaseCommand *command); // Add a new command to the history
	const vector<BaseCommand*>& getHistory() const; // Return a reference to the history of commands
};

#endif
