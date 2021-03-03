#include "Command.h"

#include<ostream>

 string Command::log_filepath_;
 TreeNode* Command::directory_;
 //Skup validnih komandi
 set<string> Command::valid_commands_{ "NEW","DEL","CD","LS","EXE" };

Command::Command(const string& name) :name_(name){

}

Command::Command(const string& name, string& line):name_(name)
{
	//Citanje jednog argumenta iz linije i proveravanje validnosti
	readArgument(true,line);
	if (!line.empty())throw(CommandError("Too many arguments"));
}

Command::~Command()
{
}

string Command::commandToString()
{
	if (name_ != "LS") {
		return name_ + " " + arguments_;
	}
	else
		return name_;
}

//Ispis na standardni izlaz
void Command::output()
{
	cout << commandToString();
}

//Ispis greske u log fajl
void Command::writeErrorInLogFile(const string& line)
{
   bool first_line;
   fstream output_file;

   //Citanje prve linije fajla
   output_file.open(log_filepath_, ios::in);
   if (!output_file.is_open())throw("File couldn't open");
   first_line = (output_file.peek() == EOF);
   output_file.close();

   output_file.open(log_filepath_, ios::app);
   if (!output_file.is_open())throw("File couldn't open");
   //Ako je fajl prazan ne ispisuje se novi red na pocetku
	if (!first_line) { output_file << endl;  }
	output_file << "Error: " << line;
	output_file.close();
}

string Command::getName() const
{
	return name_;
}

string Command::getArguments() const
{
	return arguments_;
}

TreeNode* Command::getDirectory()
{
	return directory_;
}

void Command::setDirectory(TreeNode* directory)
{
	Command::directory_ = directory;
}

void Command::setLogFilePath(const string& log_filepath)
{
	Command::log_filepath_ = log_filepath;
}

string Command::readCodeLine(string& text)
{
	int i = 0;
	string line = "";
	//Cita liniju teksta formatiranog sa laznim novim redovima
	while (i < text.length() && (text[i] != '\\' ||(i<(text.length()-1) && text[i + 1] != 'n'))) { line.push_back(text[i++]); }
	//Ako je dosao do novog reda brise znakove za novi red
	if (i < text.length())text.erase(0, i + 2);
	else text.clear();//U suprotnom brise tekst do kraja
	return line;
}

string Command::readCommand(string& line)
{
	string command = "";
	int i = 0;
	//Komanda se cita do razmaka ili kraja linije
	while (i < line.length() && line[i] != ' ') {
		command.push_back(line[i]);
		i++;
	}
	//Ako je procitano nesto sto nije komanda onda je procitan tekst
	if ((valid_commands_.find(command) == (valid_commands_.end()))) { command = ""; }
	//Ako je procitana komanda ali je ili LS sa razmakom ili neka druga komanda na kraju linije komanda nije validna
	if (i<line.length()&&(line[i] == ' ' && command == "LS")) { deleteLine(line);throw WrongCommand("Wrong command line"); }
	
	//Ako je komanda procitana i validna
	if (command != "") {
		if (i >= (line.length() - 1))line.clear();//Ako je dosla do kraja brise se linija
		else  line.erase(0, i + 1);//Ako nije brise se procitano
	}
	return command;
}

//Citanje jednog argumenta
void Command::readArgument(bool last_argument,string& text)
{
	int i=0;
	//Dok nije dosao do kraja linije ili razmaka(text je samo u slucaju NEW kada svakako mora postojati razmak na kraju ekstenzije)
	while (i < text.length() && text[i] != ' ') {
		arguments_.push_back(text[i]);
		i++;
	}
	if (i < (text.length())) {//Ako je dosao do razmaka cita se razmak i brise sve do njega 
		arguments_.push_back(' ');
		text.erase(0, i + 1);
	}
	else {//Ako je dosao do kraja a nije poslednji argument ima premalo argumenata
		if (!last_argument)throw(WrongCommand("Invalid syntax"));
		text.clear();
	}
	//Ako je trazeno citanje argumenta a on nije procitan komanda ima premalo argumenata
	if (i == 0)throw(WrongCommand("Not enough arguments"));
	

}

void Command::deleteLine(string& text)
{
	int i = 0;
	while (i < text.length() && (text[i] != '\\' || (i < (text.length() - 1) && text[i + 1] != 'n'))) {i++;}//Pomera brojac do kraja reda
	if (i < text.length())text.erase(0,i + 2);//brise red
	else text.clear();
}

