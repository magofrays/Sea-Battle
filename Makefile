all: playField.o shipManager.o Ship.o 
		g++ Ship.o playField.o shipManager.o -o playField
playField.o: playField.cpp playField.h
		g++ -c playField.cpp
shipManager.o: shipManager.cpp shipManager.h
		g++ -c shipManager.cpp
Ship.o: Ship.cpp Ship.h
		g++ -c Ship.cpp 
clear:
	rm *.o