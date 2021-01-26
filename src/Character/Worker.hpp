#ifndef TIHO_WORKER_HPP
#define TIHO_WORKER_HPP

#include "Entity.hpp"

class Worker : public Entity {
public:
    Worker();

    void update(double dx, double dy) override;
};

#endif //TIHO_WORKER_HPP