New::New(string& line,string& text):Command("NEW")
{
	string command;
	
	if (line.find(".") != -1) {//Ako je u pitanju fajl
		readArgument(false,line);//Cita ime fajla
		arguments_ += line+'\\'+'n';//Dodaje prvu liniju u argumente ako je procitano ime validno
		string prev_text;//Cuvanje azuriranog teksta
		try {
			 prev_text = text;//Pre azuriranja cuvanje teksta
			 line = readCodeLine(text);//citanje linije
			 while ((command = readCommand(line)) == "" && (!text.empty()||prev_text=="\\n")){//Ako je procitan tekst a ne komanda 
			    //i tekst nije prazan ili je poslednji procitnan novi red
				arguments_ += line + '\\' + 'n';//Dodavanje reda u argumente
				prev_text = text;//Azuriranje teksta
				line = readCodeLine(text);//Citanje sledece linije 
			} 
			 if(command == "" && text.empty())arguments_ += line + '\\' + 'n';//Ako je izasao iz petlje jer je dosao do kraja teksta
			                                                                 //cita poslednju neprocitanu liniju
		}
		catch (WrongCommand& e) {//Ako je doslo do citanja komande koja je pogresna treba prekinuti while i uhvatiti izuzetak
			cout << e.what() << endl;	
		}

		if (command != "") {//Ako je procitana komanda vratiti je u tekst za dalje citanje
			if (command != "LS")
				text = command + " " + line+"\\n"+text;
			else
				text = command + "\\n" + text;
		}
		//Brisanje poslednjeg novog reda jer se on ne vidi u ispisu
		arguments_.pop_back();
		arguments_.pop_back();
	     
	}
	else {//Ako je u pitanju folder 
		readArgument(true, line);//Citanje imena
		if (!line.empty())throw(WrongCommand("Too many arguments"));//Ako je procitano jos nesto sem imena ima previse argumenata
	}
	
}

New::New( string& arguments):Command("NEW",arguments)
{
}

void New::Do()
{
	string name = arguments_;//kopiranje argumenata
	if (name.find(".")!=-1) { //proverava da li je fajl
		int i = name.find(" ");//nalazi kraj imena
		if(i!=-1)name.erase(name.begin()+i, name.end());//brise ostalo
	}//citanje imena iz argumenata
	if (directory_->findChild(name) != -1)throw(InsertError("File or Folder already exists"));//Provera da li postoji vec folder/fajl sa ovim imenom
    directory_->addTreeNode(arguments_);//Dodavanje fajla/foldera ako ne postoji
}


Del::Del( string&text):Command("DEL",text)
{
	
}

void Del::Do()
{
  int id= directory_->findChild(arguments_);//Provera da li dete postoji
  if (id == -1)throw(SearchError("Node not found"));
  else directory_->eraseChild(id);//Ako postoji brisanje deteta
	
}

Cd::Cd( string& text):Command("CD",text)
{
	if (arguments_!=".." && arguments_.find(".") != -1)throw(WrongCommand("File is not directory"));//Provera da li je pozvano citanje fajla kao argumenta
}

void Cd::Do()
{
	
  int id = -1;
  if (arguments_ == "..") {
	  if (directory_->getParent() == nullptr)throw(SearchError("Directory cannot be nullptr"));//Provera d ali postoji roditelj
	  else directory_ = directory_->getParent();
	}
  else {
	   id=directory_->findChild(arguments_);//pronalazenje detata
	   if (id == -1)throw(SearchError("Directory not found"));//Ako ne postoji greska
	   else directory_ = directory_->getChild(id);
	}

}

bool Ls::first_line_;//Staticka promenljiva koja proverava da li se upisuje u prazan fajl
Ls::Ls():Command("LS")
{
}

void Ls::Do()
{
	fstream output_file;
	string file_line;
	//Provera da li je fajl prazan
	output_file.open(log_filepath_, ios::in);
	if (!output_file.is_open())throw("File couldn't open");
	Ls::first_line_ = (output_file.peek() == EOF);
	output_file.close();
	//Ispis
	output_file.open(log_filepath_,  ios::app);
	if (!output_file.is_open())throw("File couldn't open");
	directory_->outputChildren(true,"", output_file);
	//directory_->output("");
	output_file.close();
}


Exe::Exe( string& text):Command("EXE",text)
{
	//Provera validnosti argumenata
	int i = arguments_.find(".");
	if (i  == -1)throw(WrongCommand("Cannot execute folder"));
	if (i>(arguments_.length()-4)||arguments_[i + 1] != 'e' || arguments_[i + 2] != 'x' || arguments_[i + 3] != 'e')throw(WrongCommand("Cannot execute file that is not exe"));
}


void Exe::Do()
{
	TreeNode* node = directory_->getChild(directory_->findChild(arguments_));
	node->execute();
}


Command* Command::chooseCommand( string& line,string& text)
{
	string new_line;
	string name = readCommand(line);//Citanje komande
	if (name == "NEW") {
		if (text != "")return new New(line, text);//Ako je u pitanju komanda iz pravog fajla
		else return new New(new_line=readCodeLine(line), line);//Ako je u pitanju komanda iz exe fajla sve se nalazi u jednoj liniji
	}
	if (name == "DEL")return new Del(line);
	if (name == "LS")return new Ls();
	if (name == "CD")return new Cd(line);
	if (name == "EXE")return new Exe(line);

	throw CommandNotFound("Command not found");
}

Command* Command::chooseCommand(Command* command)
{
	string arguments = command->getArguments();
	if (command->getName() == "NEW") return new New(arguments);
	if (command->getName() == "DEL")return new Del(arguments);
	if (command->getName() == "LS")return new Ls();
	if (command->getName() == "CD")return new Cd(arguments);
	if (command->getName() == "EXE")return new Exe(arguments);

	throw CommandNotFound("Command not found");
}


