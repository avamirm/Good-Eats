#ifndef NORMAL_USER_HPP
#define NORMAL_USER_HPP

#include "user.hpp"
#include "shelf.hpp"
#include "exceptions.hpp"


class Normal_user : public User
{
public:
	Normal_user(std::string username_, std::string password_);
	~Normal_user();
	std::string set_session_id(std::string id_) override;
	std::string get_session_id() { return session_id; }
	std::string print_user_shelves();
	void add_shelf(Shelf* shelf_);
	void add_to_shelf(Recipe*recipe, const std::string &shelf_id);
	bool find_shelf(const std::string &shelf_id);
	void delete_recipe(const std::string &shelf_id, const std::string &recipe_id);
private:
	std::string session_id;
	std::vector <Shelf*> user_shelves;
};

#endif
