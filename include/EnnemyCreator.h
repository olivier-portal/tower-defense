//
// Created by gravy on 06/06/2025.
//

#include <string>
#include <deque>
#include <SFML/System/Vector2.hpp>

#ifndef ENNEMY_H
#define ENNEMY_H

class EnnemyCreator {
public:
    EnnemyCreator();
    ~EnnemyCreator();
    void update();


private:
    std::string id;
    std::deque <sf::Vector2i> path;
    sf::Vector2i gridPosition;
    sf::Vector2i NextGridPosition;
    sf::Vector2f pixelPosition;
    float speed;
    int lives;
    bool isAlive;
    int credit;
    int score;

};

#endif //ENNEMY_H
