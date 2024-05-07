#include "RandomizePlaces.h"

void RandPosition(int& x, int& y) {
	//srand(time(nullptr));
	if (current_room == 1){
		x = rand() % 1300 - 700;
		y = rand() % 1100 + 4800;
	}
	else if (current_room == 2) {
		x = rand() % 1100 - 650;
		y = rand() % 1100 + 3000;
	}
	else if (current_room == 3) {
		x = rand() % 2000 - 1200;
		y = rand() % 700 + 1500;
	}
	else if (current_room == 4) {
		x = rand() % 1000 - 650;
		y = rand() % 1000 - 50;
	}
	else if (current_room == 5) {
		x = rand() % 1500 - 800;
		y = rand() % 700 - 1900;
	}
}