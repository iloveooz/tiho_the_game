#ifndef TIHO_WORKER_HPP
#define TIHO_WORKER_HPP

#include "Entity.hpp"

class Worker : public Entity {
public:
    Worker();

    void doGo(sf::Vector2f& position) override;

    void update() override;
};

#endif //TIHO_WORKER_HPP
