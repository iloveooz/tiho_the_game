
	#include <iostream>
	#include <SFML/Graphics.hpp>
	#include <cmath>
	#include <string>
	
	const int Weight = 1600; // ширина главного окна
	const int Height = 800;  // высота главного окна
	
	int main() {
		
		std::cout << "start!" << std::endl;
		
		// создаём основное окно
		sf::RenderWindow MWindow(sf::VideoMode(Weight, Height), "Tycho Planet");
		MWindow.setFramerateLimit(60);
		
		// загружаем текстуры
		sf::Texture tBackground;
		tBackground.loadFromFile("images/terrain.png");
		
		sf::Texture tCar;
		tCar.loadFromFile("images/car.png");
		
		sf::Texture tTank;
		tTank.loadFromFile("images/tank.png");
		
		// создаём спрайты
		sf::Sprite sBackground(tBackground);
		sf::Sprite sCar(tCar);
		sf::Sprite sTank(tTank);
		
		while (MWindow.isOpen()) {
			sf::Event event;
			
			while (MWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) 
					MWindow.close();
			}
			
			MWindow.clear();
			
			MWindow.draw(sBackground);
			
			MWindow.display();
		}
		
		return 0;
	}
