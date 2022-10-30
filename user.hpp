#ifndef USER_HPP
#define USER_HPP

#include "recipe.hpp"

class User
{
public:
	User(std::string username_, std::string password_);
	bool has_common_info(const std::string &username_);
	std::string get_username() { return username; }
	virtual std::string set_session_id(std::string id_)=0;
	bool does_pass_match(const std::string &pass);
protected:
	std::string username;
	std::string password;
	bool is_chef;
};

struct User_Comparator
{
	bool operator()(User* a, User* b);
};

#endif
