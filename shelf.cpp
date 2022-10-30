#include "shelf.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

Shelf::Shelf(string name_, string id_)
{
	name = name_;
	id = id_;
}
string Shelf::print()
{
	ostringstream body;
	body
		<< "<td>" << "<a href='/shelf_info?id=" << id << "'>" << id << "</a></td>" << endl
		<< "<td>" << name << endl << "</td>" << endl;
	return body.str();
}
std::string Shelf::print_shelf_recipe(const std::string &shelf_id)
{
	ostringstream body;
	sort(recipes.begin(), recipes.end(), Recipe_Comparator());
	for (int i = 0; i < recipes.size(); i++)
	{
		string total_id = shelf_id + " " + recipes[i]->get_id();
		body
			<< "<tr>" << endl
			<< recipes[i]->print_summary() << endl
			<< "<td>" << "<a href='/delete_shelf_recipe?id=" << total_id << "'>" << "Delete" << "</a></td>" << endl
			<< "</tr>" << endl;
	}
	return body.str();
}
void Shelf::find_recipe(const string &recipe_id)
{
	for (int i = 0; i < recipes.size(); i++)
	{
		if (recipes[i]->get_id() == recipe_id)
		{
			recipes.erase(recipes.begin() + i);
			return;
		}
	}
}
void Shelf::add_recipe(Recipe* recipe)
{
	recipes.push_back(recipe);	
}
