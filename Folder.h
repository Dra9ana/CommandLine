#ifndef FOLDER_H
#define FOLDER_H

#include"TreeNode.h"

#include<string>

class Folder :public TreeNode {

public:
	Folder(string text, Folder* parent);
	Folder(const Folder& folder)=delete;
	Folder(Folder&& folder)=delete;
	~Folder();
	
	vector<TreeNode*> getChildren()override;
	void copyChildren(vector<TreeNode*>children)override;
	void deleteChildren()override;

	TreeNode* getChild(int i)const override;
	string getNameWithExtension()const;
	string getExtension()const;
	string getContent()const;

	TreeNode* findTreeNode(const string& name) override;
	int  findChild(const string& name_with_extension)const override;
	void addTreeNode(string text)override;

	void output(const string& path, fstream& output_file)const override;
	void output(string path)const  override;
	void outputChildren(bool root_call, string path, fstream& output_file)const override;
	
	void eraseChild(int i)override;

	bool isLeaf()const override;

	void execute()override;
private:
	vector<TreeNode*> children_;
};


#endif