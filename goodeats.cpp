#include "goodeats.hpp"
#include "handlers.hpp"
#include <algorithm>
#include<iomanip>
#include <sstream>
#include <iostream>
using namespace std;

Goodeats::Goodeats()
{
	shelves_count = 0;
	recipe_count = 0;
	chef_count = 0;
	user_count = 0;
}
Goodeats::~Goodeats()
{
	for (Normal_user* normal_user_ : normal_users)
		delete normal_user_;
	for (Chef* chef : chefs)
		delete chef;
}

void Goodeats::run()
{
	Server server(8080);
	server.get("/", new ShowPage("signup.html"));
	server.post("/signup", new Signup_Handler(this));
	server.get("/login",new ShowPage("login.html"));
	server.post("/login", new Login_Handler(this));
	server.get("/chef_home", new Chef_Home_Handler(this));
	server.post("/add_recipe", new ShowPage("add_recipe.html"));
	server.post("/add_chef_recipe", new Add_Recipe_Handler(this));
	server.get("/delete_recipe", new Delete_Recipe_Handler(this));
	server.get("/user_home", new User_Home_Handler(this));
	server.get("/recipe_info", new Recipe_Info_Handler(this));
	server.get("/show_shelves", new Show_Shelves_Handler(this));
	server.post("/add_shelf", new ShowPage("add_shelf.html"));
	server.post("/add_user_shelf", new Add_Shelf_Handler(this));
	server.get("/shelf_info", new Shelf_Info_Handler(this));
	server.get("/delete_shelf_recipe", new Delete_Shelf_Recipe_Handler(this));
	server.post("/add_recipe_to_shelf", new Add_Recipe_To_Shelf_Handler(this));
	server.post("/put_rate", new Put_Rate_Handler(this));
	server.get("/logout", new Logout_Handler(this));
	server.run();
}
string Goodeats::add_chef(const std::string &username_, const std::string &pass)
{
	Chef* chef_ = new Chef(username_, pass);
	chefs.push_back(chef_);
	users.push_back(chef_);
	chef_count = chef_count + 1;
	return(chef_->set_session_id(to_string(chef_count)));

}
string Goodeats::add_user(const std::string &username_, const std::string &pass)
{
	Normal_user* user_ = new Normal_user(username_, pass);
	normal_users.push_back(user_);
	users.push_back(user_);
	user_count = user_count + 1;
	return(user_->set_session_id(to_string(user_count)));

}


Chef* Goodeats::find_chef_by_id(const std::string &id_)
{
	for (Chef* chef : chefs)
	{
		if (chef->get_session_id() == id_)
			return chef;
	}
	return nullptr;
}
string Goodeats::print_chef_recipes(const string &id_)
{
	Chef* chef_ = find_chef_by_id(id_);
	return(chef_->print_chef_recipes());
}
void Goodeats::add_recipe(std::string const &title_, std::string const & minutes_to_ready_, std::string const & ingredients_,
	std::string const & tags_, std::string const & vegetarian_,const std::string &image_address_, std::string const &id_)
{
	Chef* chef_ = find_chef_by_id(id_);
	recipe_count = recipe_count + 1;
	Recipe* recipe_ = new Recipe(title_, ingredients_, vegetarian_, minutes_to_ready_, tags_,image_address_, to_string(recipe_count));
	recipes_.push_back(recipe_);
	chef_->post_recipes(recipe_);
}
void Goodeats::make_chef_delete(const std::string &recipe_id_,const std::string &chef_id)
{
	Chef* chef_ = find_chef_by_id(chef_id);
	chef_->delete_chef_recipe(recipe_id_);
	delete_recipe(recipe_id_);
}
void Goodeats::delete_recipe(const string &id_)
{
	for (int i = 0; i < recipes_.size(); i++)
	{
		if (recipes_[i]->get_id() == id_)
		{
			recipes_.erase(recipes_.begin() + i);
			return;
		}
	}
}
string Goodeats::print_all_recipes()
{
	ostringstream body;
	for (int i = 0; i < recipes_.size(); i++)
	{
		body
			<< "<tr>" << endl
			<< recipes_[i]->print_summary() << endl
			<< "</tr>" << endl;
	}
	return body.str();
}

string Goodeats::login(const std::string &username_,const std::string &pass)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->has_common_info(username_) && users[i]->does_pass_match(pass))
			return find_session_id(username_,pass);
	}
	throw Bad_Request_Error();
}
std::string Goodeats::find_session_id(const std::string &username_, const std::string &pass)
{
	for (int i = 0; i < chefs.size(); i++)
		if (chefs[i]->has_common_info(username_) && chefs[i]->does_pass_match(pass))
			return (chefs[i]->get_session_id());
	for (int i = 0; i < normal_users.size(); i++)
		if (normal_users[i]->has_common_info(username_) && normal_users[i]->does_pass_match(pass))
			return (normal_users[i]->get_session_id());
	return "";		
}
std::string Goodeats::print_recipe_info(std::string id_)
{
	ostringstream body;
	Recipe* recipe = find_recipe(id_);
	body << (recipe->print_recipe()) << endl;
	return body.str();
}
Recipe* Goodeats::find_recipe(const string &id_)
{
	for (Recipe* recipe : recipes_)
	{
		if (recipe->get_id() == id_)
			return recipe;
	}
	return nullptr;
}
std::string Goodeats::print_user_shelves(std::string user_id)
{
	Normal_user* user = find_user(user_id);
	return(user->print_user_shelves());
}
Normal_user* Goodeats::find_user(const string &user_id)
{
	for (Normal_user* user : normal_users)
		if (user->get_session_id() == user_id)
			return user;
	return nullptr;
}
void Goodeats::add_shelf(const std::string &shelf_name,const std::string &user_id)
{
	shelves_count = shelves_count + 1;
	Shelf* shelf_ = new Shelf(shelf_name, to_string(shelves_count));
	Normal_user* user = find_user(user_id);
	user->add_shelf(shelf_);
	shelves.push_back(shelf_);
}
std::string Goodeats::print_shelf_recipes(const std::string &shelf_id)
{
	Shelf* shelf = find_shelf(shelf_id);
	return (shelf->print_shelf_recipe(shelf_id));
}
Shelf* Goodeats::find_shelf(const std::string &shelf_id)
{
	for (Shelf* shelf : shelves)
	{
		if (shelf->get_id() == shelf_id)
			return shelf;
	}
	return nullptr;
}
void Goodeats::make_user_delete(const std::string &total_id, const std::string &user_id)
{
	Normal_user* user = find_user(user_id);
	vector <string> ids;
	tokenize_(total_id, ' ', ids);
	user->delete_recipe(ids[0], ids[1]);
}
void Goodeats::tokenize_(string const &str, const char delim, vector<string> &out)
{
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}
void Goodeats::add_recipe_to_shelf(const string &shelf_id, const string &recipe_id, const string &user_id)
{
	Normal_user* user = find_user(user_id);
	Recipe* recipe = find_recipe(recipe_id);
	if (recipe == nullptr)
		throw Not_Found_Error();
	user->add_to_shelf(recipe, shelf_id);

}
void Goodeats::put_rates(const std::string &recipe_id, const int &score, const string &user_id)
{
	Normal_user* user = find_user(user_id);
	Recipe* recipe = find_recipe(recipe_id);
	if (recipe->has_rated(user) == false)
		recipe->insert_rate(user, score);
	else
	recipe->change_rate(user, score);
}
void Goodeats::check_validation(const string &username_)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->has_common_info(username_))
			throw Bad_Request_Error();
	}
}