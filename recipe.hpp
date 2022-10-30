#ifndef RECIPE_HPP
#define RECIPE_HPP 
#include <vector>
#include <string>
#include <map>
class Normal_user;
class Recipe
{
public:
	Recipe(std::string title_, std::string ingredients_, std::string is_vegetarian_,
		std::string minutes_to_ready_, std::string tags_,std::string image_address_, std::string id_);
	std::string get_title() { return title; }
	std::string print_recipe();
	std::string print_summary();
	std::string get_id() { return id; }
	double get_rating() { return rating; }
	bool has_rated(Normal_user* user);
	void insert_rate(Normal_user* user, const int &score);
	void change_rate(Normal_user* user, const int &score);
	void calculate_rating();
	bool get_is_rated() { return is_rated; }
	double approximate_rate();
	double rate_is_ready();

private:
	std::string title;
	std::string ingredients;
	std::string is_vegetarian;
	std::string minutes_to_ready;
	std::string tags;
	std::string image_address;
	std::string id;
	std::map <Normal_user*, int> rates;
	double rating;
	bool is_rated;
};
struct Recipe_Comparator
{
	bool operator()(Recipe* a, Recipe* b);
};

#endif
