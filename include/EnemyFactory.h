//
// Created by gravy on 06/06/2025.
//
#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <unordered_map>
#include <functional>
#include <string>
#include <deque>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "EnemyCreator.h"
#include "gruntEnemy.h"
#include "stalkerEnemy.h"
#include "juggernautEnemy.h"

/**
 * @namespace enemy_creator
 * @brief Contains factory functions for creating different types of enemies
 */
namespace enemy_creator {
    /**
     * @brief Creates a grunt enemy unit
     * @param id Unique identifier for the enemy
     * @param path Path that the enemy will follow
     * @return A unique pointer to the created enemy
     */
    std::unique_ptr<EnemyCreator> createGrunt(const std::string& id, const std::deque<sf::Vector2i>& path);

    /**
     * @brief Creates a stalker enemy unit
     * @param id Unique identifier for the enemy
     * @param path Path that the enemy will follow
     * @return A unique pointer to the created enemy
     */
    std::unique_ptr<EnemyCreator> createStalker(const std::string& id, const std::deque<sf::Vector2i>& path);

    /**
     * @brief Creates a juggernaut enemy unit
     * @param id Unique identifier for the enemy
     * @param path Path that the enemy will follow
     * @return A unique pointer to the created enemy
     */
    std::unique_ptr<EnemyCreator> createJuggernaut(const std::string& id, const std::deque<sf::Vector2i>& path);
}


/**
 * @class EnemyFactory
 * @brief Factory class responsible for creating different types of enemies
 *
 * This factory maintains a registry of enemy creators and provides a unified
 * interface for creating different types of enemies in the game.
 */
class EnemyFactory {
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<EnemyCreator>(const std::string&, const std::deque<sf::Vector2i>&)>> creators;   ///< Map linking enemy types to their creation functions


public:
    /**
     * @brief Constructs the factory and registers all enemy creators
     */
    EnemyFactory();

    /**
     * @brief Creates a new enemy of the specified type
     * @param type The type of enemy to create ("grunt", "stalker", "juggernaut")
     * @param id Unique identifier for the enemy
     * @param path Path that the enemy will follow
     * @return A unique pointer to the created enemy
     * @throw std::runtime_error if the enemy type is unknown
     */
    std::unique_ptr<EnemyCreator> create(const std::string& type, const std::string& id, const std::deque<sf::Vector2i>& path) const;
};

#endif //ENEMYFACTORY_H
