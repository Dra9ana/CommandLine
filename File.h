#ifndef FILE_H
#define FILE_H

#include"Command.h"
#include"Folder.h"
#include"TreeNode.h"

class File : public TreeNode {
	public:

		File(string& text, TreeNode* parent);
		File(string name, TreeNode* parent, const string& content, const string& extension);
		File(const File& file)=delete;
		File(File&& file)=delete;
		virtual ~File();

		vector<TreeNode*> getChildren()override;
		void copyChildren(vector<TreeNode*>children)override;
		void deleteChildren()override;
		
		string getNameWithExtension()const;
	    string getExtension()const;
		string getContent()const;

		TreeNode* findTreeNode(const string& name_with_extension) override;
		int findChild(const string& name_with_extension)const override;
		TreeNode* getChild(int i)const override;
		void addTreeNode(string text) override;

		void output(const string& path, fstream& output_file) const override;
		virtual void output(string path)const override;
		void outputChildren(bool root_call, string path, fstream& output_file)const override;

		void eraseChild(int i)override;

		bool isLeaf() const override;

		static File* chooseFile(string& text, TreeNode* parent);
		static File* chooseFile(const string& name, TreeNode* parent, const string& content, const string& extension);

		virtual void execute();
	protected:
		string extension_;
		string content_;
		
		static string readExtension(string& text);
	};



class TxtFile :public File {
   public: TxtFile(string& text, TreeNode* parent);
		 TxtFile(const string& name,TreeNode* parent,const string& content);
		 TxtFile(const TxtFile& file)=delete;
		 TxtFile(TxtFile&& file)=delete;
	};

#endif
