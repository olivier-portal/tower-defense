//
// Created by gravy on 06/06/2025.
//

#include "../include/EnemyCreator.h"

EnemyCreator::EnemyCreator(std::string id, std::deque <sf::Vector2i> path, float speed, int lives, int credit, int score) : id(id), path(path), speed(speed), lives(lives), credit(credit), score(score) {
    advancePath();
};


void EnemyCreator::advancePath() {
    if (path.empty()) {
        gridPosition.reset();
        isArrived = true;
        return;
    }
    gridPosition = path.front();
    path.pop_front();

    if (!path.empty()) {
        nextGridPosition = path.front();
    } else {
        nextGridPosition.reset();
    }
}

void EnemyCreator::update() {}