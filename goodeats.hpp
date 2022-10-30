#ifndef GOODEATS_HPP
#define GOODEATS_HPP

#include "chef.hpp"
#include "normal_user.hpp"

class Goodeats
{
public:
	Goodeats();
	~Goodeats();
	void run();
	std::string print_chef_recipes(const std::string &id_);
	Chef* find_chef_by_id(const std::string &id_);
	void add_recipe(std::string const &title_, std::string const & minutes_to_ready_, std::string const & ingredients_, std::string const & tags_,
		std::string const & vegetarian_, std::string const &image_address_, std::string const &id_);
	void make_chef_delete(const std::string &recipe_id_,const std::string &chef_id);
	void delete_recipe(const std::string &id_);
	std::string print_all_recipes();
	std::string login(const std::string &username_, const std::string &pass);
	std::string find_session_id(const std::string &username_, const std::string &pass);
	std::string print_recipe_info(std::string id_);
	std::string print_user_shelves(std::string user_id);
	std::string  add_user(const std::string &username_, const std::string &pass);
	std::string add_chef(const std::string &username_, const std::string &pass);
	Recipe* find_recipe(const std::string &id_);
	Normal_user* find_user(const std::string &user_id);
	void add_shelf(const std::string &shelf_name,const std::string &user_id);
	std::string print_shelf_recipes(const std::string &shelf_id);
	Shelf* find_shelf(const std::string &shelf_id);
	void make_user_delete(const std::string &total_id, const std::string &user_id);
	void tokenize_(std::string const &str, const char delim, std::vector<std::string> &out);
	void add_recipe_to_shelf(const std::string &shelf_id, const std::string &recipe_id, const std::string &user_id);
	void put_rates(const std::string &recipe_id, const int &score, const std::string &user_id);
	void check_validation(const std::string &username_);
private:
	std::vector<User*> users;
	std::vector <Chef*> chefs;
	std::vector <Normal_user*> normal_users;
	std::vector<Recipe*> recipes_;
	std::vector<Shelf*> shelves;
	int recipe_count;
	int shelves_count;
	int chef_count;
	int user_count;
};
#endif
