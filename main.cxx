
	#include <iostream>
	#include <SFML/Graphics.hpp>
	#include <cmath>
	#include <string>
	
	const int Weight = 1600; // ширина главного окна
	const int Height = 800;  // высота главного окна
	
	const int AmountTanks = 10;
	
	struct point {
		int x;
		int y;
	};
	
	int main() {
		
		srand(time(NULL));
		
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
		
		// фигура хексагон
		sf::CircleShape fHexagon(80, 6);
		
		// массив танков
		point tanks[AmountTanks];
		
		// заполняем массив
		for (int i = 0; i < AmountTanks; i++) {
			tanks[i].x = rand() % Weight;
			tanks[i].y = rand() % Height;
		}		
		
		// свойства спрайтов
		sCar.setPosition(200, 200);
		// sTank.setPosition(200, 300);
		fHexagon.setPosition(200, 300);
		fHexagon.setFillColor(sf::Color::Transparent);
		fHexagon.setOutlineColor(sf::Color::Green);
		fHexagon.setOutlineThickness(1);
		while (MWindow.isOpen()) {
			sf::Event event;
			
			while (MWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) 
					MWindow.close();
			}
			
			MWindow.clear();
			
			MWindow.draw(sBackground);
			
			for (int i = 0; i < 8; i++) {
				sTank.setPosition(tanks[i].x, tanks[i].y);
				MWindow.draw(sTank);
			}			
			MWindow.draw(sCar);
			MWindow.draw(fHexagon);
			MWindow.display();
		}
		
		return 0;
	}
