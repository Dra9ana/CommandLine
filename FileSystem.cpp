#include "FileSystem.h"

FileSystem::FileSystem():tree_(new Tree(""))
{
	my_directory_ = tree_->getRoot();
}

//Kopirajuci konstruktor
FileSystem::FileSystem(const FileSystem& file_system)
{
	tree_ = new Tree(*file_system.tree_);
	my_directory_ = tree_->getRoot();
	log_filepath_ = file_system.log_filepath_;
}

//Premestajuci konstruktor
FileSystem::FileSystem(FileSystem&& file_system)
{
	tree_ = file_system.tree_;
	my_directory_ = tree_->getRoot();
	log_filepath_ = file_system.log_filepath_;
	file_system.tree_ = nullptr;
	file_system.my_directory_ = nullptr;
}

//destruktor
FileSystem::~FileSystem()
{
	delete tree_;
}

//Ucitavanje
void FileSystem::loadHierarchy(const string& fs_filepath, const string& log_filepath)
{
	    //Brisanje sadrzaja fajla pre novog unosa jer se sa out brise prethodni sadrzaj
	    ofstream output_file(log_filepath, ios::out);
		if (!output_file.is_open())throw("File couldn't open");
	    output_file.close();
		//Postavljanje log fajla na novi
		log_filepath_ = log_filepath;
		
		//Ako u stablu postoji node koji nije koreni <=> koreni node je list
		if (!tree_->getRoot()->isLeaf()) { 
			tree_->getRoot()->deleteChildren(); 
		}

		fstream input_file(fs_filepath, ios::in);
		if (!input_file.is_open())throw("File couldn't open");
		while (input_file.peek() != EOF) {
			string line,saved_line;
			getline(input_file, line);
			saved_line = line;
			try {
				tree_->addTreeNode(line);
			}
			catch (NameError& e) {
				cout << e.what() <<" in line: "<< saved_line<< endl;
			}
			catch (ExtensionError& e) {
				cout << e.what() << " in line: " << saved_line << endl;
			}
			catch (SearchError& e) {
				cout << e.what() << " in line: " << saved_line << endl;
			}
			catch (InsertError& e) {
				cout << e.what() << " in line: " << saved_line << endl;
			}
			catch (CommandError& e) {
				cout << e.what() << " in line: " << saved_line << endl;
			}
			catch (WrongCommand& e) {
				cout << e.what() << " in line: " << saved_line << endl;
			}
			catch (CommandNotFound& e) {
				cout << e.what() << " in line: " << saved_line << endl;
			}
		}
		input_file.close();


	}
	
void FileSystem::execute(const string& filepath)
{
	//Postavljanje statickih promenljivih na karakteristike fajl sistema koji zove komande
	//Da bi se izbegla greska u slucaju da vise fajl sistema naizmenicno poziva komande u svojim direktorijumima
	Command::setDirectory(my_directory_);
	Command::setLogFilePath(log_filepath_);

	string empty_text;
	fstream input_file(filepath, ios::in);
	if (!input_file.is_open())throw("File couldn't open");
	while (input_file.peek() != EOF) {
		string line;
		//citanje linije komande
		getline(input_file, line);
		Command* command = nullptr;
		string saved_line = line;
		try {
			//pravljenje i izvrsavanje komande
			command = Command::chooseCommand(line,empty_text="");
			command->Do();
			//U slucaju poziva CD promena direktorijuma
			if (command->getName() == "CD")my_directory_ = Command::getDirectory();
			delete command;

		}
		catch (NameError& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}
		catch (ExtensionError& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}
		catch (SearchError& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}
		catch (InsertError& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}
		catch (WrongCommand& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}
		catch (CommandError& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}
		catch (CommandNotFound& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}
		catch (DeleteError& e) {
			cout << e.what() << endl;
			Command::writeErrorInLogFile(saved_line);
			delete command;
		}


	}
}

void FileSystem::output()
{
	tree_->output();
}





