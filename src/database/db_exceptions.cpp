#include "db_exceptions.hpp"
#include <string>

using namespace std;

namespace database
{

SqlStatementException::SqlStatementException(const string & message)
: _message(message)
{

}

const char * SqlStatementException::what() const throw() 
{
    return this->_message.c_str();
}

SqlFetchRowErrorException::SqlFetchRowErrorException(const string & message)
: _message(message)
{

}

const char * SqlFetchRowErrorException::what() const throw() 
{
    return this->_message.c_str();
} 

} // namespace database
