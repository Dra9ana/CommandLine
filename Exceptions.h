#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<exception>
#include<fstream>
#include<string>

using namespace std;

class NameError : public exception {
public:
	NameError( const char* message);
};

class BackSlashMissing :public NameError {
public:
	BackSlashMissing(const char* message);
};
class ExtensionError :public exception {
public:
	ExtensionError(const char* message);
};

class InsertError :public exception {
public: InsertError(const char* message);
};

class SearchError :public exception {
public:SearchError(const char* message);
};

class DeleteError : public exception {
public: DeleteError(const char* message);
};

class CommandError :public exception {
public:CommandError(const char* message);
};
class CommandNotFound : public exception {
public: CommandNotFound(const char* message);
};
class WrongCommand : public exception {
public: WrongCommand(const char* message);
};

#endif