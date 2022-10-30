CC=g++ --std=c++11
EXE_FILE=goodeats.out
all: $(EXE_FILE) 

goodeats.out: main.o goodeats.o user.o normal_user.o chef.o exceptions.o shelf.o recipe.o handlers.o utilities.o request.o response.o template_parser.o server.o route.o
	$(CC) main.o goodeats.o user.o normal_user.o chef.o exceptions.o shelf.o recipe.o handlers.o utilities.o request.o response.o template_parser.o server.o route.o -o $(EXE_FILE)

main.o: goodeats.hpp user.hpp normal_user.hpp chef.hpp exceptions.hpp shelf.hpp recipe.hpp main.cpp
	$(CC) -c main.cpp -o main.o

exceptions.o: exceptions.hpp exceptions.cpp
	$(CC) -c exceptions.cpp -o exceptions.o

goodeats.o: goodeats.hpp user.hpp normal_user.hpp chef.hpp exceptions.hpp shelf.hpp recipe.hpp handlers.hpp goodeats.cpp
	$(CC) -c goodeats.cpp -o goodeats.o	

user.o: user.hpp recipe.hpp user.cpp
	$(CC) -c user.cpp -o user.o	

normal_user.o: user.hpp normal_user.hpp exceptions.hpp shelf.hpp recipe.hpp normal_user.cpp
	$(CC) -c normal_user.cpp -o normal_user.o	

chef.o: chef.hpp user.hpp exceptions.hpp recipe.hpp chef.cpp
	$(CC) -c chef.cpp -o chef.o	

shelf.o: shelf.hpp recipe.hpp exceptions.hpp recipe.hpp shelf.cpp
	$(CC) -c shelf.cpp -o shelf.o

recipe.o: recipe.hpp recipe.cpp
	$(CC) -c recipe.cpp -o recipe.o

handlers.o: handlers.cpp handlers.hpp goodeats.hpp server/server.hpp
	$(CC) -c handlers.cpp handlers.hpp server/server.hpp

template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) -c utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp utils/response.hpp utils/include.hpp

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp utils/utilities.hpp

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) -c server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp 

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp 

clean:
	rm *.o $(EXE_FILE)