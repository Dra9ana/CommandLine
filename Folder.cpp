#include"Exceptions.h"
#include"ExeFile.h"
#include"Folder.h"
#include"TreeNode.h"

//Poziva konstruktor nasledjene klase i cita ime iz teksta
Folder::Folder(string text, Folder* parent) :TreeNode(text,parent)
{
   if (!text.empty())throw(NameError("Folder has no content"));
}

//Destruktor mora da obrise decu iz vektora pre brisanja samog vektora
//Dovoljno je obrisati samo decu jer je svako dete zaduzeno za brisanje svoje dece tako da ce svi biti obrisani
Folder::~Folder()
{
	deleteChildren();

}

//matode potrebne za kopirajuci i premestajuci konstruktor stabla 
vector<TreeNode*> Folder::getChildren()
{
	return children_;
}

//kopira u decu jedno po jedno dete iz prosledjenog vektora
void Folder::copyChildren(vector<TreeNode*> children)
{
	for (int i = 0; i < children.size(); i++) {

		if (children[i]->isFolder(children[i]->getNameWithExtension()))
		{
			children_.push_back(new Folder(children[i]->getName(),this));//dodavanje ovog deteta, name sluzi da bi moglo po referenci da se posalje
			children_[i]->copyChildren(children[i]->getChildren());//kopiranje dece deteta ako ih ima
		}
		else
		{
			children_.push_back(File::chooseFile(children[i]->getName(),this,children[i]->getContent(),children[i]->getExtension()));//kapiranje ovog fajla
		}

	}
}
void Folder::deleteChildren()
{
	for (int i = 0; i < children_.size(); i++) {
		delete children_[i];
	}
	children_.clear();
}
//Geteri
TreeNode* Folder::getChild(int i)const
{
	return children_[i];
}

string Folder::getNameWithExtension() const
{
	return name_;
}

string Folder::getExtension() const
{
	throw("Folder has no extension");
}

string Folder::getContent()const
{
	throw("Folder has no content");
}

//Pronalazi fajl ili folder u ovom direktorijumu
//Vraca pokazivac na njega
TreeNode* Folder::findTreeNode(const string& name)
{
	//ako se imena poklapaju to je ovaj folder
	if (name_ == name)return this;

	//Ako ne, trazi ga u deci
	for (int i = 0; i < children_.size(); i++) {
		//Procitaj sta je naslo dete
		TreeNode* c = children_[i]->findTreeNode(name);
		//Ako je nasao pretraga je zavrsena
		if (c)return c;
	}
	//Ako nigde nije nadjen vrati nullptr
	return nullptr;
}

//Trazi da li postoji dete sa datim imenom kao dete foldera, ako da vraca njegov indeks, ako ne vraca -1
int Folder::findChild(const string& name_with_extension)const
{
	for (int i = 0; i < children_.size(); i++) {
		if (children_[i]->getNameWithExtension() == name_with_extension)return i;
	}
	return -1;
}

//Dodaje fajl ili folder u ovaj folder cije se informacije nalaze u textu
void Folder::addTreeNode(string text)
{
	TreeNode* node;

	//Alokacija memorije za nov fajl/folder
	if (isFolder(text))  node = new Folder(text, this);
	else                 node = File::chooseFile(text, this);

	//Ako nema dece postavi prvo dete
	if (children_.empty())children_.push_back(node);
	else {//Ako ima
		int i;
		//idi dokle god trenutno dete ima alfabetski prioritet
		for (i = 0; i < children_.size() && children_[i]->compareName(node->getName()); i++) {}
        //Ubaci ga na mesto sa odgovarajucim prioritetom
		children_.insert(children_.begin() + i, node);
	}
}

//Ispisuje ime foldera u izlazni fajl
void Folder::output(const string& path, fstream& output_file)const
{
	output_file << path + "\\" + name_;
}

//ispisuje folder i svu njegovu decu na standardni izlaz
void Folder::output(string path)const
{
	int i = 0;

	if (parent_ != nullptr) { path = path + "\\" + name_; cout << path; }

	while (i < children_.size()) {
		if (parent_ != nullptr || i != 0)cout << endl;
		children_[i]->output(path);
		i++;
	}
}

//ispisuje svu decu foldera u izlazni fajl
void Folder::outputChildren(bool root_call, string path, fstream& output_file)const
{
	int i = 0;
	//Ako ga nije pozvao trenutni direktorijum=trenutni koren dodaje u putanju kosu crtu i ime
	if(!root_call)path = path + "\\" + name_;

	while (i < children_.size()) {//prolazak kroz svu decu

		//Ispisuje se novi red osim ako je u pitanju prva linija
		if (!Ls::first_line_ || i != 0) {
			output_file << endl;
			Ls::first_line_ = false;//Ako smo prosli prvu liniju first_line_ postaje false
		}

		//Ispisuje ime i-tog deteta
		children_[i]->output(path, output_file);
		//Poziva decu i-tog deteta
		children_[i]->outputChildren(false, path, output_file);

		i++;
	}
}

//Brise svoje dete na poziciji i
void Folder::eraseChild(int i)
{
	//Ako neko pozove brisanje deteta s indeksom vecim od duzine to je greska
	if (i >= children_.size())throw DeleteError("Index is greater from number of children");
	else {
		delete children_[i];
		children_.erase(children_.begin() + i);
	}
}

//Folder je list u stablu ako nema decu
bool Folder::isLeaf()const
{
	return children_.empty();
}

void Folder::execute()
{
	throw("Cannot execute folder");
}