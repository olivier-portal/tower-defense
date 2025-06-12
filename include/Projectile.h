//
// Created by gravy on 12/06/2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <string>
#include <SFML/System/Vector2.hpp>

class Projectile {
public:
    Projectile();
    ~Projectile();

private:
    std::string sprite;
    sf::Vector2f origin_position;
    sf::Vector2f current_position;
    sf::Vector2f destination_position;
    sf::Vector2f velocity; //const
};

#endif //PROJECTILE_H
