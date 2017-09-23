#ifndef __DB_EXCEPTIONS_HPP
#define __DB_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace database
{

class NotDatabaseConnectionException : public std::exception
{
};


class SqlStatementException : public std::exception
{
private:
    std::string _message;
public:
    SqlStatementException(const std::string & message);
    virtual ~SqlStatementException() = default;

    virtual const char * what() const throw();
};


class SqlFetchRowErrorException : public std::exception
{
private:
    std::string _message;
public:
    SqlFetchRowErrorException(const std::string & message);
    virtual ~SqlFetchRowErrorException() = default;

    virtual const char * what() const throw();
};

} // namespace database

#endif
