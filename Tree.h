#ifndef TREE_H
#define TREE_H

#include"Folder.h"
#include"TreeNode.h"

#include<fstream>
#include<iostream>
#include<iomanip>

class Tree {
public:
	Tree();
	Tree(const Tree& tree);
	Tree(Tree&& tree);
	Tree(string root_name);
	~Tree();

	TreeNode* getRoot()const;

	void addTreeNode(string path);

	void deleteTree();
	void output();

private:
	Folder* root_;

	string pathRoot(string& path)const;
};
#endif

