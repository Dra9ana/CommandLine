#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>


#include "FileSystem.h"

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int tests_public_passed = 0;

// Funkcija koja poredi Vas izlaz sa ocekivanim izlazom za odgovarajuci test primer
// Da biste lakse uocili gresku ukoliko Vas izlaz ne odgovara ocekivanom izlazu, uporediti fajlove na linku https://text-compare.com/
void checkOutput(const string& log_filename, int test_number) {

	ifstream correct_output("correct_log_" + to_string(test_number) + ".txt");
	stringstream ss_correct;
	ss_correct << correct_output.rdbuf(); correct_output.close();
	string correct_file_system = ss_correct.str();

	ifstream student_output(log_filename);
	stringstream ss_student;
	ss_student << student_output.rdbuf(); student_output.close();
	string student_file_system = ss_student.str();

	if (student_file_system != "" && student_file_system == correct_file_system) {
		cout << "Test " + to_string(test_number) + ": PASSED" << endl;
		tests_public_passed++;
	}
	else {
		cout << "Test " + to_string(test_number) + ": FAILED" << endl;
	}

}

void test(int test_number) {

	FileSystem* file_system = new FileSystem;

	//file_system->loadHierarchy("hierarchy_public_" + to_string(test_number+1) + ".txt", "student_log_" + to_string(test_number+1) + ".txt");
	//file_system->output();
	file_system->loadHierarchy("hierarchy_public_" + to_string(test_number) + ".txt", "student_log_" + to_string(test_number) + ".txt");
	//file_system->output();

	//FileSystem* file_system_cpy = new FileSystem(*file_system);
	//file_system_cpy->output();
	//delete file_system;
	//file_system_cpy->execute("commands_" + to_string(test_number) + ".txt");
	file_system->execute("commands_" + to_string(test_number) + ".txt");
	

	checkOutput("student_log_" + to_string(test_number) + ".txt", test_number);

	//delete file_system_cpy;
	delete file_system;
}

int main() {

	// Izmeniti elemente niza u zavisnosti od testova koje zelite da pokrenete!
	// Svi testovi testiraju ucitavanje hijerarhije i izvrsavanje komandi
	// Test 1 - Testira izvrsavanje komande LS
	// Test 2 - Testira izvrsavanje komandi CD i LS
	// Test 3 - Testira izvrsavanje komandi NEW, CD i LS
	// Test 4 - Testira izvrsavanje komandi DEL i LS
	// Test 5 - Testira izvrsavanje komandi EXE i LS
	int active_tests[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int number_of_tests = sizeof(active_tests) / sizeof(int);
	//_crtBreakAlloc =1565 ;
	cout << "============================================" << endl;
	cout << "TESTING FILE_SYSTEM" << endl << endl;
	cout << "Executing tests: ";
	for (int i = 0; i < number_of_tests; i++) cout << active_tests[i] << (i < number_of_tests - 1 ? ", " : "");
	cout << endl;

	for (int i = 0; i < number_of_tests; i++) test(active_tests[i]);

	cout << "============================================" << endl;
	cout << "Public tests passed count: " << tests_public_passed << endl;

	//_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}