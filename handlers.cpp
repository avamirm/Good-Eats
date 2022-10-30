#include "handlers.hpp"
#include "goodeats.hpp"
#include "exceptions.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

Response *Signup_Handler::callback(Request *req)
{
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	std::ostringstream body;
	try
	{
		goodeats->check_validation(req->getBodyParam("username"));
		if (req->getBodyParam("user_type") == "chef")
		{
			string id = goodeats->add_chef(req->getBodyParam("username"), req->getBodyParam("password"));
			res = Response::redirect("/chef_home");
			res->setSessionId(id);
		}
		else
		{
			string id_ = goodeats->add_user(req->getBodyParam("username"), req->getBodyParam("password"));
			res = Response::redirect("/user_home");
			res->setSessionId(id_);
		}
	} 
	catch (std::exception& e)
	{
		body << "<!DOCTYPE html>" << "<html>"
			<< "<head>An error has ocuured while trying to sign you up!</head>"
			<< "<br/>" << "<p>Error message: " << e.what() << "</p>" << "<a href = \"/\">try again</a></html>";
		res->setBody(body.str());
	}
	return res;
}
Response *Logout_Handler::callback(Request *req)
{
	Response *res = new Response;
	res->setSessionId("");
	res = Response::redirect("/");
	return res;
}
Response *Login_Handler::callback(Request *req)
{
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	try
	{
		string id_ = goodeats->login(req->getBodyParam("username"), req->getBodyParam("password"));
		if (id_[0] == 'c')
		{
			res = Response::redirect("/chef_home");
			res->setSessionId(id_);
		}
		else
		{
			res = Response::redirect("/user_home");
			res->setSessionId(id_);
		}
	}
	catch (std::exception& e)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>"
			<< "<head>An error has ocuured while trying to login!</head>"
			<< "<br/>" << "<p>Error message: " << e.what() << "</p>" << "</html>";
		res->setBody(error_body.str());
	}
	return res;
}
Response *Chef_Home_Handler::callback(Request *req)
{
	Response *res = new Response;
	std::ostringstream body;
	res->setHeader("Content-Type", "text/html");
	body << "<!DOCTYPE html>" << endl
		<< "<html>" << endl
		<< "<head>" << endl
		<< "<style>" 
		<< "body{" << endl
		<< "background-image: url('food.png');" << endl
		<< "background-repeat: no-repeat;" << endl
		<< "background - size: cover;" << endl
		<< "}" << endl
		<< "table{" << endl
		<< "font-family:arial,sans-serif;" << endl
		<< "border-collapse:collapse;" << endl
		<< "width:100 %;" << endl
		<< "}" << endl
		<< "td,th{" << endl
		<< "border: 1px solid #dddddd;" << endl
		<< "text-align:left;" << endl
		<< "padding: 8px;" << endl
		<< "}" << endl
		<< "tr:nth-child(even) {" << endl
		<< " background-color:#dddddd;" << endl
		<< "}" << endl
		<< "table,th,td{"
		<< "border: 2px solid black;" << endl
		<< "}" << endl
		<< "</style>" << endl
		<< "</head>" << endl
		<< "<body>" << endl
		<< "<h2 style ='color:DeepPink;'>My Recipes</h2>" << endl
		<< "<table>" << endl
		<< "<tr>" << endl
		<< "<th>Recipe id</th>" << endl
		<< "<th>Recipe name</th>" << endl
		<< "<th>Vegetarian</th>" << endl
		<< "<th>Time to get ready</th>" << endl
		<< "<th>Ingredients</th>" << endl
		<< "<th>tags</th>" << endl
		<< "<th>rate</th>" << endl
		<< "<th></th>" << endl
		<< "</tr>" << endl
		<< goodeats->print_chef_recipes(req->getSessionId())
		<< "</table>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<form action = '/add_recipe' method = 'POST'>" << endl
		<< "<input style = 'background-color:DarkSalmon;' type='submit' value='add new recipe'>" << endl
		<< "</form>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<a style ='color:DeepPink;' href ='/logout'>logout</a>" << endl
		<< "</body>" << endl
		<< "</html>" << endl;
	res->setBody(body.str());
	return res;
}
Response *Add_Recipe_Handler::callback(Request *req)
{
	Response *res;
	string title_ = req->getBodyParam("recipe_title");
	string minutes_to_ready_ = req->getBodyParam("minutes_to_ready");
	string ingredients_ = req->getBodyParam("ingredients");
	string tags_ = req->getBodyParam("tags");
	string vegetarian_ = req->getBodyParam("vegetarian_status");
	string image_address_ = req->getBodyParam("image_address");
	goodeats->add_recipe(title_, minutes_to_ready_, ingredients_, tags_, vegetarian_,image_address_, req->getSessionId());
	res = Response::redirect("/chef_home");
	return res;
}
Response *Delete_Recipe_Handler::callback(Request *req)
{
	Response *res;
	goodeats->make_chef_delete(req->getQueryParam("id"), req->getSessionId());
	
	res = Response::redirect("/chef_home");
	return res;
}
Response *User_Home_Handler::callback(Request *req)
{
	Response *res = new Response;
	std::ostringstream body;
	res->setHeader("Content-Type", "text/html");
	body << "<!DOCTYPE html>" << endl
		<< "<html>" << endl
		<< "<head>" << endl
		<< "<style>" 
		<< "body{" << endl
		<< "background-image:url('food.png');" << endl
		<< "background-repeat: no-repeat;" << endl
		<< "background - size: cover;" << endl
		<< "}" << endl
		<< "table{" << endl
		<< "font-family:arial,sans-serif;" << endl
		<< "border-collapse:collapse;" << endl
		<< "width:100 %;" << endl
		<< "}" << endl
		<< "td,th{" << endl
		<< "border: 1px solid #dddddd;" << endl
		<< "text-align:left;" << endl
		<< "padding: 8px;" << endl
		<< "}" << endl
		<< "tr:nth-child(even) {" << endl
		<< " background-color:#dddddd;" << endl
		<< "}" << endl
		<< "table,th,td{"
		<< "border: 2px solid black;" << endl
		<< "}" << endl
		<< "</style>" << endl
		<< "</head>" << endl
		<< "<body>" << endl
		<< "<h2 style ='color:DeepPink;'>All Recipes</h2>" << endl
		<< "<table>" << endl
		<< "<tr>" << endl
		<< "<th>Recipe id</th>" << endl
		<< "<th>Recipe name</th>" << endl
		<< "<th>Vegetarian</th>" << endl
		<< "<th>Time to get ready</th>" << endl
		<< "</tr>" << endl
		<< goodeats->print_all_recipes()
		<< "</table>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<form action = '/show_shelves' method = 'GET'>" << endl
		<< "<input style = 'background-color:DarkSalmon;' type='submit' value='show shelves'>" << endl
		<< "</form>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<a style ='color:DeepPink;' href ='/logout'>logout</a>" << endl
		<< "</body>" << endl
		<< "</html>" << endl;
	res->setBody(body.str());
	return res;
}
Response *Recipe_Info_Handler::callback(Request *req)
{
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	ostringstream body;
	std::string id = req->getQueryParam("id");
	body << "<!DOCTYPE html>" << endl
		<< "<html>" << endl
		<< "<head>" << endl
		<< "<style>" << endl
		<< "body{" << endl
		<< "background-image:url('food.png');" << endl
		<< "background-repeat: no-repeat;" << endl
	    <<"background - size: cover;" <<endl
	    <<"}" <<endl		
		<<"table{" << endl
		<< "font-family:arial,sans-serif;" << endl
		<< "border-collapse:collapse;" << endl
		<< "width:100 %;" << endl
		<< "}" << endl
		<< "td,th{" << endl
		<< "border: 1px solid #dddddd;" << endl
		<< "text-align:left;" << endl
		<< "padding: 8px;" << endl
		<< "}" << endl
		<< "tr:nth-child(even) {" << endl
		<< " background-color:#dddddd;" << endl
		<< "}" << endl
		<< "table,th,td{"
		<< "border: 2px solid black;" << endl
		<< "}" << endl
		<< "</style>" << endl
		<< "</head>" << endl
		<< "<body>" << endl
		<< "<h2 style ='color:DeepPink;'>Recipe info</h2>" << endl
		<< "<table>" << endl
		<< "<tr>" << endl
		<< "<th>Recipe id</th>" << endl
		<< "<th>Recipe name</th>" << endl
		<< "<th>Vegetarian</th>" << endl
		<< "<th>Time to get ready</th>" << endl
		<< "<th>Ingredients</th>" << endl
		<< "<th>tags</th>" << endl
		<< "<th>rate</th>" << endl
		<< "</tr>" << endl
		<< goodeats->print_recipe_info(id)
		<< "</table>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<form action='/put_rate' method='POST'>"
		<< "<label style='color:Purple;' for='rate'>" << "Rate:" << "</label><br>"
		<< "<input style='background-color:LightGrey;' type='text' id='rate' name='rate' placeholder='enter rate' required>" << "<br>"
		<< "<input type='hidden' name='recipe_id' value='" << id << "'>" << endl
		<< "<h6>" << endl
		<< "</h6>" << endl
		<< "<input style = 'background-color:DarkSalmon;' type='submit' value='put rate'>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<a style ='color:DeepPink;' href ='/logout'>logout</a>" << endl
		<< "</body>" << endl
		<< "</html>" << endl;
	res->setBody(body.str());
	return res;
}


