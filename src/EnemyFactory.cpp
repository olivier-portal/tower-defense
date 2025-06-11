//
// Created by gravy on 06/06/2025.
//

#include "../include/EnemyFactory.h"

EnemyFactory::EnemyFactory() {
    creators["grunt"] = enemy_creator::createGrunt;
    creators["stalker"] = enemy_creator::createStalker;
    creators["juggernaut"] = enemy_creator::createJuggernaut;
}

std::unique_ptr<EnemyCreator> EnemyFactory::create(const std::string &type, const std::string &id, const std::deque<sf::Vector2i> &path) const {
    // Use a constant iterator to avoid modifying the map while iterating over it
    std::unordered_map<std::string, std::function<std::unique_ptr<EnemyCreator>(const std::string&, const std::deque<sf::Vector2i>&)>>::const_iterator it = creators.find(type);
    if (it != creators.end()) {
        return it->second(id, path);
    }
    throw std::runtime_error("Type not found:" + type);
}

