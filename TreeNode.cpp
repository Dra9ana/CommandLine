#include"Exceptions.h"
#include"Folder.h"
#include"TreeNode.h"

// =======TREENODE========

//konstruktori
TreeNode::TreeNode(string& text, TreeNode* parent) : parent_(parent)
{
	readName(text);
}

//virtuelni destruktor
TreeNode::~TreeNode()
{
	parent_ = nullptr;
}

//getter metode
string TreeNode::getName()const
{
	return name_;
}

TreeNode* TreeNode::getParent()const
{
	return parent_;
}

//poredi neko procitano ime sa imenom ovog objekta da bi ga ubacio na dobro mesto u vektoru
bool TreeNode::compareName(const string& name)
{
	int i;

	//prolazi kroz imena dokle god su im karakteri na istim pozicijama jednaki
	for ( i = 0; i < name.length() && i < name_.length() && tolower(name[i]) == tolower(name_[i]) ; i++)
	{
	}

	if (i == name_.length())return true;//ako je name_ krace ili jednake duzine sa name, a sastoje se iz istih karaktera do pozicije len(name_) name_ je pre alfabetski
	if (i == name.length())return false;//ako je name krace od name_ a sastoje se iz istih karaktera do pozicije len(name) onda je name pre name_ alfabetski

	return tolower(name_[i]) < tolower(name[i]);//vraca  da li je name_ pre alfabetski tako sto poredi prve razlicite karaktere

}

//Proverava da li je TreeNode cije je ime dato unutar text-a fajl ili folder
//Tekst moze biti ime TreeNode-a, putanja ili putanja sa sadrzajem u slucaju fajla
 bool TreeNode::isFolder(const string& text)
{
	return  (text.find('.')==-1);
}

 void TreeNode::readName(string& text)
 {
	 int i = 0;
	 //Cita ime foldera/fajla
	 while (i < text.length() && text[i] != ' ') {
		 //ako trenutni karakter nije slovo cifra ili donja crta unos je nevalidan
		 if (!isalpha(text[i]) && !isdigit(text[i]) && !(text[i] == '_'))
		 {
			 throw(NameError("Invalid name of file or folder"));
		 }
		 else //ako je validan ubacuje ga u ime
			 name_.push_back(text[i++]);
	 }

	 if (i < text.length()) { text.erase(0, i + 1); }//ako nije dosao do kraja obrisi prvih i karaktera koji su zapravo procitano ime i razmak
	 else text.clear();//Ako je stigao do kraja samo resetuj string
 }



