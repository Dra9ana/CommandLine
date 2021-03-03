#ifndef EXE_FILE_H
#define EXE_FILE_H

#include"Command.h"
#include"File.h"
#include"Treenode.h"

#include<iostream>
#include<string>


using namespace std;

class ExeFile :public File {
public:
	ExeFile(string text, TreeNode* parent);
	ExeFile(const string& name, TreeNode* parent, string content);
	ExeFile(const ExeFile& file)=delete;
	ExeFile(ExeFile&& file)=delete;
	~ExeFile();

	void copyCommands(vector<Command*>commands);
	void execute();
	

private:
	vector<Command*> commands_;
	void readContent();
	void readCommands(string& text);
};
#endif
