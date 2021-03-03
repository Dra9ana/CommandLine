
#include"Exceptions.h"
NameError::NameError(const char* message):exception(message)
{

}
ExtensionError::ExtensionError(const char* message) : exception(message)
{

}

InsertError::InsertError(const char* message):exception(message)
{
}

SearchError::SearchError(const char* message):exception(message)
{
}

DeleteError::DeleteError(const char* message):exception(message)
{
}

CommandError::CommandError(const char* message):exception(message)
{

}

CommandNotFound::CommandNotFound(const char* message):exception(message)
{
}

WrongCommand::WrongCommand(const char* message):exception(message)
{
}

BackSlashMissing::BackSlashMissing(const char* message):NameError(message)
{

}
