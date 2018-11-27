# All Targets
all: bin/fs

# Tool invocations
# Executable "fs" depends on the files .o (Object files)
bin/fs: bin/Main.o bin/BaseFile.o bin/File.o bin/Directory.o bin/FileSystem.o bin/Environment.o bin/BaseCommand.o bin/PwdCommand.o bin/CdCommand.o bin/LsCommand.o bin/MkdirCommand.o bin/MkfileCommand.o bin/CpCommand.o bin/MvCommand.o bin/RenameCommand.o bin/RmCommand.o bin/HistoryCommand.o bin/VerboseCommand.o bin/ExecCommand.o bin/ErrorCommand.o

	@echo 'Buildinmg target: fs'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/fs bin/Main.o bin/BaseFile.o bin/File.o bin/Directory.o bin/Environment.o bin/FileSystem.o bin/BaseCommand.o bin/PwdCommand.o  bin/CdCommand.o bin/LsCommand.o bin/MkdirCommand.o bin/MkfileCommand.o bin/CpCommand.o bin/MvCommand.o bin/RenameCommand.o bin/RmCommand.o bin/HistoryCommand.o bin/VerboseCommand.o bin/ExecCommand.o bin/ErrorCommand.o
	@echo 'Finished building target: fs'
	@echo ' '

# Depends on the source and header files
bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp
bin/BaseFile.o:src/BaseFile.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseFile.o src/BaseFile.cpp
bin/File.o: src/File.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/File.o src/File.cpp
bin/Directory.o: src/Directory.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Directory.o src/Directory.cpp
bin/FileSystem.o: src/FileSystem.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp
bin/Environment.o: src/Environment.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Environment.o src/Environment.cpp
bin/BaseCommand.o: src/BaseCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseCommand.o src/BaseCommand.cpp
bin/PwdCommand.o: src/PwdCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/PwdCommand.o src/PwdCommand.cpp
bin/CdCommand.o: src/CdCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CdCommand.o src/CdCommand.cpp
bin/LsCommand.o: src/LsCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/LsCommand.o src/LsCommand.cpp
bin/MkdirCommand.o: src/MkdirCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MkdirCommand.o src/MkdirCommand.cpp
bin/MkfileCommand.o: src/MkfileCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MkfileCommand.o src/MkfileCommand.cpp
bin/CpCommand.o: src/CpCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CpCommand.o src/CpCommand.cpp
bin/MvCommand.o: src/MvCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MvCommand.o src/MvCommand.cpp
bin/RenameCommand.o: src/RenameCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RenameCommand.o src/RenameCommand.cpp
bin/RmCommand.o: src/RmCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RmCommand.o src/RmCommand.cpp
bin/HistoryCommand.o: src/HistoryCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/HistoryCommand.o src/HistoryCommand.cpp
bin/VerboseCommand.o: src/VerboseCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/VerboseCommand.o src/VerboseCommand.cpp
bin/ExecCommand.o: src/ExecCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ExecCommand.o src/ExecCommand.cpp
bin/ErrorCommand.o: src/ErrorCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ErrorCommand.o src/ErrorCommand.cpp



#Clean the build directory
clean: 
	rm -f bin/*.o bin/fs
