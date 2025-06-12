//
// Created by gravy on 10/06/2025.
//

#include "../include/stalkerEnemy.h"

stalkerEnemy::stalkerEnemy(const std::string& id, const std::deque <sf::Vector2i>& path, float speed, int lives, const int credit, const int score, const std::string_view sprite) : EnemyCreator(id, path, speed, lives, credit, score, std::string(sprite)) {}