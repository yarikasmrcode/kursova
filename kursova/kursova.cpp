#include "Game.h"
#include <time.h>

int main() {

	srand(static_cast<unsigned>(time(0))); //random number generator

	sf::Music music;
	if (!music.openFromFile("Sounds/music.ogg"))
		std::cout << "wrong my man";
	music.play();

	Game game;
	game.run();

	return 0;
}