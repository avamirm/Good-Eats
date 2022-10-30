#include "user.hpp"
#include <iostream>
using namespace std;
User::User(string username_, string password_)
{
	username = username_;
	password = password_;
}
bool User::does_pass_match(const string &pass)
{
	return(password == pass);
}
bool User::has_common_info(const string &username_)
{
	return (username == username_);
}
bool User_Comparator::operator()(User* a, User* b)
{
	return a->get_username() < b->get_username();
}