Response *Show_Shelves_Handler::callback(Request *req)
{
	Response *res = new Response;
	std::ostringstream body;
	res->setHeader("Content-Type", "text/html");
	body << "<!DOCTYPE html>" << endl
		<< "<html>" << endl
		<< "<head>" << endl
		<< "<style>" 
		<< "body{" << endl
		<< "background-image:url('food.png');" << endl
		<< "background-repeat: no-repeat;" << endl
		<< "background - size: cover;" << endl
		<< "}" << endl
		<< "table{" << endl
		<< "font-family:arial,sans-serif;" << endl
		<< "border-collapse:collapse;" << endl
		<< "width:100 %;" << endl
		<< "}" << endl
		<< "td,th{" << endl
		<< "border: 1px solid #dddddd;" << endl
		<< "text-align:left;" << endl
		<< "padding: 8px;" << endl
		<< "}" << endl
		<< "tr:nth-child(even) {" << endl
		<< " background-color:#dddddd;" << endl
		<< "}" << endl
		<< "table,th,td{"
		<< "border: 2px solid black;" << endl
		<< "}" << endl
		<< "</style>" << endl
		<< "</head>" << endl
		<< "<body>" << endl
		<< "<h2 style ='color:DeepPink;'>My Shelves</h2>" << endl
		<< "<table>" << endl
		<< "<tr>" << endl
		<< "<th>Shelf id</th>" << endl
		<< "<th>Shelf name</th>" << endl
		<< "</tr>" << endl
		<< goodeats->print_user_shelves(req->getSessionId())
		<< "</table>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<form action = '/add_shelf' method = 'POST'>" << endl
		<< "<input style = 'background-color:DarkSalmon;' type='submit' value='add new shelf'>" << endl
		<< "</form>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<a style ='color:DeepPink;' href ='/logout'>logout</a>" << endl
		<< "</body>" << endl
		<< "</html>" << endl;
	res->setBody(body.str());
	return res;
}
Response *Add_Shelf_Handler::callback(Request *req)
{
	Response *res;
	string title_ = req->getBodyParam("shelf_title");
	goodeats->add_shelf(title_,  req->getSessionId());
	res = Response::redirect("/show_shelves");
	return res;
}
Response *Shelf_Info_Handler::callback(Request *req)
{
	Response *res = new Response;
	std::ostringstream body;
	res->setSessionId(req->getSessionId());
	res->setHeader("Content-Type", "text/html");
	std::string id = req->getQueryParam("id");
	body << "<!DOCTYPE html>" << endl
		<< "<html>" << endl
		<< "<head>" << endl
		<< "<style>" 
		<< "body{" << endl
		<< "background-image:url('food.png');" << endl
		<< "background-repeat: no-repeat;" << endl
		<< "background - size: cover;" << endl
		<< "}" << endl
		<< "table{" << endl
		<< "font-family:arial,sans-serif;" << endl
		<< "border-collapse:collapse;" << endl
		<< "width:100 %;" << endl
		<< "}" << endl
		<< "td,th{" << endl
		<< "border: 1px solid #dddddd;" << endl
		<< "text-align:left;" << endl
		<< "padding: 8px;" << endl
		<< "}" << endl
		<< "tr:nth-child(even) {" << endl
		<< " background-color:#dddddd;" << endl
		<< "}" << endl
		<< "table,th,td{"
		<< "border: 2px solid black;" << endl
		<< "}" << endl
		<< "</style>" << endl
		<< "</head>" << endl
		<< "<body>" << endl
		<< "<h2 style ='color:DeepPink;'>Shelf Recipes</h2>" << endl
		<< "<table>" << endl
		<< "<tr>" << endl
		<< "<th>Recipe id</th>" << endl
		<< "<th>Recipe name</th>" << endl
		<< "<th>Vegetarian</th>" << endl
		<< "<th>Time to get ready</th>" << endl
		<< "<th></th>" << endl
		<< "</tr>" << endl
		<< goodeats->print_shelf_recipes(id)
		<< "</table>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<< "<h3>" << endl
		<< "</h3>" << endl
		<<"<form action='/add_recipe_to_shelf' method='POST'>"
		<<"<label style='color:Purple;' for='recipe_id'>" << "Recipe id:" << "</label><br>"
		<<"<input style='background-color:LightGrey;' type='text' id='recipe_id' name='recipe_id' placeholder='enter recipe id' required>" <<"<br>" 
		<< "<input type='hidden' name='shelf_id' value='" << id << "'>" << endl
		<< "<input style = 'background-color:DarkSalmon;' type='submit' value='add recipe'>" << endl
		<< "<a style ='color:DeepPink;' href ='/logout'>logout</a>" << endl
		<< "</body>" << endl
		<< "</html>" << endl;
	res->setBody(body.str());
	return res;
}
Response *Delete_Shelf_Recipe_Handler::callback(Request *req)
{
	Response *res;
	goodeats->make_user_delete(req->getQueryParam("id"), req->getSessionId());
	res = Response::redirect("/show_shelves");
	return res;
}
Response *Add_Recipe_To_Shelf_Handler::callback(Request *req)
{
	Response *res = new Response;
	
	res->setHeader("Content-Type", "text/html");
	std::ostringstream body;
	try
	{
		string shelf_id = req->getBodyParam("shelf_id");
		string recipe_id = req->getBodyParam("recipe_id");
		goodeats->add_recipe_to_shelf(shelf_id, recipe_id, req->getSessionId());
		res = Response::redirect("/show_shelves");
	}
	catch (std::exception& e)
	{
		body << "<!DOCTYPE html>" << "<html>"
			<< "<head>An error has ocuured while trying to add recipe!</head>"
			<< "<br/>" << "<p>Error message: " << e.what() << "</p>" << "<a href = \"/show_shelves\">try again</a></html>";
		res->setBody(body.str());
	}
	return res;
}
Response *Put_Rate_Handler::callback(Request *req)
{
	Response *res;
	string score = req->getBodyParam("rate");
	string recipe_id = req->getBodyParam("recipe_id");
	goodeats->put_rates(recipe_id, stoi(score), req->getSessionId());
	res = Response::redirect("/user_home");
	return res;
}