#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP "EXCEPTIONS_HPP"
#include <iostream>
#include <exception>
constexpr char BAD_REQUEST[] = "Bad Request\n";
constexpr char PERMISSION_DENIED[] = "Permission Denied\n";
constexpr char NOT_FOUND[] = "Not Found\n";
constexpr char EMPTY[] = "Empty\n";


class Bad_Request_Error : public std::exception {
public:
	const char* what() const noexcept { return BAD_REQUEST; }
};



class Permission_Denied_Error : public std::exception {
public:
	const char* what() const noexcept { return PERMISSION_DENIED; }
};

class Not_Found_Error : public std::exception {
public:
	const char* what() const noexcept { return NOT_FOUND; }
};



class Empty_Error : public std::exception {
public:
	const char* what() const noexcept { return EMPTY; }
};
#endif