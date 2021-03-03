#include"File.h"
#include"ExeFile.h"
//konstruktori
File::File(string& text, TreeNode* parent) :TreeNode(text, parent)
{
}
  

File::File(string name, TreeNode* parent, const string& content, const string& extension):TreeNode(name,parent),content_(content),extension_(extension)
{
}

File::~File()
{
	extension_.clear();
	content_.clear();
}

//Prijavljuje gresku u slucaju da neko pozove ovu metodu nad fajlom jer je fajl list
vector<TreeNode*> File::getChildren()
{
	throw("File has no children");
}

//Prijavljuje gresku u slucaju da neko pozove ovu metodu nad fajlom jer je fajl list
void File::copyChildren(vector<TreeNode*>children)
{
	throw("File has no children");
}

void File::deleteChildren()
{
	throw("File has no children");
}

//getteri
string File::getNameWithExtension() const
{
	return name_ + "." + extension_;
}

string File::getExtension() const
{
	return extension_;
}

string File::getContent()const
{
	return content_;
}

//Proverava da li je ime u stringu name_with_extension ime ovog fajla sa ekstenzijom
//Ako nije znamo da smo na kraju stabla i da trazeni fajl/folder nije nadjen nigde u stablu
TreeNode* File::findTreeNode(const string& name_with_extension)
{
	if ((name_ + "." + extension_) == name_with_extension)return this;
	else return nullptr;
}

//U slucaju da neko pokusa da nadje dete fajla javljamo gresku jer je fajl list
int File::findChild(const string& name_with_extension)const
{
	throw(SearchError("File has no children"));
}

//Prijavljuje gresku u slucaju da neko pozove ovu metodu nad fajlom jer je fajl list
TreeNode* File::getChild(int i)const
{
	throw(SearchError("File have no children"));
}

//Prijavljuje gresku u slucaju pokusaja dodavanja deteta u fajl
void File::addTreeNode(string text)
{
	throw InsertError("Cannot add document into file");
}

//Ispisuje ime fajla sa ekstenzijom u izlazni fajl
void File::output(const string& path, fstream& output_file)const
{
	output_file << path + "\\" + name_ + "." + extension_;
}

//Ispisuje ime  fajla sa ekstenzijom i sadrzajem na standardni izlaz
void File::output(string path)const
{
	cout << path + "\\" + name_ + "." + extension_+" "+content_;
}

//nema decu tako da samo prekida rekurziju u funkcijama za ispis
void File::outputChildren(bool root_call, string path, fstream& output_file)const
{
}

//Javlja gresku ako neko pokusa da obrise decu fajla jer je fajl list
void File::eraseChild(int i)
{
	throw SearchError("File has no children");
}

//Fajl jeste list u stablu
bool File::isLeaf()const
{
	return true;
}

//Cita ekstenziju koja se nalazi u tekstu
string File::readExtension(string& text)
{
	string extension = "";
	int start = text.find("."),i=start+1;//nalazi tacku

	//Ako ne postoji tacka onda nema ni ekstenzije
	if (text.empty()||start==-1)throw ExtensionError("Extension not found");

	//Ekstenzija je sve izmedju tacke i razmaka
	while (i < text.length() && text[i] != ' ') {
		//Proverava ispravnost imena ekstenzije
		if (!isalpha(text[i]) && !isdigit(text[i]) && !(text[i] == '_'))
			throw(ExtensionError("Invalid name of extension"));
		else //ako je validan ubacuje ga u ime
			extension.push_back(text[i++]);
	}

	//Brise iz teksta procitanu ekstenziju
	text = text.erase(start, i-start);

	return extension;
}

//Bira koji konstruktor treba pozvati
File* File::chooseFile(string& text, TreeNode* parent)
{
	string extension = readExtension(text);

	if (extension=="exe")return new ExeFile(text, parent);
	if (extension=="txt")return new TxtFile(text, parent);

	throw(ExtensionError("Extension not found"));
}

File* File::chooseFile(const string& name, TreeNode* parent, const string& content,const string& extension)
{
	if (extension == "exe")return new ExeFile(name,  parent, content);
	if (extension == "txt")return new TxtFile(name, parent, content);

	throw(ExtensionError("Extension not found"));
}

//Odbija executovanje bilo kog fajla koji nije exe
void File::execute()
{
	throw("Cannot execute ordinary file");
}

TxtFile::TxtFile(string& text, TreeNode* parent) :File(text, parent)
{
	content_ = text;
	extension_ = "txt";
}

TxtFile::TxtFile(const string& name, TreeNode* parent, const string& content):File(name,parent,content,"txt")
{

}


