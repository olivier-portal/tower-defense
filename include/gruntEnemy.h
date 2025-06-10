//
// Created by gravy on 10/06/2025.
//
# include "EnemyCreator.h"

#ifndef GRUNTENEMY_H
#define GRUNTENEMY_H

/**
 * @class gruntEnemy
 * @brief Basic balanced enemy unit with moderate characteristics
 *
 * Grunt represents the standard enemy unit with balanced stats across all attributes.
 * These units serve as the backbone of enemy waves, offering a moderate challenge
 * with balanced speed, health, and rewards.
 *
 * Key characteristics:
 * - Moderate movement speed (2.0f)
 * - Standard health points (100)
 * - Basic credit reward (10)
 * - Standard score value (50)
 */
class gruntEnemy : public EnemyCreator {
private:
    static constexpr int GRUNT_SPEED = 2.0f;
    static constexpr int GRUNT_LIVES = 100;
    static constexpr int GRUNT_CREDIT = 10;
    static constexpr int GRUNT_SCORE = 50;
    static constexpr std::string GRUNT_SPRITE = "grunt.png";

public:
    /**
     * @brief Constructs a new grunt enemy
     *
     * @param id Unique identifier for this grunt instance
     * @param path Predefined path the grunt will follow
     * @param speed Movement speed (default: 2.0f)
     * @param lives Initial health points (default: 100)
     * @param credit Credits awarded when defeated (default: 10)
     * @param score Score points awarded when defeated (default: 50)
     * @param sprite Sprite filename for rendering (default: "grunt.png")
     */
    explicit gruntEnemy(const std::string& id, const std::deque <sf::Vector2i>& path, float speed = GRUNT_SPEED, int lives = GRUNT_LIVES, int credit = GRUNT_CREDIT, int score = GRUNT_SCORE, std::string sprite = GRUNT_SPRITE);
};

#endif //GRUNTENEMY_H
