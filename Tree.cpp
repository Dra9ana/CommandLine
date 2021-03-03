#include"Exceptions.h"
#include"Folder.h"
#include "Tree.h"
#include"TreeNode.h"

Tree::Tree() :root_(nullptr)
{
}

Tree::Tree(const Tree& tree)
{
	root_ = new Folder("",nullptr);
	root_->copyChildren(tree.root_->getChildren());
}

Tree::Tree(Tree&& tree)
{
	root_ = tree.root_;
	tree.root_ = nullptr;
}

Tree::Tree(string root_name) : root_(new Folder(root_name, nullptr))
{
}

Tree::~Tree()
{
	deleteTree();
}

TreeNode* Tree::getRoot()const
{
	return root_;
}

//Nije const string jer se dalje prenosi kao rederenca u pathRoot
void Tree::addTreeNode(string path)
{
	string path_root = pathRoot(path);//citanje prvog imena
	TreeNode* node = root_;
	//Ako je stablo bez direktorijuma napravi prazan direktorijum i dodaj prvi fajl/folder
	if (root_ == nullptr) { root_ = new Folder("", nullptr); root_->addTreeNode(path_root); }
	else {
		while (!path.empty() && node != nullptr) {//Dok se ne procita poslednji deo putanje ili nije nadjen neki deo putanje
			node = node->findTreeNode(path_root);//Pronalazanje trenutnog dela putanje
			path_root = pathRoot(path);//Citanje sledeceg dela putanje
		}

		if (node == nullptr)throw(SearchError("Some part of path is not found"));//Ako je petlja prekinuta jer neki deo nije nadjen baci gresku
		else {
			node->addTreeNode(path_root);//Ako je petlja prekinuta jer je doslo do kraja citanja putanje dodaj ga
		}
	}
}

//Brisanje stabla
void Tree::deleteTree()
{
	delete root_;
	root_ = nullptr;
}

void Tree::output()
{
	root_->output("");
}

//Citanje jednog dela putanje
string Tree::pathRoot(string& path)const
{
	string ret = "";
	int i = 1;
	
	if (path.empty())throw(NameError("Empty path"));
	// Ako putanja ne pocitanje sa'\\' ime se cita od karaktera 0 i prijavljuje se greska
	if (path[0] != '\\'){
		  cout << "\\ missing" << endl;
		  i = 0;
	 }
		
	//Citanje putanje do sledeceg znala '\\' ili kraja putanje
	while (i < path.length() && (path[i] != '\\' || (i<(path.length()-1)&&(path[i + 1] == 'n'||path[i+1]=='t'))))ret.push_back(path[i++]);
	
	//brisanje procitanog
	if (!path.empty())path = path.erase(0, i);

	return ret;
}





