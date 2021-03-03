#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include"Command.h"
#include"Exceptions.h"
#include"Tree.h"
#include"TreeNode.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include<map>
#include<string>
#include<vector>

using namespace std;

class FileSystem {
public:
	FileSystem();
	FileSystem(const FileSystem& file_system);
	FileSystem(FileSystem&& file_system);
	~FileSystem();
	void loadHierarchy(const string& fs_filepath, const string& log_filepath);
	void execute(const string& filepath);
	void output();

private:
	Tree* tree_;
	TreeNode* my_directory_;
	string log_filepath_;
};
#endif
