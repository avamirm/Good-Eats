#include "chef.hpp"
#include <algorithm>
#include<iomanip>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

Chef::Chef(string username_, string password_)
	:User(username_, password_)
{
	is_chef = true;
	rating = 0.0;
}
Chef::~Chef()
{
	for (Recipe* recipe : chef_recipes)
		delete recipe;
}

std::string Chef::set_session_id(std::string id_)
{
	session_id = "chef" + id_ ;
	return session_id;
}
string Chef::print_chef_recipes()
{
	std::ostringstream body;
	sort(chef_recipes.begin(), chef_recipes.end(), Recipe_Comparator());
	for (int i = 0; i < chef_recipes.size(); i++)
	{
		body
			<< "<tr>" << endl
			<< chef_recipes[i]->print_recipe() << endl
			<< "<td>" << "<a href='/delete_recipe?id=" << chef_recipes[i]->get_id() << "'>" << "Delete" << "</a></td>" << endl
			<< "</tr>" << endl;
	}
	return body.str();
}
void Chef::post_recipes(Recipe* recipe_)
{
	chef_recipes.push_back(recipe_);
}
void Chef::delete_chef_recipe(const string &id_)
{
	for (int i = 0; i < chef_recipes.size(); i++)
	{
		if (chef_recipes[i]->get_id() == id_)
		{
			chef_recipes.erase(chef_recipes.begin() + i);
			return;
		}
	}
}

Recipe* Chef::find_recipe_by_id(const string &id_)
{
	for (Recipe* recipe : chef_recipes)
	{
		if (recipe->get_id() == id_)
		{
			return recipe;
		}
	}
	return nullptr;
}
