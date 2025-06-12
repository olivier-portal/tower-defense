//
// Created by gravy on 06/06/2025.
//
#ifndef ENEMY_CREATOR_H
#define ENEMY_CREATOR_H

#include <string>
#include <deque>
#include <optional>
#include <cmath>
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @file EnemyCreator.h
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
    EnemyCreator(const std::string& id, const std::deque <sf::Vector2i>& path, float speed, int lives, int credit, int score, std::string sprite = "");

    /**
     * @brief Virtual destructor for proper inheritance cleanup
     */
    virtual ~EnemyCreator() = default;

    // Basic getters
    std::string getId() const;
    sf::Vector2i& getGridPosition();
    sf::Vector2f& getPixelPosition();
    float getSpeed() const;
    int getLives() const;
    int getCredit() const;
    int getScore() const;

    /**
     * @brief Advances the enemy to the next position in its path
     *
     * @details
     * - If path is empty: resets grid position and marks enemy as arrived
     * - Otherwise: updates current grid position with first path position and removes it from path
     * - If path still has positions: sets next grid position
     * - If path becomes empty: resets next grid position
     */
    void advancePath();

    /**
     * @brief Converts a grid position to its corresponding pixel position
     *
     * @param gridPosition The position in grid coordinates (x, y)
     * @param tileSize The size of one grid tile in pixels
     * @return sf::Vector2f The corresponding position in pixel coordinates
     *
     * @details Performs the conversion by multiplying each grid coordinate
     * by the tile size to get the pixel position in the game window
     */
    sf::Vector2f pixelPositionFromGridPosition(const sf::Vector2i& gridPosition, float tileSize);

    /**
     * @brief Calculates the normalized direction vector between current and next grid positions
     *
     * @param tileSize The size of one grid tile in pixels
     * @return sf::Vector2f A normalized vector (magnitude of 1) representing the movement direction,
     *                      returns (0,0) if either current or next position is not set
     *
     * @details
     * Converts grid positions to pixel coordinates and computes a normalized
     * direction vector between them. This vector is used for smooth movement
     * between grid positions.
     */
    sf::Vector2f computePixelDirection(float tileSize);

    /**
     * @brief Updates the enemy's pixel position based on its current movement
     *
     * @param tileSize The size of one grid tile in pixels
     *
     * @details
     * Calculates the new pixel position using:
     * - Current position
     * - Movement direction
     * - Enemy speed
     *
     * If the enemy reaches its next grid position (determined by hasReachedNextGrid),
     * it snaps to that position exactly and advances to the next path segment.
     * Otherwise, it moves smoothly towards the next position.
     */
    void updatePixelPosition(float tileSize);

    /**
     * @brief Checks if the enemy has reached its next grid position
     *
     * @param tileSize The size of one grid tile in pixels
     * @return bool true if the enemy is close enough to the next grid position,
     *              false if not or if current/next positions are not set
     *
     * @details
     * Calculates the Euclidean distance between the current pixel position and
     * the next grid position (converted to pixels). The enemy is considered to
     * have reached its target if the distance is less than half its speed.
     * This threshold prevents overshooting and ensures smooth movement transitions.
     */
    bool hasReachedNextGrid(float tileSize);

    void render(sf::RenderWindow& window, float tileSize);

    /**
     * @brief Adds damage to the pending damage queue for later processing
     *
     * @param damage Amount of damage to be applied to the enemy
     *
     * @details
     * Instead of immediately applying damage, this method queues it for processing
     * during the next update cycle. This approach:
     * - Prevents race conditions when multiple damage sources hit simultaneously
     * - Ensures damage is applied in the correct order
     * - Allows for better synchronization with the game loop
     *
     * The queued damage will be processed in FIFO order during the update() method call
     */
    void queueDamage(int damage);

    /**
     * @brief Applies damage to the enemy and updates its state
     *
     * @param damage Amount of damage to inflict (positive value)
     * @return int Remaining health points after damage is applied
     *
     * @details
     * This method:
     * - Subtracts damage from current health points
     * - Updates isAlive state if health drops to 0 or below
     * - Is typically called by the update() method to process queued damage
     *
     * Note: Damage is applied immediately, for delayed application,
     * use queueDamage() instead
     */
    int takeDamage(int damage);

    /**
     * @brief Checks if the enemy has reached its final destination
     *
     * @return bool true if the enemy has completed its path and arrived at the destination, false if still moving along the path
     *
     * @details
     * This method indicates whether the enemy has finished traversing its assigned path.
     * An enemy is considered "arrived" when:
     * - It has consumed all waypoints in its path
     * - The path queue is empty
     * - The isArrived flag has been set to true by advancePath()
     *
     * This status is used to:
     * - Determine if the enemy should be removed from the game
     * - Calculate if the player should lose lives
     */
    bool hasArrived() const;

    /**
     * @brief Checks if the enemy has been eliminated
     *
     * @return bool true if the enemy has been eliminated (health <= 0), false if the enemy is still alive
     *
     * @details
     * This method checks the enemy's life status, which is updated by takeDamage().
     * An enemy is considered dead when:
     * - Its health points have dropped to 0 or below
     * - The isAlive flag has been set to false
     *
     * This status is used to:
     * - Determine if the enemy should be removed from the game
     * - Award credits and score to the player
     *
     * @see takeDamage() - The method that can trigger death state
     */
    bool isDead() const;

    /**
     * @brief Updates the enemy's state and position
     *
     * @param tileSize Size of one grid tile in pixels
     *
     * @details
     * This method:
     * 1. Checks if updates should be processed (enemy alive and not arrived)
     * 2. Processes pending damage while enemy is still alive
     * 3. Updates position if enemy survives damage processing
     *
     * The improved damage processing loop stops immediately when the enemy dies,
     * avoiding unnecessary iterations through the remaining damage queue.
     */
    void update(float tileSize);


protected:
    const std::string id;                          ///< Unique identifier for the enemy type
    std::deque <sf::Vector2i> path;                ///< Remaining path positions
    std::optional<sf::Vector2i> gridPosition;      ///< Current position in grid coordinates
    std::optional<sf::Vector2i> nextGridPosition;  ///< Next position in grid coordinates
    std::optional<sf::Vector2f> pixelPosition;     ///< Exact position in pixels for smooth movement
    float speed;                                   ///< Movement speed in pixels per frame
    int lives;                                     ///< Current health points
    std::queue<int> pendingDamage;                 ///< Queue of damage values to be applied during update
    bool isAlive = true;                           ///< Whether the enemy is still alive
    bool isArrived = false;                        ///< Whether the enemy has reached its destination
    const int credit;                              ///< Credits awarded when defeated
    const int score;                               ///< Points awarded when defeated
    std::string sprite;                            ///< Sprite sheet name
};

#endif //ENEMY_CREATOR_H
