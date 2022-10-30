#include "normal_user.hpp"
#include <sstream>
using namespace std;

Normal_user::Normal_user(string username_, string password_)
	:User(username_, password_)
{
	is_chef = false;
}

Normal_user::~Normal_user()
{
	for (Shelf* shelf : user_shelves)
		delete shelf;
}
string Normal_user::set_session_id(std::string id_) 
{
	session_id = "user" + id_;
	return session_id;
}
string Normal_user::print_user_shelves()
{
	ostringstream body;
	for (int i = 0; i < user_shelves.size(); i++)
	{
		body
			<< "<tr>" << endl
			<< user_shelves[i]->print() << endl
			<< "</tr>" << endl;
	}
	return body.str();
		
}
void Normal_user::add_shelf(Shelf* shelf_)
{
	user_shelves.push_back(shelf_);
}
void Normal_user::delete_recipe(const string &shelf_id, const string &recipe_id)
{
	for (int i = 0; i < user_shelves.size(); i++)
	{
		if (user_shelves[i]->get_id() == shelf_id)
		{
			user_shelves[i]->find_recipe(recipe_id);
			return;
		}
	}
}
void Normal_user::add_to_shelf(Recipe* recipe, const string &shelf_id)
{
	for (int i = 0; i < user_shelves.size(); i++)
	{
		if (user_shelves[i]->get_id() == shelf_id)
		{
			user_shelves[i]->add_recipe(recipe);
			return;
		}
	}
}
bool Normal_user::find_shelf(const string &shelf_id)
{
	for (int i = 0; i < user_shelves.size(); i++)
	{
		if (user_shelves[i]->get_id() == shelf_id)
		{
			user_shelves[i]->print_shelf_recipe(shelf_id);
			return true;
		}
	}
	return false;
}

