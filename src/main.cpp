
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <string>

#include <list>

#include "Character/Entity.hpp"

#include "Character/Car.hpp"
#include "Character/Tank.hpp"

#include "Animation/Animation.hpp"

const int Amount = 5;

int main() {

    srand(time(0));

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

    Animation asTank(tTank, 74, 108);
    Animation asCar(tCar, 43, 45);

    // танки, машинки и всё остальное
    std::list <Entity *> objects;

    // создание танчиков
    for (int i = 0; i < Amount; i++) {
        Tank *tank = new Tank();
        Car *car = new Car();

        tank->settings(asTank, rand() % Weight, rand() % Height, rand() % 360);
        car->settings(asCar, rand() % Weight, rand() % Height, rand() % 360);

        // вставка элемента в конец контейнера
        objects.push_back(tank);
        std::cout << i << "-ый танк " << tank->getName() << " создан." << '\n';

        objects.push_back(car);
        std::cout << i << "-ая машинка " << car->getName() << " создана." << '\n';
    }

    while (MWindow.isOpen()) {
        sf::Event event;

        while (MWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                MWindow.close();
        }
        // цикл обновления
        for (auto i = objects.begin(); i != objects.end();) {
            Entity *object = *i;
            object->update();

            if (!object->isAlive()) {
                i = objects.erase(i);
                delete object;
            }
            else
                i++;
        }

        MWindow.clear();

        MWindow.draw(sBackground);

        // отображение танков
        for (auto i:objects)
            i->draw(MWindow);

        MWindow.display();
    }

    return 0;
}
