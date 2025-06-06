//
// Created by gravy on 06/06/2025.
//

#include <string>
#include <deque>
#include <optional>
#include <SFML/System/Vector2.hpp>

#ifndef ENNEMY_H
#define ENNEMY_H
/**
 * @file EnnemyCreator.h
 * @brief Class responsible for creating and managing enemy entities in the tower defense game.
 */

/**
 * @class EnemyCreator
 * @brief Base class for creating and managing enemy entities.
 *
 * This class handles the creation and movement of enemies along a predefined path.
 * It manages both grid-based and pixel-based positioning for smooth movement.
 */
class EnemyCreator {
public:

    /**
     * @brief Constructs a new enemy entity.
     *
     * @param id Unique identifier for the enemy type
     * @param path Deque of grid positions defining the enemy's path
     * @param speed Movement speed of the enemy (in pixels per frame)
     * @param lives Initial health points of the enemy
     * @param credit Amount of credits awarded when the enemy is defeated
     * @param score Points awarded when the enemy is defeated
     * @throws std::invalid_argument if the path is empty
     */
    EnemyCreator(std::string id, std::deque <sf::Vector2i> path, float speed, int lives, int credit, int score);

    /**
     * @brief Virtual destructor for proper inheritance cleanup
     */
    virtual ~EnemyCreator() = default;

    /**
     * @brief Advances the enemy to the next position in its path
     *
     * Updates the current grid position and next grid position based on the path.
     * Sets isArrived to true when the enemy reaches the end of its path.
     */
    void advancePath();

    void update();


protected:
    std::string id;                                ///< Unique identifier for the enemy type
    std::deque <sf::Vector2i> path;                ///< Remaining path positions
    std::optional<sf::Vector2i> gridPosition;      ///< Current position in grid coordinates
    std::optional<sf::Vector2i> nextGridPosition;  ///< Next position in grid coordinates
    std::optional<sf::Vector2f> pixelPosition;     ///< Exact position in pixels for smooth movement
    float speed;                                   ///< Movement speed in pixels per frame
    int lives;                                     ///< Current health points
    bool isAlive = true;                           ///< Whether the enemy is still alive
    bool isArrived = false;                        ///< Whether the enemy has reached its destination
    int credit;                                    ///< Credits awarded when defeated
    int score;                                     ///< Points awarded when defeated
};

#endif //ENNEMY_H
