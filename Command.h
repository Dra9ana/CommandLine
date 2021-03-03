#ifndef COMMAND_H
#define COMMAND_H

#include"Exceptions.h"
#include "Tree.h"

#include<exception>
#include<iostream>
#include<set>
#include<string>

using namespace std;
class Command {
public:
	Command( const string& name);
	Command(const string& name, string& text);
	virtual ~Command();

	virtual void  Do()=0;

	string commandToString();
	void output();
	static void writeErrorInLogFile(const string& line );

	string getName()const;
	string getArguments()const;
	static TreeNode* getDirectory();

	static void setDirectory(TreeNode* directory);
	static void setLogFilePath(const string& log_filepath);

	static Command* chooseCommand( string& line,string& text);
	static Command* chooseCommand(Command* command);

	static string readCodeLine(string& text);
	static string readCommand(string& line);
    static void deleteLine(string&text);
protected:
	string name_;
	string arguments_;
	static TreeNode* directory_;
	static string log_filepath_;
	static set<string>valid_commands_;

	void readArgument(bool last_argument,string& text);
	
	
	
	
};
class New :public Command {
public:
	  New( string& line,string& arguments);
	  New( string& arguments);
	  void Do() override;

};
class Del :public Command {
public:
	Del( string& arguments);
	void Do() override;

};
class Cd :public Command {
public:
	Cd( string& name);
	void Do()override;
};
class Ls :public Command {
public:
	Ls();
	void Do()override;
	static bool first_line_;
	
};
class Exe :public Command {
public:
	Exe(string& name);
	void Do()override;
};
#endif
