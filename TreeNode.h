#ifndef TREE_NODE_H
#define TREE_NODE_H

#include<fstream>
#include<iostream>
#include<string>
#include<vector>


using namespace std;

class TreeNode {
public:
	TreeNode(string& text,TreeNode* parent);
	TreeNode(const TreeNode& node)=delete;
	TreeNode(TreeNode&& node)=delete;
	virtual ~TreeNode();

	virtual vector<TreeNode*> getChildren()=0;
	virtual void copyChildren(vector<TreeNode*>children) = 0;
	virtual void deleteChildren() = 0;

	string getName()const;
	virtual string getExtension()const=0;
	virtual string getNameWithExtension()const =0;
	TreeNode* getParent()const;
	virtual string getContent()const=0 ;
	virtual TreeNode* getChild(int i) const = 0 ;
	
	virtual TreeNode* findTreeNode(const string& name_with_extension)=0 ;
	virtual int findChild(const string& name_with_extension)const=0;
	virtual void addTreeNode( string text) = 0;

	virtual void output(const string& path, fstream& output_file)const = 0; 
	virtual void output( string path)const = 0;
	virtual void outputChildren(bool root_call, string path, fstream& output_file)const = 0;

	virtual void eraseChild(int i)=0;

	virtual bool isLeaf()const=0;
	static bool isFolder(const string& text);

	bool compareName(const string& name);

	virtual void execute() = 0;

protected:

	
    virtual void readName( string& text);
	
	string name_;
	TreeNode* parent_;
   
    
	
};


#endif