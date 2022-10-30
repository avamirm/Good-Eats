#ifndef CHEF_HPP
#define CHEF_HPP

#include"user.hpp"
#include"exceptions.hpp"

class Chef : public User
{
public:
	Chef(std::string username_, std::string password_);
	~Chef();
	std::string set_session_id(std::string id_) override;
	std::string print_chef_recipes();
	std::string get_session_id() { return session_id; }
	void post_recipes(Recipe* recipe_);
	Recipe* find_recipe_by_id(const std::string &id_);
	void delete_chef_recipe(const std::string &id_);

private:
	std::string session_id;
	std::vector < Recipe*> chef_recipes;
	double rating;
};

#endif
