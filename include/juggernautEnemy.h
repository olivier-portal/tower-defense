//
// Created by gravy on 10/06/2025.
//
#ifndef JUGGERNAUTENEMY_H
#define JUGGERNAUTENEMY_H

# include "EnemyCreator.h"

/**
 * @class juggernautEnemy
 * @brief Heavy-duty enemy unit with high durability
 *
 * Juggernaut represents a tank-like enemy unit that excels in survivability
 * but moves slowly across the map. These units are designed to absorb
 * significant damage while providing high rewards when defeated.
 *
 * Key characteristics:
 * - Very slow movement speed (1.0f)
 * - High health points (300)
 * - High credit reward (25)
 * - High score value (100)
 */
class juggernautEnemy : public EnemyCreator {
private:
    static constexpr int JUGGERNAUT_SPEED = 1.0f;
    static constexpr int JUGGERNAUT_LIVES = 200;
    static constexpr int JUGGERNAUT_CREDIT = 25;
    static constexpr int JUGGERNAUT_SCORE = 100;
    static constexpr std::string_view JUGGERNAUT_SPRITE = "juggernaut.png";

public:
    /**
     * @brief Constructs a new juggernaut enemy
     *
     * @param id Unique identifier for this juggernaut instance
     * @param path Predefined path the juggernaut will follow
     * @param speed Movement speed (default: 1.0f)
     * @param lives Initial health points (default: 300)
     * @param credit Credits awarded when defeated (default: 25)
     * @param score Score points awarded when defeated (default: 100)
     * @param sprite Sprite filename for rendering (default: "juggernaut.png")
     */
    explicit juggernautEnemy(const std::string& id, const std::deque <sf::Vector2i>& path, float speed = JUGGERNAUT_SPEED, int lives = JUGGERNAUT_LIVES, int credit = JUGGERNAUT_CREDIT, int score = JUGGERNAUT_SCORE, std::string_view sprite = JUGGERNAUT_SPRITE);
};

#endif //JUGGERNAUTENEMY_H
