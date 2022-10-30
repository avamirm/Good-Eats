#ifndef SHELF_HPP
#define SHELF_HPP
#include "recipe.hpp"

class Shelf
{
public:
	Shelf(std::string name_, std::string id_);
	std::string print();


	std::string get_id() { return id; }
	void add_recipe(Recipe* recipe);
	std::string print_shelf_recipe(const std::string &shelf_id);
	void find_recipe(const std::string &recipe_id);

private:

	std::vector <Recipe*> recipes;
	std::string id;
	std::string name;
};

#endif

