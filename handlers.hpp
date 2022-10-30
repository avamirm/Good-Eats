#ifndef HANDLERS_HPP
#define HANDLERS_HPP 
#include "server/server.hpp"
class Goodeats;

class Signup_Handler : public RequestHandler {
public:
	Signup_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};

class Chef_Home_Handler : public RequestHandler {
public:
	Chef_Home_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Add_Recipe_Handler : public RequestHandler {
public:
	Add_Recipe_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Delete_Recipe_Handler : public RequestHandler {
public:
	Delete_Recipe_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class User_Home_Handler : public RequestHandler {
public:
	User_Home_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Logout_Handler : public RequestHandler {
public:
	Logout_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Login_Handler : public RequestHandler {
public:
	Login_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};

class Recipe_Info_Handler : public RequestHandler {
public:
	Recipe_Info_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Show_Shelves_Handler : public RequestHandler {
public:
	Show_Shelves_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Add_Shelf_Handler : public RequestHandler {
public:
	Add_Shelf_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Shelf_Info_Handler : public RequestHandler {
public:
	Shelf_Info_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Delete_Shelf_Recipe_Handler : public RequestHandler {
public:
	Delete_Shelf_Recipe_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Add_Recipe_To_Shelf_Handler : public RequestHandler {
public:
	Add_Recipe_To_Shelf_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
class Put_Rate_Handler : public RequestHandler {
public:
	Put_Rate_Handler(Goodeats* goodeats_) : goodeats(goodeats_) {};
	Response *callback(Request *);
private:
	Goodeats* goodeats;
};
#endif
