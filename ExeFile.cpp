#include"ExeFile.h"
#include"File.h"


ExeFile::ExeFile(string text, TreeNode* parent) :File(text, parent)
{
	extension_ = "exe";
	readCommands(text);
	readContent();
}

ExeFile::ExeFile(const string& name, TreeNode* parent, string content):File( name, parent,"", "exe")
{
	readCommands(content);
	readContent();
}


ExeFile::~ExeFile()
{
	for (int i = 0; i < commands_.size(); i++) {
		delete commands_[i];
	}
}

//Egzekjutuje exe fajl
void ExeFile::execute()
{
	bool first = true;

		for (int i = 0; i < commands_.size(); i++) {
			try {
				commands_[i]->Do();
			}
			catch (NameError& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE "+getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());
				

			}
			catch (ExtensionError& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE " + getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());

			}
			catch (SearchError& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE " + getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());

			}
			catch (InsertError& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE " + getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());

			}
			catch (WrongCommand& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE " + getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());

			}
			catch (CommandError& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE " + getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());

			}
			catch (CommandNotFound& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE " + getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());

			}
			catch (DeleteError& e) {
				if (first) { first = false; Command::writeErrorInLogFile("EXE " + getNameWithExtension()); }
				cout << e.what() << endl;
				Command::writeErrorInLogFile(commands_[i]->commandToString());

			}

		}
	
	
}

//Ispis exe fajla na standardni izlaz
void ExeFile::readContent()
{
	for (int i = 0; i < commands_.size(); i++) {
		content_+=commands_[i]->commandToString();
		if (i != commands_.size() - 1)content_+= "\\n";
	}
}

void ExeFile::readCommands(string& text)
{
	string line,saved_line;
	while (!text.empty()) {
		try {
			saved_line=line = Command::readCodeLine(text);//Cita liniju koda sa ulaza
			commands_.push_back(Command::chooseCommand(line, text));//Bira konstruktor komande i ubacuje je u vektor komandi
		}//Prijavljivanje greske
		catch (CommandError& e) {
			cout << e.what() << endl;
			cout << saved_line << endl;
		}
		catch (WrongCommand& e) {
			cout << e.what() << endl;
			cout << saved_line << endl;

		}
		catch (CommandNotFound& e) {
			cout << e.what() << endl;
			cout << saved_line << endl;
		}
	}
}

void ExeFile::copyCommands(vector<Command*>commands)
{
	for (int i = 0; i < commands.size(); i++) {
		commands_.push_back(Command::chooseCommand(commands[i]));
	}
}

