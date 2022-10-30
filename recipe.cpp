#include "recipe.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
using namespace std;
bool Recipe_Comparator::operator()(Recipe* a, Recipe* b)
{
	return a->get_title() < b->get_title();
}
Recipe::Recipe(std::string title_, std::string ingredients_, std::string is_vegetarian_,
	std::string minutes_to_ready_, std::string tags_,std::string image_address_,  string id_)
{
	title = title_;
	ingredients = ingredients_;
	is_vegetarian = is_vegetarian_;
	minutes_to_ready = minutes_to_ready_;
	tags = tags_;
	id = id_;
	image_address = image_address_;
	rating = 0.0;
	is_rated = false;
}

std::string Recipe::print_recipe()
{
	ostringstream body;
	double rate_ = 0.0;
	if (rates.size())
	{
		rate_ = rate_is_ready();
	}
	body
		<< "<td>" << id << endl << "</td>" << endl
		<< "<td>" << title << endl << "</td>" << endl
		<< "<td>" << is_vegetarian << endl << "</td>" << endl
		<< "<td>" << minutes_to_ready << endl << "</td>" << endl
		<< "<td>" << ingredients << endl << "</td>" << endl
		<< "<td>" << tags << endl << "</td>" << endl
		<< "<td>" << std::fixed << std::setprecision(1) << to_string(rate_) << endl << "</td>" << endl
		<< "<img src='" << image_address << "'alt='food'><br>" << endl;
	return body.str();
}

string Recipe::print_summary()
{
	ostringstream body;
	body
		<< "<td>" << "<a href='/recipe_info?id=" << id << "'>" << id << "</a></td>"
		<< "<td>" << title << endl << "</td>" << endl
		<< "<td>" << is_vegetarian << endl << "</td>" << endl
		<< "<td>" << minutes_to_ready << endl << "</td>" << endl;
	return body.str();
}

bool Recipe::has_rated(Normal_user* user)
{
	std::map<Normal_user*, int>::iterator finder;
	finder = rates.find(user);
	if (finder == rates.end())
		return false;
	else
		return true;
}
void Recipe::change_rate(Normal_user* user, const int &score)
{
	std::map<Normal_user*, int>::iterator finder;
	finder = rates.find(user);
	rates.erase(finder);
	rates.insert({ user, score });
}
void Recipe::insert_rate(Normal_user* user, const int &score)
{
	rates.insert({ user,score });
	is_rated = true;
}

void Recipe::calculate_rating()
{
	if (rates.size() != 0)
	{
		double sum = 0.0;
		for (auto itr = rates.begin(); itr != rates.end(); ++itr)
			sum = sum + itr->second;
		rating = sum / rates.size();
	}

}
double Recipe::approximate_rate()
{
	double result = ceil(rating * 10) / 10;
	return result;
}
double Recipe::rate_is_ready()
{
	calculate_rating();
	double result = approximate_rate();
	return result;
}
